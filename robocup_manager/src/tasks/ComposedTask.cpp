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
}

