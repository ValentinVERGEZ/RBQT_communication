/**
 * \file 		Machine.h
 *
 * \brief		Contient l'état d'une machine pendant un match
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */


#ifndef MACHINE_H_
#define MACHINE_H_

#include "Actor.h"
#include "arenaState/zones/MachineStorage.h"
#include "arenaState/actors/Puck.h"

enum machineType
{
	T1,
	T2,
	T3,
	T4,
	T5,
	Delivry,
	Recycling,
	UNKNOWN
};

enum machineState
{
	IDLE,
	WORKING,
	DOWN
};


class Machine : public Actor {
public:
	Machine(std::string id);
	virtual ~Machine();

	void setType(machineType t)
	{
		m_type = t;
	}
	void setType(std::string t)
	{
		if (t=="T1")
		{ m_type = T1; }
		else if (t=="T2")
		{ m_type = T2; }
		else if (t=="T3")
		{ m_type = T3; }
		else if (t=="T4")
		{ m_type = T4; }
		else if (t=="T5")
		{ m_type = T5; }
		else if (t=="Delivry")
		{ m_type = Delivry; }
		else if (t=="Recycling")
		{ m_type = Recycling; }
		else
		{ m_type = UNKNOWN;}
	}
protected:
	machineType m_type;
	machineState m_state;

	MachineStorage m_zone;

	Puck *m_puckUnderRFID;

};

#endif /* MACHINE_H_ */
