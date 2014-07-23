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
	void assignActor(Actor *a);

	virtual std::string getDescrition()
	{
		std::stringstream sstr;
		sstr << m_description  << ", subtask :" << getCurrentTask()->getDescrition();
		return sstr.str();m_description;
	}


	virtual bool checkInitialConditions();

	virtual bool checkFailConditions();

	virtual void executeCancelation();

	virtual std::string executeCancelationImpl();

	virtual bool checkCompletionConditions();

	virtual void executePostCompletion();

	virtual void execute();

protected:
	std::vector<SimpleTask *> m_tasks;
	int m_taskIndex;




};

#endif /* COMPOSEDTASK_H_ */
