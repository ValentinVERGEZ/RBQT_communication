/**
 * \file 		ReportMachineTask.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-18
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */


#ifndef REPORTMACHINETASK_H_
#define REPORTMACHINETASK_H_

#include <string>
#include <tasks/SimpleTask.h>

class ReportMachineTask: public SimpleTask {
public:
	ReportMachineTask(ArenaState *as, Controller *c, GeneralGameStatus *ggs, std::string machineName);
	virtual ~ReportMachineTask();

	virtual bool checkInitialConditionsImpl();

	virtual bool checkFailConditions();

	virtual std::string executeCancelationImpl();

	virtual bool checkCompletionConditions();
	virtual void executePostCompletion() ;

	virtual void executeImpl();
protected:

	std::string m_machineName;

	bool compareSignals(const refBoxComm::ExplorationSignal &signalMachine,
		   			    const rbqt_lecture_feu_tricolore::LightSignal &signalDetected);
};

#endif /* REPORTMACHINETASK_H_ */
