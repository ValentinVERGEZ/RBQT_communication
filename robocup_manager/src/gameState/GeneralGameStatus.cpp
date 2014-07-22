/**
 * \file 		GeneralGameStatus.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-18
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include "gameState/GeneralGameStatus.h"
#include "rbqt_lecture_feu_tricolore/LightSpec.h"


GeneralGameStatus::GeneralGameStatus() {
	// TODO Auto-generated constructor stub
	m_gs.phase = m_gs.PRE_GAME;
	m_gs.state = m_gs.INIT;
	m_gs.points = 0;
	m_gs.game_time = ros::Time(0, 0);


	rbqt_lecture_feu_tricolore::LightSpec ls;
	ls.color = rbqt_lecture_feu_tricolore::LightSpec::RED;
	ls.state = rbqt_lecture_feu_tricolore::LightSpec::ON;
	m_lastLightSignal.lights.push_back(ls);
	ls.color = rbqt_lecture_feu_tricolore::LightSpec::GREEN;
	ls.state = rbqt_lecture_feu_tricolore::LightSpec::ON;
	m_lastLightSignal.lights.push_back(ls);
	ls.color = rbqt_lecture_feu_tricolore::LightSpec::YELLOW;
	ls.state = rbqt_lecture_feu_tricolore::LightSpec::OFF;
	m_lastLightSignal.lights.push_back(ls);

}

GeneralGameStatus::~GeneralGameStatus() {
	// TODO Auto-generated destructor stub
}

