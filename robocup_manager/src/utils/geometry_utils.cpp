/**
 * \file 		geometry_utils.cpp
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-21
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#include <cmath>
#include <tf/transform_datatypes.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Pose.h>

#include "utils/geometry_utils.h"

geometry_msgs::Pose quat_normalize(const geometry_msgs::Pose &p)
{
	geometry_msgs::Pose r = p;
	r.orientation.w = sqrt(1 - pow(r.orientation.x, 2) - pow(r.orientation.y, 2)  -  pow(r.orientation.z, 2));
	return r;
}


bool isSame(float f1, float f2)
{
	return fabs(f1 - f2) < DELTA_EPSILON;
}

bool isSame(const geometry_msgs::Pose &P1, const geometry_msgs::Pose &P2)
{
	geometry_msgs::Pose P1n = quat_normalize(P1);
	geometry_msgs::Pose P2n = quat_normalize(P2);
	double y1 = tf::getYaw(P1n.orientation);
	double y2 = tf::getYaw(P2n.orientation);

	return (isSame(P1n.position.x, P2n.position.x) &&
			isSame(P1n.position.y, P2n.position.y) &&
			isSame(y1, y2));
}


