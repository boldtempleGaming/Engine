/*
 * Object.cpp
 *
 *  Created on: 03 March 2015 г.
 *      Author: WinPooh32
 */

#include <Core/Object.h>

std::list<Object*> Object::ObjList;
int Object::_last_id = 0;

Object::Object() {
	_owner = nullptr;
	_id = _last_id++;
	_type = OBJ_NONE;
}

Object::~Object() {
	if (_owner) {
		_owner->Disconnect(this);
	}

	while (!ChildrenList.empty()) {
		auto it = ChildrenList.begin();
		delete (*it);
	}
}

void Object::SetPos(const Vec2& new_pos) {
	_pos = new_pos;

	if (_owner) {
		_global_pos.x = _owner->_global_pos.x + _pos.x;
		_global_pos.y = _owner->_global_pos.y + _pos.y;
	}else{
		_global_pos = _pos;
	}

	if (!ChildrenList.empty())
		MoveChildern();
}

void Object::Move(const Vec2& delta_pos) {
    _pos += delta_pos;

	if (_owner) {
		_global_pos.x = _owner->_global_pos.x + _pos.x;
		_global_pos.y = _owner->_global_pos.y + _pos.y;
	}else{
		_global_pos = _pos;
	}

	if (!ChildrenList.empty())
		MoveChildern();
}

Object* Object::GetOwner() {
	return _owner;
}

void Object::SetOwner(Object* obj) {
	_owner = obj;
}

void Object::Connect(Object* obj) {
	if(obj->_owner != nullptr){
		std::cout << "[Warning!] Object " << obj->_id << " already connected to " << obj->_owner->_id << std::endl;
	}else if (FindChild(obj) == ChildrenList.end()) {
		std::cout << "Object connected: " << obj->_id << std::endl;
		ChildrenList.push_back(obj);
		obj->SetOwner(this);
		obj->Move(Vec2()); // update global pos
	}
}

void Object::Disconnect(Object* obj) {
	ChildrenList.remove(obj);
	obj->SetOwner(nullptr);
}

void Object::SetType(obj_type type) {
	_type = type;
}

const Vec2& Object::GetPos(){
    return _pos;
}

const Vec2& Object::GetGlobalPos(){
    return _global_pos;
}

obj_type Object::GetType() {
	return _type;
}

int Object::GetId(){
    return _id;
}

void Object::MoveChildern() {
	//Vec2 null; // x=0 y=0
	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		(*it)->Move(Vec2());
	}
}

std::list<Object*>::iterator Object::FindChild(Object* obj) {
	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		if ((*it)->_id == obj->_id) {
			return it;
		}
	}
	return ChildrenList.end(); //not found
}

void Object::OnUpdate() {
	UpdateChildren();
}

void Object::OnRender() {
	RenderChildren();
}

void Object::OnCollide(Object* obj) {

}

void Object::UpdateChildren(){
	if (ChildrenList.empty()) {
		return;
	}

	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		(*it)->OnUpdate();
		(*it)->UpdateChildren();
	}
}

void Object::RenderChildren(){
	if (ChildrenList.empty()) {
		return;
	}

	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		(*it)->OnRender();
		(*it)->RenderChildren();
	}
}
