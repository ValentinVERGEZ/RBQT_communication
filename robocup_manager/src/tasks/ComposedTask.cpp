/**
 * \file 		ComposedTask.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include "tasks/ComposedTask.h"

ComposedTask::ComposedTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs)
	: AbstractTask(as, c, ggs)
{
	m_taskIndex = 0;
}

ComposedTask::~ComposedTask() {
	// TODO Auto-generated destructor stub
	// TODO delete all tasks
}

void ComposedTask::addTask(SimpleTask *t)
{
	m_tasks.push_back(t);

    if(getAssignedActor()!=NULL)
    {
		t->assignActor(getAssignedActor());
	}
}


AbstractTask* ComposedTask::getCurrentTask()
{
	return m_tasks[m_taskIndex];
}


void ComposedTask::assignActor(Actor *a)
{
	AbstractTask::assignActor(a);

	for(unsigned int idx = 0; idx < m_tasks.size(); ++idx)
	{
		m_tasks[idx]->assignActor(a);
	}
	if(a==NULL)
	{
		ROS_INFO("WARNING TASK ASSIGNED TO NULL ACTOR");
	}
}

bool ComposedTask::checkInitialConditions()
{
	if(!getAssignedActor()->isBusy())
	{
		setState(State::READY);

		//getAssignedActor()->setBusy(true);
		return true;
	}
	return false;
}


bool ComposedTask::checkFailConditions()
{
	return getCurrentTask()->checkFailConditions();
}

void ComposedTask::executeCancelation()
{

}

std::string ComposedTask::executeCancelationImpl()
{
	return NULL;
}

bool ComposedTask::checkCompletionConditions()
{
	return getCurrentTask()->checkCompletionConditions();
}


void ComposedTask::executePostCompletion()
{
	getCurrentTask()->executePostCompletion();
	getCurrentTask()->setState(State::COMPLETED);

	if(m_taskIndex<m_tasks.size()-1) {
		//there is another task
		m_taskIndex++;
		setState(State::READY);
		getCurrentTask()->setState(State::READY);
	}else {
		//there is no other task
		setState(State::COMPLETED);
		getAssignedActor()->setBusy(false);
	}
}

void ComposedTask::execute() {
	if(getCurrentTask()->checkInitialConditions()) {
		getCurrentTask()->execute();
		setState(State::RUNNING);
		getCurrentTask()->setState(State::RUNNING);
	}
}
