/**
 * \file 		ArenaState.cpp
 *
 * \brief		Contient l'état de l'aire de jeu pendant un match
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include "arenaState/ArenaState.h"

ArenaState::ArenaState() {
	// TODO Auto-generated constructor stub


	//create robotino
	m_robotinos["R1"] = new Robotino("R1", 1);
	m_robotinos["R2"] = new Robotino("R2", 2);
	m_robotinos["R3"] = new Robotino("R3", 3);

}

ArenaState::~ArenaState() {
	// TODO Auto-generated destructor stub

	//TODO detruire tous les elements
}

