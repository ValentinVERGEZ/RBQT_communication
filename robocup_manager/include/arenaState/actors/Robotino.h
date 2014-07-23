/**
 * \file 		Robotino.h
 *
 * \brief		Contient l'état d'un robotino pendant un match
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#ifndef ROBOTINO_H_
#define ROBOTINO_H_

#include <string>

#include "Actor.h"
#include "arenaState/actors/Puck.h"


class Robotino : public Actor {
public:
	Robotino(std::string id, int number);
	virtual ~Robotino();


	bool isFree() {
		return m_puck==NULL;
	}

protected:
	std::string m_name;
	int m_number;

	Puck *m_puck;
};

#endif /* ROBOTINO_H_ */
