/**
 * \file 		geometry_utils.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-21
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#ifndef GEOMETRY_UTILS_H_
#define GEOMETRY_UTILS_H_

#include <geometry_msgs/Pose.h>

#define DELTA_EPSILON 0.3

geometry_msgs::Pose quat_normalize(const geometry_msgs::Pose &p);

bool isSame(float f1, float f2);

bool isSame(const geometry_msgs::Pose &P1, const geometry_msgs::Pose &P2);

#endif /* GEOMETRY_UTILS_H_ */
