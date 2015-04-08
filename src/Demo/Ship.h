/*
 * Ship.h
 *
 *  Created on: 17 сент. 2014 г.
 *      Author: snickers
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "Core/Entity.h"
#include "Core/Vec2.h"
#include "IO/KeyBoard.h"
#include "Core/Timer.h"

#include "Bullet.h"

class Ship: public Entity {
public:
	Ship();
	virtual ~Ship();
	void OnUpdate();
	void OnRender(const double& interpolation);
	void Rotate(const int& da);
	void OnCollide(Entity* ent);

	const Uint8 MAX_SPEED = 20;
	KeyBoard keyb;
	float speed;
	Vec2 direct;
	Timer gun_timer;
};

#endif /* SHIP_H_ */
