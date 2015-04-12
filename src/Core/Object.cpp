/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Core/Object.cpp
!*/

#include <Core/Object.h>

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

    if(_id == _last_id - 1){
        _last_id = 0; // reset when all objects are deleted
    }
}

void Object::SetPos(const Vec2& new_pos) {
	_pos = new_pos;

	if (_owner) {
	    _global_pos = _owner->GetGlobalPos() + GetPos();
	    //_global_pos.x = _owner->_global_pos.x + _pos.x;
	    //_global_pos.y = _owner->_global_pos.y + _pos.y;
	}else{
		_global_pos = _pos;
	}

	if (!ChildrenList.empty())
		MoveChildern(Vec2());
}

void Object::Move(const Vec2& delta_pos) {
    _pos += delta_pos;

	if (_owner) {
	    _global_pos = _owner->GetGlobalPos() + GetPos();
        //_global_pos.x = _owner->_global_pos.x + _pos.x;
        //_global_pos.y = _owner->_global_pos.y + _pos.y;
	}else{
		_global_pos = _pos;
	}

	if (!ChildrenList.empty())
		MoveChildern(Vec2());
}

Object* Object::GetOwner() const{
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


std::list<Object*> Object::GetChildrenList(){
    return ChildrenList;
}

const Vec2& Object::GetPos() const{
    return _pos;
}

const Vec2& Object::GetGlobalPos() const{
    return _global_pos;
}

obj_type Object::GetType() const{
	return _type;
}

int Object::GetId() const{
    return _id;
}

void Object::SetSize(const Vec2& size){
    _size = size;
}

const Vec2& Object::GetSize() const{
    return _size;
}

void Object::MoveChildern(const Vec2& delta_pos) {
	for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
		(*it)->Move(delta_pos);
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

//if you want to your object to be clicked call this function
void  Object::CheckClick(){
    //Was clicked mouse buttun
    if(Cursor::button != 0){
        SDL_bool inter;
        SDL_Rect result;
        SDL_Rect obj_rect = {_global_pos.x, _global_pos.y, _size.x, _size.y};
        SDL_Rect cursor_rect = {Cursor::X(), Cursor::Y(), 1, 1};
        //check intersection
        inter = SDL_IntersectRect(&cursor_rect, &obj_rect, &result);
        if(inter == SDL_TRUE){
            //Set to last clicked
            GUI::SetLastCliked(this);
        }
    }
}

void Object::OnUpdate() {
	//UpdateChildren();
}

void Object::OnRender() {
	//RenderChildren();
}

void Object::OnCollide(Object* obj) {

}

void Object::OnClick(){

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
