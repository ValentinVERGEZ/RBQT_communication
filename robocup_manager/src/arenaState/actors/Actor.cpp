/**
 * \file 		Actor.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */
#include "arenaState/actors/Actor.h"

Actor::Actor(std::string id) {
	m_id = id;
	m_isBusy = false;

}

Actor::~Actor() {
	// TODO Auto-generated destructor stub
}

