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
#include "geometry_msgs/Pose.h"
#include <tf/transform_datatypes.h>

ArenaState::ArenaState() {
	// TODO Auto-generated constructor stub


	//create robotino
	m_robotinos["R1"] = new Robotino("R1", 1);
	m_robotinos["R2"] = new Robotino("R2", 2);
	m_robotinos["R3"] = new Robotino("R3", 3);

	//generate pose for the exploration phase
	generateExplorationPoses(m_explorationsPoses);
}

ArenaState::~ArenaState() {
	// TODO Auto-generated destructor stub

	//TODO detruire tous les elements
}


void ArenaState::generateExplorationPoses(std::map<std::string, geometry_msgs::Pose> &ExplorationPoses)
{
	geometry_msgs::Pose Pose;

	Pose = calculPoint (1, 4, -M_PI/2.0);
	ExplorationPoses["M1"] = Pose;

	Pose = calculPoint (1, 6, M_PI/2.0);
	ExplorationPoses["M2"] = Pose;

	Pose = calculPoint (3, 4, -M_PI/2.0);
	ExplorationPoses["M3"] = Pose;

	Pose = calculPoint (3, 6, M_PI/2.0);
	ExplorationPoses["M4"] = Pose;

	Pose = calculPoint (3, 8, M_PI/2.0);
	ExplorationPoses["M5"] = Pose;

	Pose = calculPoint (5, 4, -M_PI/2.0);
	ExplorationPoses["M6"] = Pose;

	Pose = calculPoint (5, 8, M_PI/2.0);
	ExplorationPoses["M7"] = Pose;

	Pose = calculPoint (5, 10, M_PI/2.0);
	ExplorationPoses["M8"] = Pose;

	Pose = calculPoint (7, 4, -M_PI/2.0);
	ExplorationPoses["M9"] = Pose;

	Pose = calculPoint (7, 6, -M_PI/2.0);
	ExplorationPoses["M10"] = Pose;

	Pose = calculPoint (7, 8, M_PI/2.0);
	ExplorationPoses["M11"] = Pose;

	Pose = calculPoint (9, 8, M_PI/2.0);
	ExplorationPoses["M12"] = Pose;

	/******************************/

	Pose = calculPoint (-1, 4, -M_PI/2.0);
	ExplorationPoses["M13"] = Pose;

	Pose = calculPoint (-1, 6, M_PI/2.0);
	ExplorationPoses["M14"] = Pose;

	Pose = calculPoint (-3, 4, -M_PI/2.0);
	ExplorationPoses["M15"] = Pose;

	Pose = calculPoint (-3, 6, M_PI/2.0);
	ExplorationPoses["M16"] = Pose;

	Pose = calculPoint (-3, 8, M_PI/2.0);
	ExplorationPoses["M17"] = Pose;

	Pose = calculPoint (-5, 4, -M_PI/2.0);
	ExplorationPoses["M18"] = Pose;

	Pose = calculPoint (-5, 8, M_PI/2.0);
	ExplorationPoses["M19"] = Pose;

	Pose = calculPoint (-5, 10, M_PI/2.0);
	ExplorationPoses["M20"] = Pose;

	Pose = calculPoint (-7, 4, -M_PI/2.0);
	ExplorationPoses["M21"] = Pose;

	Pose = calculPoint (-7, 6, -M_PI/2.0);
	ExplorationPoses["M22"] = Pose;

	Pose = calculPoint (-7, 8, M_PI/2.0);
	ExplorationPoses["M23"] = Pose;

	Pose = calculPoint (-9, 8, M_PI/2.0);
	ExplorationPoses["M24"] = Pose;
}

//fonction qui calcule la pose réelle en fonction d'un n° de ligne,
//d'un n° de colonne et d'un angle en radian
geometry_msgs::Pose ArenaState::calculPoint(int xgrille, int ygrille, float yaw)
{
    geometry_msgs::Pose P;

    P.position.x = (float)xgrille * OFFSET;
    P.position.y = (float)ygrille * OFFSET;
    P.orientation =  tf::createQuaternionMsgFromYaw(yaw);

    return P;
}

