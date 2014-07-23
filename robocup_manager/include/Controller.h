/**
 * \file 		Controller.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <list>
#include <atomic>

#include "ros/ros.h"
#include "arenaState/ArenaState.h"
#include "gameState/GeneralGameStatus.h"

#include "tasks/AbstractTask.h"
#include "refBoxComm/GameState.h"
#include "refBoxComm/ExplorationInfo.h"
#include "refBoxComm/LightSpec.h"
#include "executePath/EdCState.h"
#include "rbqt_lecture_feu_tricolore/LightSignal.h"
#include "rbqt_pathfinder/GeneratePath.h"
#include "nav_msgs/Odometry.h"

class Controller {

public:

	enum Team {
		cyan,
		magenta
	};

	Controller();
	Controller(std::string robotName, int robotNumber, Team team);
	virtual ~Controller();

	void run();

	void addJob(AbstractTask *t)
	{
		m_jobList.push_back(t);
	}

	ArenaState *getArenaState()
	{
		return &m_as;
	}

	GeneralGameStatus *getGameState()
	{
		return &m_ggs;
	}

	Actor* findAvailableRobotino()
	{
		return m_as.getRobotino(m_robotName);
	}

	bool generatePath(int &id, geometry_msgs::Pose &start, geometry_msgs::Pose &target);
	bool executePath(int id, int type);
	bool reportMachine(std::string name, std::string type);
	bool getTypeFromFeu(refBoxComm::LightSpec ls);

protected:

	ArenaState m_as;
	GeneralGameStatus m_ggs;

	Team m_team;
	std::string m_robotName;
	int m_robotNumber;

	int m_lastPathId;

	std::list<AbstractTask *> m_jobList;

	std::atomic<bool>  m_stopController;

	ros::NodeHandle m_nh;

	ros::Subscriber m_gameStateSub;
	ros::Subscriber m_explorationInfoSub;
	ros::Subscriber m_pathFoundSub;
	ros::Subscriber m_aStarStateSub;
	ros::Subscriber m_edCStateSub;
	ros::Subscriber m_lectureFeuSub;
	ros::Subscriber m_odomSub;

	//ros::Publisher m_

	ros::ServiceClient m_reportMachineSC;
	ros::ServiceClient m_commandExecutePathSC;
	ros::ServiceClient m_genratePathSC;

	//callBack functions
	void gameStateCB(const refBoxComm::GameState &gs);
	void explorationInfoCB(const refBoxComm::ExplorationInfo &ei);
	void pathFoundCB();
	void aStarStateCB();
	void executePathCB(const executePath::EdCState &edCState);
	void lectureFeuCB(const rbqt_lecture_feu_tricolore::LightSignal &ls);
	void odomCB(const nav_msgs::Odometry &odo);

	void processTasks();


};

#endif /* CONTROLLER_H_ */
