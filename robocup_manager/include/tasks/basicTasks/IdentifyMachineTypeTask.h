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

#ifndef IDENTIFYMACHINETYPETASK_H_
#define IDENTIFYMACHINETYPETASK_H_

#include <tasks/SimpleTask.h>
#include "arenaState/actors/Machine.h"


class IdentifyMachineTypeTask: public SimpleTask {
public:
	IdentifyMachineTypeTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs);
	virtual ~IdentifyMachineTypeTask();
protected:
	std::string m_machineName;

	virtual bool checkInitialConditionsImpl();

	virtual bool checkFailConditions();

	virtual void executeCancelation();
	virtual std::string executeCancelationImpl();

	virtual bool checkCompletionConditions();
	virtual void executePostCompletion() ;


	virtual void executeImpl();
};

#endif /* IDENTIFYMACHINETYPETASK_H_ */
