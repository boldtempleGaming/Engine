//
// Created by snickers on 14.05.15.
//

#ifndef ENGINE_COLLIDER_H
#define ENGINE_COLLIDER_H

#include <vector>
#include <algorithm>
#include <cmath>

#include "Core/Vec2.h"
#include "Core/Object.h"

enum TYPE_COLLIDER {
    COLLIDER_RECT = 0,
    COLLIDER_CIRCLE
};

class Collider {
public:
    static void ProcessCollisions();
    static void RegisterObject(Object* obj, Vec2 offset, Vec2 size, bool is_static);
    static void UnregisterObject(Object* obj);
    static Collider* GetCollider(Object* obj);

    void SetCircleRadius(float radius);
    float GetCircleRadius();

    TYPE_COLLIDER GetType();
    void SetType(TYPE_COLLIDER type);

    bool CheckCollision(Collider* col, Vec2& dif);
    //Object* RayCast(const Vec2& begin, const Vec2& end);

    bool _is_static = true;
    Vec2 _offset;
    Vec2 _size;
protected:
    float _radius = 0;

private:
    static std::vector<Collider*> _Colliders;
    static std::vector<Collider*>::iterator Find(Object* obj);

    Object* _owner = nullptr;
    TYPE_COLLIDER  _type = COLLIDER_RECT;

    Collider(Object *obj);
    ~Collider();

    void SetOwner(Object* owner);
    Object* GetOwner();
};

#endif //ENGINE_COLLIDER_H
