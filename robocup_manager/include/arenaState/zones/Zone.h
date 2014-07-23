/**
 * \file 		Zone.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-17
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#ifndef ZONE_H_
#define ZONE_H_

#include <string>
#include <list>

#include "arenaState/actors/Puck.h"
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>

class Zone {
public:
	Zone();
	virtual ~Zone();
protected:
	std::string m_name;
	std::list<Puck> m_stock;

	geometry_msgs::Pose m_pose;
	geometry_msgs::Point m_size; //les zones sont des rectangles
};

#endif /* ZONE_H_ */
