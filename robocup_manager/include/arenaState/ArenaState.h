/**
 * \file 		ArenaState.h
 *
 * \brief		Contient l'état de l'aire de jeu pendant un match
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#ifndef ARENASTATE_H_
#define ARENASTATE_H_

#include <vector>
#include <map>

#include "arenaState/actors/Machine.h"
#include "arenaState/actors/Robotino.h"
#include "arenaState/zones/Zone.h"
#include "arenaState/zones/InputStorage.h"
#include "arenaState/actors/Puck.h"

#include "refBoxComm/ExplorationSignal.h"

class ArenaState {
public:
	ArenaState();
	virtual ~ArenaState();

	Robotino *getRobotino(std::string name)
	{
		return m_robotinos[name];
	}

	std::map<std::string, Machine*> &getMachines()
	{
		return m_machines;
	}

	void addMachine(std::string id, Machine* m)
	{
		m_machines[id] = m;
	}

	std::map<std::string, refBoxComm::ExplorationSignal> &getSignals()
	{
		return m_signals;
	}

	void addSignal(std::string type, refBoxComm::ExplorationSignal ls)
	{
		m_signals[type] = ls;
	}


protected:
	std::map<std::string, Machine*> m_machines;

	std::map<std::string, Robotino*> m_robotinos;

	std::map<std::string, refBoxComm::ExplorationSignal> m_signals;

	InputStorage m_cyanStorage;
	InputStorage m_magentaStorage;

	std::vector<Puck*> m_pucks;
};

#endif /* ARENASTATE_H_ */
