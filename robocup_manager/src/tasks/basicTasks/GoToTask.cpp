/**
 * \file 		GoToTask.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */


#include "tasks/basicTasks/GoToTask.h"
#include "Controller.h"
#include "utils/geometry_utils.h"
#include "executePath/EdCState.h"
#include "executePath/command.h"
#include <sstream>
#include <tf/transform_datatypes.h>

GoToTask::GoToTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs, geometry_msgs::Pose p)
	: SimpleTask(as, c, ggs)
{
	m_target = p;
	m_pathId = -1;

	std::stringstream sstr;
	sstr << "GoToTask, dest : (" << p.position.x << ", "
							     << p.position.y << ", "
							     << tf::getYaw(p.orientation) << ")";
	m_description = sstr.str();
}

GoToTask::~GoToTask() {
	// TODO Auto-generated destructor stub
}



bool GoToTask::checkInitialConditionsImpl()
{
	Actor * a;
	ROS_INFO("Actor assigned?? %s", (m_assigned==NULL? "false" : "true"));
	ROS_INFO("Robot is busy : %s", (m_assigned->isBusy()? "true" : "false"));

	if (m_assigned != NULL && !(m_assigned->isBusy()))
	{
		return true;
	}
	return false;
}

bool GoToTask::checkFailConditions()
{
	return (m_ggs->getEdCState().state == executePath::EdCState::PROBLEM);
}


std::string GoToTask::executeCancelationImpl()
{
	m_assigned->setBusy(false);
}

bool GoToTask::checkCompletionConditions()
{
	//le robot atteind la cible et le executePath indique terminé
	bool robotAtDestination = isSame(m_assigned->getPose(), m_target);
	return (m_ggs->getEdCState().ID == m_pathId ) && (m_ggs->getEdCState().state == executePath::EdCState::FINISHED);
}

void GoToTask::executePostCompletion()
{
	m_assigned->setBusy(false);
}

void GoToTask::executeImpl()
{
	m_assigned->setBusy(true);
	//set the new destination
	m_start = m_assigned->getPose();

	//compute the path to destination
	//launch the pathPlanner

	m_c->generatePath(m_pathId, m_start, m_target);
	ROS_INFO("GoToTask : request path id = %d", m_pathId);
	//wait the generation of the message
	sleep(1);

	//send the order to the robotino

	m_c->executePath(m_pathId, executePath::command::Request::EXECUTE_PATH);

}
