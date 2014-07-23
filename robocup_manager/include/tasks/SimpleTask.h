/**
 * \file 		SimpleTask.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */


#ifndef SIMPLETASK_H_
#define SIMPLETASK_H_

#include "AbstractTask.h"

class SimpleTask : public AbstractTask {
public:
	SimpleTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs);
	virtual ~SimpleTask();

	virtual bool checkInitialConditions()
	{
		if(checkInitialConditionsImpl())
		{
			setState(State::READY);
			ROS_INFO("task go to READY");
			return true;
		}else{
			return false;
		}
	}

	virtual bool checkInitialConditionsImpl()=0;

	virtual bool checkFailConditions()
	{return false;}

	virtual void executeCancelation()
	{
		executeCancelationImpl();
		setState(State::FAILED);
	}

	virtual std::string executeCancelationImpl() = 0;

	virtual bool checkCompletionConditions()
	{return false;}

	virtual void executePostCompletion(){}

	virtual void execute()
	{
		executeImpl();
		ROS_INFO("task go to RUNNING");
		setState(State::RUNNING);
	}

	virtual void executeImpl()=0;
};

#endif /* SIMPLETASK_H_ */
