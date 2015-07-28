//
// Created by snickers on 14.05.15.
//

#ifndef ENGINE_COLLIDER_H
#define ENGINE_COLLIDER_H

#include "Core/Object.h"

enum TYPE_COLLIDER {
    COLLIDER_RECT = 0,
    COLLIDER_CIRCLE
};

class Collider {
public:
    Collider();
    ~Collider();

    void SetCircleRadius(float radius);
    float GetCircleRadius();

    void SetOwner(Object* owner);
    Object* GetOwner();

    TYPE_COLLIDER GetType();
    void SetType(TYPE_COLLIDER type);

    virtual bool CheckCollision(Collider* col);

protected:
    float _radius = 0;

private:
    Object* _owner = nullptr;
    TYPE_COLLIDER  _type = COLLIDER_RECT;
};


#endif //ENGINE_COLLIDER_H
