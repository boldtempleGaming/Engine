#include "Collider.h"

std::unordered_map<Object* ,Collider*> Collider::_Colliders;

Collider::Collider(Object *obj){
    SetOwner(obj);
}

Collider::~Collider(){

}

void Collider::ProcessCollisions() {
    static Vec2 dif;
    static Vec2 vel;

    int size = _Colliders.size();

    static std::unordered_set<Collider*> collided;
    collided.reserve(size);

    for(auto it_i : _Colliders){
        auto collider_i = it_i.second;

        #define I_POS_X (collider_i->_owner->GetGlobalPos().x + collider_i->_offset.x)
        #define I_POS_Y (collider_i->_owner->GetGlobalPos().y + collider_i->_offset.y)
        #define I_SIZE_W (collider_i->_size.x)
        #define I_SIZE_H (collider_i->_size.y)

        #define J_POS_X (collider_j->_owner->GetGlobalPos().x + collider_j->_offset.x)
        #define J_POS_Y (collider_j->_owner->GetGlobalPos().y + collider_j->_offset.y)
        #define J_SIZE_W (collider_j->_size.x)
        #define J_SIZE_H (collider_j->_size.y)

        collided.clear();

        if(collider_i->_is_static){
            continue;
        }

        //Vec2 prev_pos_i = collider_i->_owner->GetGlobalPos();
        collider_i->_owner->Move(Vec2(collider_i->_owner->GetVel().x, 0));
        vel = collider_i->_owner->GetVel();

        for(auto it_j : _Colliders){
            if(it_i.first == it_j.first) continue;
            auto collider_j = it_j.second;

            if(collider_i->CheckCollision(collider_j, dif)){

                collided.insert(it_j.second);

                switch(collider_j->_type){
                case COLLIDER_RECT:
                    if(collider_i->_owner->GetVel().x >= 0) {
                        dif.x = J_POS_X - (I_POS_X + I_SIZE_W);
                    }else{
                        dif.x = (J_POS_X + J_SIZE_W) - I_POS_X;
                    }

                    collider_i->_owner->Move(Vec2(dif.x, 0));

                    vel.x = 0;
                    collider_i->_owner->SetVel(vel);

                    break;

                case COLLIDER_CIRCLE:

                    break;
                }

                collider_i->_owner->OnCollide(collider_j->_owner);
            }
        }

        collider_i->_owner->Move(Vec2(0, collider_i->_owner->GetVel().y));
        for(auto it_j : _Colliders) {
            if(it_i.first == it_j.first) continue;
            auto collider_j = it_j.second;

            if(collided.find(it_j.second) == collided.end())
            if(collider_i->CheckCollision(collider_j, dif)){

                switch(collider_j->_type){
                case COLLIDER_RECT:
                    if(collider_i->_owner->GetVel().y >= 0) {
                        dif.y = J_POS_Y - (I_POS_Y + I_SIZE_H);
                    }else{
                        dif.y = (J_POS_Y + J_SIZE_H) - I_POS_Y;
                    }

                    collider_i->_owner->Move(Vec2(0, dif.y));

                    vel.y = 0;
                    collider_i->_owner->SetVel(vel);

                    break;

                case COLLIDER_CIRCLE:

                    break;
                }

                collider_i->_owner->OnCollide(collider_j->_owner);

            }
        }
    }
}

Collider* Collider::RegisterObject(Object* obj, const Vec2& offset, const Vec2& size, bool is_static) {
    if(obj != nullptr){
        auto iter = Find(obj);
        if(iter == _Colliders.end()){
            Collider* coll = new Collider(obj);

            coll->_offset = offset;
            coll->_size = size;
            coll->_is_static = is_static;

            _Colliders[obj] = coll;

            return coll;
        }else{
            return iter->second;
        }
    }

    return nullptr;
}

void Collider::UnregisterObject(Object *obj) {
    if(obj != nullptr){
        auto iter = Find(obj);
        if(iter != _Colliders.end()){
            delete(iter->second);
            _Colliders.erase(iter);
        }
    }
}

Collider* Collider::GetCollider(Object* obj){
    if(obj != nullptr){
        auto iter = Find(obj);
        if(iter != _Colliders.end()){
            return(iter->second);
        }
    }
    return nullptr;
}

void Collider::SetStatic(bool is_static){
    _is_static = is_static;
}

void Collider::SetCircleRadius(float radius){
    _radius = radius;
}

float Collider::GetCircleRadius(){
    return _radius;
}

void Collider::SetOwner(Object* owner){
    _owner = owner;
}

Object* Collider::GetOwner(){
    return _owner;
}

Collider::TYPE_COLLIDER Collider::GetType(){
    return _type;
}

void Collider::SetType(Collider::TYPE_COLLIDER type){
       _type = type;
}

bool Collider::CheckCollision(Collider* col, Vec2& dif){
    if(_owner == nullptr || col->_owner == nullptr){
        return false;
    }

    static Vec2 this_pos;
    static Vec2 col_pos;

    this_pos = _owner->GetGlobalPos() + _offset;
    col_pos = col->_owner->GetGlobalPos() + col->_offset;

    //RECT VS RECT
    if(_type == COLLIDER_RECT && _type == col->_type){
        if(this_pos.x >= col_pos.x + col->_size.x || this_pos.x + _size.x <= col_pos.x) return false;
        if(this_pos.y >= col_pos.y + col->_size.y || this_pos.y + _size.y <= col_pos.y) return false;

        return true;
    }
    //CIRCLE VS CIRCLE
    else if(_type == COLLIDER_CIRCLE && _type == col->_type){
        return (this_pos - col_pos).GetLength() >= this->_radius + col->_radius;
    }
    //CIRCLE VS RECT
    else{
        static Vec2 dist;
        static Vec2 rect_center;
        static Vec2 rect_half_size;
        static Vec2 circle_pos;
        static int radius;
        static float dx;
        static float dy;

        if(_type == COLLIDER_CIRCLE){
            rect_half_size = col->_size * 0.5f;
            rect_center = col->GetOwner()->GetGlobalPos() + col->_offset + rect_half_size;
            circle_pos = this_pos;
            radius = col->_radius;
        }
        else{
            rect_half_size = this->_size * 0.5f;
            rect_center = this_pos + rect_half_size;
            circle_pos = col->GetOwner()->GetGlobalPos() + col->_offset;
            radius = col->_radius;
        }

        dist.x = fabs(circle_pos.x - rect_center.x);
        dist.y = fabs(circle_pos.y - rect_center.y);

        if (dist.x > (rect_half_size.x + radius)) { return false; }
        if (dist.y > (rect_half_size.y + radius)) { return false; }

        if (dist.x <= (rect_half_size.x)) { return true; }
        if (dist.x <= (rect_half_size.y)) { return true; }

        dx = dist.x - rect_half_size.x;
        dy = dist.y - rect_half_size.y;

        return dx*dx + dy*dy <= (radius*radius);
    }

    return false;
}

std::unordered_map<Object*, Collider*>::iterator Collider::Find(Object *obj) {
    if(obj == nullptr){
        return _Colliders.end();
    }

    return _Colliders.find(obj);
}
