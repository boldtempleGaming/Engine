#include "Collider.h"
std::vector<Collider*> Collider::_Colliders;

Collider::Collider(Object *obj){
    SetOwner(obj);
}

Collider::~Collider(){

}

void Collider::ProcessCollisions() {
    Vec2 dif;
    Vec2 vel;

    int size = _Colliders.size();
    for(int i = 0; i < size; ++i){


        #define I_POS_X (_Colliders[i]->_owner->GetGlobalPos().x + _Colliders[i]->_offset.x)
        #define I_POS_Y (_Colliders[i]->_owner->GetGlobalPos().y + _Colliders[i]->_offset.y)
        #define I_SIZE_W (_Colliders[i]->_size.x)
        #define I_SIZE_H (_Colliders[i]->_size.y)

        #define J_POS_X (_Colliders[j]->_owner->GetGlobalPos().x + _Colliders[j]->_offset.x)
        #define J_POS_Y (_Colliders[j]->_owner->GetGlobalPos().y + _Colliders[j]->_offset.y)
        #define J_SIZE_W (_Colliders[j]->_size.x)
        #define J_SIZE_H (_Colliders[j]->_size.y)


        //Vec2 prev_pos_i = _Colliders[i]->_owner->GetGlobalPos();
        _Colliders[i]->_owner->Move(Vec2(_Colliders[i]->_owner->GetVel().x, 0));
        vel = _Colliders[i]->_owner->GetVel();

        if(_Colliders[i]->_is_static){
            _Colliders[i]->_owner->SetVel(vel);
            continue;
        }

        for(int j = i + 1; j < size; ++j){

            if(_Colliders[i]->CheckCollision(_Colliders[j], dif)){
                if(_Colliders[i]->_owner->GetVel().x >= 0) {
                    dif.x = J_POS_X - (I_POS_X + I_SIZE_W);
                }else{
                    dif.x = (J_POS_X + J_SIZE_W) - I_POS_X;
                }

                _Colliders[i]->_owner->Move(Vec2(dif.x, 0));

                vel.x = 0;
                _Colliders[i]->_owner->SetVel(vel);

                _Colliders[i]->_owner->OnCollide(_Colliders[j]->_owner);
            }
        }

        _Colliders[i]->_owner->Move(Vec2(0, _Colliders[i]->_owner->GetVel().y));
        for(int j = i + 1; j < size; ++j) {
            if(_Colliders[i]->CheckCollision(_Colliders[j], dif)){

                if(_Colliders[i]->_owner->GetVel().y >= 0) {
                    dif.y = J_POS_Y - (I_POS_Y + I_SIZE_H);
                }else{
                    dif.y = (J_POS_Y + J_SIZE_H) - I_POS_Y;
                }

                _Colliders[i]->_owner->Move(Vec2(0, dif.y));

                vel.y = 0;
                _Colliders[i]->_owner->SetVel(vel);

                _Colliders[i]->_owner->OnCollide(_Colliders[j]->_owner);

            }
        }
    }
}

void Collider::RegisterObject(Object* obj, Vec2 offset, Vec2 size, bool is_static) {
    if(obj != nullptr){
        if(Find(obj) == _Colliders.end()){
            Collider* coll = new Collider(obj);

            coll->_offset = offset;
            coll->_size = size;
            coll->_is_static = is_static;

            _Colliders.push_back(coll);
        }
    }
}

void Collider::UnregisterObject(Object *obj) {
    if(obj != nullptr){
        auto iter = Find(obj);
        if(iter != _Colliders.end()){
            delete(*iter);
            _Colliders.erase(iter);
        }
    }
}

Collider* Collider::GetCollider(Object* obj){
    if(obj != nullptr){
        auto iter = Find(obj);
        if(iter != _Colliders.end()){
            return(*iter);
        }
    }
    return nullptr;
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

TYPE_COLLIDER Collider::GetType(){
    return _type;
}

void Collider::SetType(TYPE_COLLIDER type){
       _type = type;
}

bool Collider::CheckCollision(Collider* col, Vec2& dif){
    if(!_owner || !col->_owner){
        return false;
    }

    //RECT AND RECT
    if(_type == COLLIDER_RECT && _type == col->_type){

        Vec2 this_pos = _owner->GetGlobalPos() + _offset;
        //Vec2 this_size = _owner->GetSize();

        Vec2 col_pos = col->GetOwner()->GetGlobalPos() + col->_offset;
        //Vec2 col_size = col->GetOwner()->GetSize();

        if(this_pos.x >= col_pos.x + col->_size.x || this_pos.x + _size.x <= col_pos.x) return false;
        if(this_pos.y >= col_pos.y + col->_size.y || this_pos.y + _size.y <= col_pos.y) return false;
        return true;
    }//CIRCLE AND CIRCLE
    else if(_type == COLLIDER_CIRCLE && _type == col->_type){

    }//CIRCLE AND RECT
    else{

    }

    return false;
}

std::vector<Collider*>::iterator Collider::Find(Object *obj) {
    if(obj == nullptr){
        return _Colliders.end();
    }

    auto it = _Colliders.begin();
    for(; it != _Colliders.end(); it++){
        if( (*it)->_owner != nullptr ){
            if((*it)->_owner == obj){
                break; // collider was founded
            }
        }else{
            delete(*it);
            _Colliders.erase(it);
        }
    }

    return it;
}
