/**
 * \file 		GoToTask.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */


#ifndef GOTOTASK_H_
#define GOTOTASK_H_

#include <tasks/SimpleTask.h>
#include <geometry_msgs/Pose.h>

class GoToTask: public SimpleTask {
public:
	GoToTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs, geometry_msgs::Pose p);
	virtual ~GoToTask();


	virtual bool checkInitialConditionsImpl();

	virtual bool checkFailConditions();

	virtual std::string executeCancelationImpl();

	virtual bool checkCompletionConditions();
	virtual void executePostCompletion() ;

	virtual void executeImpl();

protected:

	geometry_msgs::Pose m_start;
	geometry_msgs::Pose m_target;


	int m_pathId;

};

#endif /* GOTOTASK_H_ */
