/**
 * \file 		Robotino.cpp
 *
 * \brief		Contient l'état d'un robotino pendant un match
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include "arenaState/actors/Robotino.h"

Robotino::Robotino(std::string id, int number): Actor(id) {
	m_number = number;
	m_puck = NULL;
}

Robotino::~Robotino() {
	// TODO Auto-generated destructor stub
}

