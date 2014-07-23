/**
 * \file 		GeneralGameStatus.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-18
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */
#ifndef GENERALGAMESTATUS_H_
#define GENERALGAMESTATUS_H_

#include <list>

#include "refBoxComm/GameState.h"
#include "refBoxComm/ExplorationInfo.h"
#include "executePath/EdCState.h"
#include "rbqt_lecture_feu_tricolore/LightSignal.h"

class GeneralGameStatus {
public:
	GeneralGameStatus();
	virtual ~GeneralGameStatus();

	void updateGameState(const refBoxComm::GameState &gs)
	{
		m_gs = gs;
	}

	const refBoxComm::GameState &getGameState()
	{
		return m_gs;
	}

	void updateExplorationInfo(const refBoxComm::ExplorationInfo &ei)
	{
		m_ei = ei;
	}

	const refBoxComm::ExplorationInfo &getExplorationInfo()
	{
		return m_ei;
	}

	void updateEdCState(const executePath::EdCState &edcs)
	{
		m_edcs = edcs;
	}

	const executePath::EdCState &getEdCState()
	{
		return m_edcs;
	}

	void updateActualSignal(const rbqt_lecture_feu_tricolore::LightSignal &ls)
	{
		m_lastLightSignal = ls;
	}

	rbqt_lecture_feu_tricolore::LightSignal getActualSignal()
	{
		return m_lastLightSignal;
	}


protected:
	refBoxComm::GameState m_gs;
	refBoxComm::ExplorationInfo m_ei;

	executePath::EdCState m_edcs;
	rbqt_lecture_feu_tricolore::LightSignal m_lastLightSignal;

	std::list<int> m_lastPathId;


};

#endif /* GENERALGAMESTATUS_H_ */
