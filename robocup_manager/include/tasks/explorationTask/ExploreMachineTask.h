/**
 * \file 		ExploreMachineTask.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-18
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */


#ifndef EXPLOREMACHINETASK_H_
#define EXPLOREMACHINETASK_H_

#include "tasks/ComposedTask.h"

class ExploreMachineTask : public ComposedTask {
public:
	ExploreMachineTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs);
	virtual ~ExploreMachineTask();
protected:


};

#endif /* EXPLOREMACHINETASK_H_ */
