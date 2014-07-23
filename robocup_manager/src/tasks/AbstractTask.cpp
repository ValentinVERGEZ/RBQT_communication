/**
 * \file 		AbstractTask.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include "tasks/AbstractTask.h"

AbstractTask::AbstractTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs) {
	m_as = as;
	m_c = c;
	m_ggs =ggs;

	m_assigned = NULL;
	m_state = WAITING;
}

AbstractTask::~AbstractTask() {
	// TODO Auto-generated destructor stub
}

AbstractTask::State AbstractTask::getState()
{
	return m_state;
}
