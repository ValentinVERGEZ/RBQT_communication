/**
 * \file 		IdentifyMachineTypeTask.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-18
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include "IdentifyMachineTypeTask.h"

IdentifyMachineTypeTask::IdentifyMachineTypeTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs)
: SimpleTask(as, c, ggs)
{
	// TODO Auto-generated constructor stub

}

IdentifyMachineTypeTask::~IdentifyMachineTypeTask() {
	// TODO Auto-generated destructor stub
}




bool IdentifyMachineTypeTask::checkInitialConditionsImpl()
{
	return true;
}

bool IdentifyMachineTypeTask::checkFailConditions()
{
	return false;
}


std::string IdentifyMachineTypeTask::executeCancelationImpl()
{
	if (m_assigned != NULL)
		m_assigned->setBusy(false);
}

bool IdentifyMachineTypeTask::checkCompletionConditions()
{

	return true;
}

void IdentifyMachineTypeTask::executePostCompletion()
{
	if (m_assigned != NULL)
		m_assigned->setBusy(false);
}


void IdentifyMachineTypeTask::executeImpl()
{
	//recuperer lightSpec du traitement d'image

	//comparer à la liste de machine de game state

	//mettre à jour lightSpec dans arenaState
}
