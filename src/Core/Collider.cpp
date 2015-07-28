//
// Created by snickers on 14.05.15.
//

#include "Collider.h"

Collider::Collider(){

}

Collider::~Collider(){

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

bool Collider::CheckCollision(Collider* col){
    if(!_owner || !col->_owner){
        return false;
    }

    //RECT AND RECT
    if(_type == COLLIDER_RECT && _type == col->_type){

        Vec2 this_pos = _owner->GetPos();
        Vec2 this_size = _owner->GetSize();

        Vec2 col_pos = col->GetOwner()->GetPos();
        Vec2 col_size = col->GetOwner()->GetSize();

        return !(this_pos.x > col_pos.x + col_size.x ||
                this_pos.x + this_size.x < col_pos.x ||
                this_pos.y + this_size.y < col_pos.y ||
                this_pos.y > col_pos.y + col_size.y);

    }//CIRCLE AND CIRCLE
    else if(_type == COLLIDER_CIRCLE && _type == col->_type){

    }//CIRCLE AND RECT
    else{

    }
}
