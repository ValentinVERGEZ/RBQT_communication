/**
 * \file 		ExploreMachineTask.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-18
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include "tasks/explorationTask/ExploreMachineTask.h"
#include "tasks/basicTasks/GoToTask.h"
#include "tasks/basicTasks/ReportMachineTask.h"

ExploreMachineTask::ExploreMachineTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs, std::string machineName)
	:ComposedTask(as, c, ggs)
{
	m_destName = machineName;

	geometry_msgs::Pose p = m_as->getExplorationPose(machineName);
	addTask(new GoToTask(as, c, ggs, p));
	addTask(new ReportMachineTask(as, c, ggs, machineName));

	std::stringstream sstr;
	sstr << "ExploreMachineTask, machine : " << machineName;
	m_description = sstr.str();
}

ExploreMachineTask::~ExploreMachineTask() {
	// TODO Auto-generated destructor stub
}
