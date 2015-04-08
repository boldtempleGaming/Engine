/*
 * Bullet.h
 *
 *  Created on: 24 сент. 2014 г.
 *      Author: snickers
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "constants.h"
#include "Core/Entity.h"
#include "Core/Vec2.h"

class Bullet: public Entity {
public:
	Bullet(const Vec2& pos, const Vec2& direct, const double& angle);
	virtual ~Bullet();

	void OnUpdate();
        void OnCollide(Entity* obj);
	void OnRender(const double& interpolation);

	const float RAD = 3.14159265359 / 180;
	const float SPEED = 15;
	Uint32 born_time;
	Vec2 direct;
};

#endif /* BULLET_H_ */
