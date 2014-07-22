/**
 * \file 		Machine.cpp
 *
 * \brief		Contient l'état d'une machine pendant un match
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */
#include "arenaState/actors/Machine.h"

Machine::Machine(std::string id):Actor(id)
{
	m_type = UNKNOWN;
	m_state = IDLE;
	m_puckUnderRFID = NULL;

	//ajouter calcul de la zone en fonction de la position
}

Machine::~Machine() {
	// TODO Auto-generated destructor stub
}

