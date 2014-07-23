/**
 * \file 		AbstractTask.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#ifndef ABSTRACTTASK_H_
#define ABSTRACTTASK_H_

#include "arenaState/ArenaState.h"
#include "arenaState/actors/Actor.h"
#include "gameState/GeneralGameStatus.h"

class Controller;

class AbstractTask {
public:
	AbstractTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs);
	virtual ~AbstractTask();

	enum State
	{
		WAITING,
		READY,
		RUNNING,
		COMPLETED,
		FAILED
	};

	AbstractTask::State getState();

	void setState(AbstractTask::State s)
	{
		m_state = s;
	}

	void assignActor(Actor *a)
	{
		m_assigned = a;
	}

	Actor *getAssignedActor()
	{
		return m_assigned;
	}

	virtual std::string getDescrition()
	{
		return m_description;
	}

	virtual bool checkInitialConditions() = 0;

	virtual bool checkFailConditions() = 0;

	virtual void executeCancelation() = 0;
	virtual std::string executeCancelationImpl() = 0;

	virtual bool checkCompletionConditions() = 0;
	virtual void executePostCompletion() = 0;


	virtual void execute(){}


protected:
	std::string m_type;
	std::string m_description;

	AbstractTask::State m_state;
	Actor *m_assigned;

	ArenaState *m_as;
	Controller *m_c;
	GeneralGameStatus *m_ggs;

};

#endif /* ABSTRACTTASK_H_ */
