/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Core/Object.cpp
!*/

#include "Object.h"
#include <IO/Mouse.h> //FIXME WTF? THIS SHIT DOESNT COMPILE IN Object.h

ObjListType Object::DeleteCandidates;
int Object::_last_id = 0;

Object::Object() {
    SetDefaults();
}

Object::Object(const std::string& label){
   SetDefaults();
   _label = label;
}

Object::~Object() {
    if (_owner) {
        _owner->Disconnect(this);
    }

    while (!ChildrenList.empty()) {
        auto it = ChildrenList.begin();
        delete (*it);
    }

    if (_id == _last_id - 1) {
        _last_id = 0; // reset when all objects are deleted
    }
}

void Object::DeleteLater(){
    if(!_delete_later){
        DeleteCandidates.push_back(this);
    }
}

void Object::SetPos(const Vec2& new_pos) {
    _pos = new_pos;

    if (_owner) {
        _global_pos = _owner->GetGlobalPos() + GetPos();
    } else {
        _global_pos = _pos;
    }

    if (!ChildrenList.empty())
        MoveChildern(Vec2::ZERO);
}

void Object::Move(const Vec2& delta_pos) {
    _pos += delta_pos;

    if (_owner) {
        _global_pos = _owner->GetGlobalPos() + GetPos();
    } else {
        _global_pos = _pos;
    }

    if (!ChildrenList.empty())
        MoveChildern(Vec2::ZERO);
}

Object* Object::GetOwner() const {
    return _owner;
}

void Object::SetOwner(Object* obj) {
    _owner = obj;
}

void Object::Connect(Object* obj) {
    if (obj->_owner != nullptr) {
        std::cout << "[Warning!] Object " << obj->_id << " already connected to " << obj->_owner->_id << std::endl;
    } 
    else if (FindChild(obj) == ChildrenList.end()) {
        ChildrenList.push_back(obj);
        obj->SetOwner(this);
        obj->Move(Vec2::ZERO); // update global pos
    }
}

void Object::Disconnect(Object* obj) {
    auto iter = FindChild(obj);
    if (iter != ChildrenList.end()) {
        ChildrenList.erase(iter);
        obj->SetOwner(nullptr);
    }
}

void Object::SetType(obj_type type) {
    _type = type;
}

ObjListType Object::GetChildrenList() {
    return ChildrenList;
}

const Vec2& Object::GetPos() const {
    return _pos;
}

const Vec2& Object::GetGlobalPos() const {
    return _global_pos;
}

void Object::SetVel(const Vec2 &vel) {
    _vel = vel;
}

Vec2 Object::GetVel() const {
    if (_owner != nullptr) {
        return _owner->GetVel() + _vel;
    } else {
        return _vel;
    }
}

obj_type Object::GetType() const {
    return _type;
}

int Object::GetId() const {
    return _id;
}

const std::string& Object::GetLabel(){
    return _label;
}

void Object::SetSize(const Vec2& size) {
    _size = size;
}

const Vec2& Object::GetSize() const {
    return _size;
}

void Object::MoveChildern(const Vec2& delta_pos) {
    for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
        (*it)->Move(delta_pos);
    }
}

ObjListType::iterator Object::FindChild(Object* obj) {
    for (auto it = ChildrenList.begin(); it < ChildrenList.end(); it++) {
        if ((*it)->_id == obj->_id) {
            return it;
        }
    }
    return ChildrenList.end(); //not found
}

void Object::SetDefaults(){
    _delete_later = false;
    _owner = nullptr;
    _id = _last_id++;
    _type = OBJ_NONE;
    _ignore_click = false;
}

//if you want your object to be clicked call this function on update tick
void Object::CheckTop(const Camera* camera) {
    if (!_ignore_click) {
        if(Mouse::Intersect(this)){
            if(camera->InView(Mouse::GetPos(), Vec2(1,1))){
                OnMouse();
                GUI::SetTopObject(this);
            }
        }
    }
}

void Object::IgnoreClick(bool ignored) {
    _ignore_click = ignored;
}

bool Object::IsClickIgnored(){
    return _ignore_click;
}

void Object::OnUpdate() {
    //UpdateChildren();
}

void Object::OnRender() {
    //RenderChildren();
}

void Object::OnCollide(Object* obj) {

}

void Object::OnMouse(){

}

void Object::OnTopMouseEvent() {

}

void Object::UpdateChildren() {
    if (ChildrenList.empty()) {
        return;
    }

    size_t len = ChildrenList.size();

    for (size_t i = 0; i < len; ++i) {
        ChildrenList[i]->OnUpdate();
        ChildrenList[i]->UpdateChildren();
    }
}

void Object::RenderChildren() {
    if (ChildrenList.empty()) {
        return;
    }

    size_t len = ChildrenList.size();

    for (size_t i = 0; i < len; ++i) {
        ChildrenList[i]->OnRender();
        ChildrenList[i]->RenderChildren();
    }
}
