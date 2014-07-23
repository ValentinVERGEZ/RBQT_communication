/**
 * \file 		Controller.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <boost/bind.hpp>
#include <string>

#include "Controller.h"
#include "refBoxComm/GameState.h"
#include "refBoxComm/ExplorationInfo.h"
#include "refBoxComm/ExplorationSignal.h"
#include "refBoxComm/ReportMachine.h"
#include "executePath/EdCState.h"
#include "executePath/command.h"
#include "rbqt_lecture_feu_tricolore/LightSignal.h"


Controller::Controller(): m_nh("~")
{

	m_stopController = false;

	std::string t;
	m_nh.param<std::string>("team", t, "magenta" );
	m_nh.param<std::string>("robot_name", m_robotName, "R1" );

	//m_nh.getParam("team", t);
	m_team = (t=="cyan" ? Controller::cyan : Controller::magenta);
	ROS_INFO("Robot team : %s", t.c_str());

	//m_nh.getParam("robot_name", m_robotName);
	ROS_INFO("Robot name : %s", m_robotName.c_str());

	m_robotNumber = stoi(m_robotName.substr(1));
	ROS_INFO("Robot number : %d", m_robotNumber);


	m_lastPathId=0;
}

Controller::Controller(std::string robotName, int robotNumber, Team team)
{

	m_stopController = false;

	m_robotName = robotName;
	m_robotNumber = robotNumber;
	m_team = team;

	m_lastPathId=0;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}


void Controller::run()
{

    int loopFreq = 20;
    unsigned long count = 0;

    //Initialize topic subscription
	m_gameStateSub = m_nh.subscribe("/refBoxComm/GameState", 1000, &Controller::gameStateCB, this);
	m_explorationInfoSub = m_nh.subscribe("/refBoxComm/ExplorationInfo", 1000, &Controller::explorationInfoCB, this);
	//m_pathFoundSub = m_nh.subscribe("/pathFound", 1000, &Controller::gameStateCB, this);
	m_edCStateSub = m_nh.subscribe("/EdCState", 1000, &Controller::executePathCB, this);
	m_lectureFeuSub = m_nh.subscribe("/rbqt_lecture_feu_tricolore/result", 1000, &Controller::lectureFeuCB, this);
	m_odomSub = m_nh.subscribe("/odom", 1000, &Controller::odomCB, this);

	//Initialize service client
	m_reportMachineSC = m_nh.serviceClient<refBoxComm::ReportMachine>("refBoxComm/ReportMachine");
	m_genratePathSC = m_nh.serviceClient<rbqt_pathfinder::GeneratePath>("generatePath");
	m_commandExecutePathSC = m_nh.serviceClient<executePath::command>("command");

	ROS_INFO("Controller launched");

	ros::Rate loop_rate(loopFreq);

    while (ros::ok() && !m_stopController )
	{

    	processTasks();



    	ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
}

void Controller::processTasks()
{
	static bool alreadyStopped=false;

	if (m_ggs.getGameState().phase != refBoxComm::GameState::EXPLORATION ||
		m_ggs.getGameState().state != refBoxComm::GameState::RUNNING)
	{
		if (!alreadyStopped)
		{
			executePath(0, executePath::command::Request::CANCEL);
			alreadyStopped=true;
		}
		//arret des robots
	}
	else
	{

		for(auto jobIter = m_jobList.begin(); jobIter != m_jobList.end(); jobIter++)
		{
			//ROS_INFO("Controller : Task processing");

			if((*jobIter)->getState()==AbstractTask::State::WAITING) {
				(*jobIter)->checkInitialConditions();
				//ROS_INFO("Controller : Task waiting");
			}
			//if the task is ready, then run it
			if((*jobIter)->getState()==AbstractTask::State::READY) {
				(*jobIter)->execute();
				//ROS_INFO("Controller : Task ready, executing... %s",(*jobIter)->getDescrition().c_str() );
			}
			//if the task is running we have to check that
			//1) it isn't already completed
			//2) it can be completed
			if((*jobIter)->getState()==AbstractTask::State::RUNNING) {
				if((*jobIter)->checkFailConditions()) {
					(*jobIter)->executeCancelation(); //also sets state to failed
					ROS_INFO("Controller : Task cancel : %s",(*jobIter)->getDescrition().c_str() );
				}else if((*jobIter)->checkCompletionConditions()) {
					(*jobIter)->executePostCompletion(); //also sets state to completed
					ROS_INFO("Controller : Task completed : %s",(*jobIter)->getDescrition().c_str() );
				}
			}
		}

		alreadyStopped=false;
	}
	//supprimer les taches terminées
}

void Controller::gameStateCB(const refBoxComm::GameState &gs)
{
	m_ggs.updateGameState(gs);
}


void Controller::explorationInfoCB(const refBoxComm::ExplorationInfo &ei)
{
	m_ggs.updateExplorationInfo(ei);

	if (m_as.getMachines().size() == 0)
	{
		for(unsigned int idx=0; idx < ei.machines.size(); ++idx)
		{
			Machine *m = new Machine(ei.machines[idx].name);
			geometry_msgs::Pose p;
			p.position.x = ei.machines[idx].pose.x;
			p.position.y = ei.machines[idx].pose.y;
			p.orientation = tf::createQuaternionMsgFromYaw(ei.machines[idx].pose.theta);
			m->updatePosition(p);
			m_as.addMachine(ei.machines[idx].name,m);
		}
		ROS_INFO("Controller : Machines loaded");
	}

	if (m_as.getSignals().size() == 0)
	{
		for(unsigned int idx=0; idx < ei.signals.size(); ++idx)
		{
			m_as.addSignal(ei.signals[idx].type, ei.signals[idx]);
		}
		ROS_INFO("Controller : Exploration Signal loaded");
	}
}


void Controller::executePathCB(const executePath::EdCState &edCState)
{
	static int last_edCState = -1;


	m_ggs.updateEdCState(edCState);

	if (last_edCState != edCState.state )//pour eviter de se faire spammer les logs
	{
		ROS_INFO("Controller : Etat executePath : %d", edCState.state);
		last_edCState = edCState.state;
	}
}


void Controller::lectureFeuCB(const rbqt_lecture_feu_tricolore::LightSignal &ls)
{
	m_ggs.updateActualSignal(ls);
}

bool Controller::generatePath(int &id, geometry_msgs::Pose &start, geometry_msgs::Pose &target)
{
	rbqt_pathfinder::GeneratePath gp_srv;

	m_lastPathId++;
	id = m_lastPathId;
	gp_srv.request.id = m_lastPathId;
	gp_srv.request.Depart = start;
	gp_srv.request.Arrivee = target;
	gp_srv.request.utilisePositionOdometry = true;

	if (m_genratePathSC.call(gp_srv))
	{
	  return gp_srv.response.requeteAcceptee;
	}
	else
	{
	  ROS_ERROR("Controller : Failed to call service generatePath");
	  return false;
	}
}

void Controller::odomCB(const nav_msgs::Odometry &odo)
{
	m_as.getRobotino(m_robotName)->updatePosition(odo.pose.pose);
}

bool Controller::executePath(int id, int type)
{
	executePath::command cmd_srv;

	cmd_srv.request.ID = id;
	cmd_srv.request.type = type;

	ROS_INFO("Controller : executePath : %d", id);
	if (m_commandExecutePathSC.call(cmd_srv))
	{
		return cmd_srv.response.accepted;
	}
	else
	{
		ROS_ERROR("Controller : Failed to call service executePath command");
		return false;
	}
	return false;
}


bool Controller::reportMachine(std::string name, std::string type)
{
	refBoxComm::ReportMachine rm_srv;

	rm_srv.request.name = name;
	rm_srv.request.type = type;

	if (m_reportMachineSC.call(rm_srv))
	{
		ROS_INFO("Controller : Machine %s of type %s reported", name.c_str(), type.c_str());
		return true;
	}
	else
	{
		ROS_ERROR("Controller : Failed to call service reportMachine");
		return false;
	}
}

bool Controller::getTypeFromFeu(refBoxComm::LightSpec ls)
{
	return false;
}

