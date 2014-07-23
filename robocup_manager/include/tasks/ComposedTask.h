/**
 * \file 		ComposedTask.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#ifndef COMPOSEDTASK_H_
#define COMPOSEDTASK_H_

#include <vector>

#include "AbstractTask.h"
#include "SimpleTask.h"

class ComposedTask : public AbstractTask {
public:
	ComposedTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs);
	virtual ~ComposedTask();

	void addTask(SimpleTask *t);
	AbstractTask* getCurrentTask();

	virtual bool checkInitialConditions()
	{return true;}

	virtual bool checkFailConditions()
	{return false;}

	virtual void executeCancelation(){}

	virtual std::string executeCancelationImpl(){}

	virtual bool checkCompletionConditions()
	{return true;}

	virtual void executePostCompletion(){}



protected:
	std::vector<SimpleTask *> m_tasks;
	int m_taskIndex;




};

#endif /* COMPOSEDTASK_H_ */
