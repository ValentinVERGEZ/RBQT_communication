/**
 * \file 		ReportMachineTask.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-18
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */


#include "tasks/basicTasks/ReportMachineTask.h"

#include "Controller.h"
#include "arenaState/ArenaState.h"
#include "rbqt_lecture_feu_tricolore/LightSignal.h"
#include "refBoxComm/ExplorationSignal.h"
#include "refBoxComm/ExplorationInfo.h"
#include "utils/geometry_utils.h"

ReportMachineTask::ReportMachineTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs, std::string machineName)
	: SimpleTask(as, c, ggs)
{

	m_machineName = machineName;

	std::stringstream sstr;
	sstr << "ReportMachineTask, machine : " << machineName;
	m_description = sstr.str();
}

ReportMachineTask::~ReportMachineTask() {
	// TODO Auto-generated destructor stub
}

bool ReportMachineTask::checkInitialConditionsImpl()
{
	bool robotAtDestination = isSame(m_assigned->getPose(), m_as->getExplorationPose(m_machineName));

	return robotAtDestination && !m_assigned->isBusy() && m_as->getSignals().size() !=0 && m_as->getMachines().size();
}

bool ReportMachineTask::checkFailConditions()
{
	return false;
}


std::string ReportMachineTask::executeCancelationImpl()
{
	if (m_assigned != NULL)
		m_assigned->setBusy(false);
}

bool ReportMachineTask::checkCompletionConditions()
{

	return true;
}

void ReportMachineTask::executePostCompletion()
{
	if (m_assigned != NULL)
		m_assigned->setBusy(false);
}


void printSignal(rbqt_lecture_feu_tricolore::LightSignal &s)
{
	for (int i = 0; i < s.lights.size(); i++)
	{
		ROS_INFO("%d : %d", s.lights[i].color, s.lights[i].state);

	}
}

void printSignal(refBoxComm::ExplorationSignal &s)
{
	for (int i = 0; i < s.lights.size(); i++)
	{
		ROS_INFO("%d : %d", s.lights[i].color, s.lights[i].state);

	}
}

void ReportMachineTask::executeImpl()
{
	m_assigned->setBusy(true);
	ROS_INFO("Report machine Task execute");
	//recuperer lightSpec du traitement d'image
	rbqt_lecture_feu_tricolore::LightSignal signalSeen = m_ggs->getActualSignal();

	printSignal(signalSeen);

	//comparer à la liste de signaux de game state
	std::map<std::string, refBoxComm::ExplorationSignal> signals = m_as->getSignals();

	std::string foundSignal;
	bool found = false;
	for(auto iter=signals.begin(); iter != signals.end(); iter++)
	{
		if (compareSignals(iter->second, signalSeen))
		{
			found = true;
			foundSignal = iter->first;
		}

	}
	if (!found)
	{
		ROS_INFO("ReportMachineTask : signal unknown");
		return;
	}

	ROS_INFO("ReportMachineTask : find machine %s of type %s", m_machineName.c_str(), foundSignal.c_str());

	//mettre à jour lightSpec dans arenaState
	//m_as->getMachines()[type].setType(foundSignal);

	//reporter la machine via la refBox
	m_c->reportMachine(m_machineName, foundSignal);
}

bool ReportMachineTask::compareSignals(const refBoxComm::ExplorationSignal &signalMachine,
									   const rbqt_lecture_feu_tricolore::LightSignal &signalDetected)
{
	int cpt = 0;

	for (int i = 0; i < signalMachine.lights.size(); i++)
	{
		for (int j = 0; j < signalDetected.lights.size(); j++)
		{
			if (signalMachine.lights[i].color == signalDetected.lights[j].color &&
				signalMachine.lights[i].state == signalDetected.lights[j].state)
			{
				cpt++;
			}
		}
	}

	if (cpt == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}
