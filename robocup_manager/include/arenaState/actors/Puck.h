/*
 * Puck.h
 *
 *  Created on: 17 juil. 2014
 *      Author: vincent
 */

#ifndef PUCK_H_
#define PUCK_H_

#include "Actor.h"

enum puckType
{
	S0,
	S1,
	S2,
	P1,
	P2,
	P3,
	Consumed,
	Removed
};


class Puck: public Actor {
public:
	Puck(std::string id);
	virtual ~Puck();
protected:
	bool m_isUsed;
	int m_ownerId;
	puckType m_type;

};

#endif /* PUCK_H_ */
