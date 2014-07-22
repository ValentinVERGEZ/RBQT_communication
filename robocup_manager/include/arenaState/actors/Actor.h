/**
 * \file 		Actor.h
 *
 * \brief
 *
 * \author		Coelen Vincent (vincent.coelen@polytech-lille.net)
 * \date		2014-07-16
 * \copyright	RBQT, Polytech-Lille
 * \license
 * \version
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include <geometry_msgs/Pose.h>
#include <string>

class Actor {
public:
	Actor(std::string id);
	virtual ~Actor();

	geometry_msgs::Pose getPose()
	{
		return m_pose;
	}

	void updatePosition(geometry_msgs::Pose pose)
	{
		m_pose = pose;
	}

	bool isBusy()
	{
		return m_isBusy;
	}

	void setBusy(bool b)
	{
		m_isBusy = b;
	}

	std::string getActorId()
	{
		return m_id;
	}

protected:
	geometry_msgs::Pose m_pose;

	std::string m_id;
	bool m_isBusy;

};

#endif /* ACTOR_H_ */
