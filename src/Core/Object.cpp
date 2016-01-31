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
    _ignore_click = false;
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

void Object::SetPos(const Vec2& new_pos) {
    _pos = new_pos;

    if (_owner) {
        _global_pos = _owner->GetGlobalPos() + GetPos();
    } else {
        _global_pos = _pos;
    }

    if (!ChildrenList.empty())
        MoveChildern(Vec2());
}

void Object::Move(const Vec2& delta_pos) {
    _pos += delta_pos;

    if (_owner) {
        _global_pos = _owner->GetGlobalPos() + GetPos();
    } else {
        _global_pos = _pos;
    }

    if (!ChildrenList.empty())
        MoveChildern(Vec2());
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
    for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
        if ((*it)->_id == obj->_id) {
            return it;
        }
    }
    return ChildrenList.end(); //not found
}

//if you want your object to be clicked call this function on update tick

void Object::CheckClick(const Camera* camera) {
    if (!_ignore_click) {
        //Was mouse buttun clicked?
        if (Cursor::button != 0) {
            SDL_Rect result;
            
            SDL_Rect obj_rect = {
                static_cast<int>(GetGlobalPos().x - camera->X()), 
                static_cast<int>(GetGlobalPos().y - camera->Y()), 
                static_cast<int>(_size.x), 
                static_cast<int>(_size.y)
            };
            
            SDL_Rect cursor_rect = {
                static_cast<int>(Cursor::X()), 
                static_cast<int>(Cursor::Y()), 
                1, 
                1
            };
            
            //check intersection
            SDL_bool inter = SDL_IntersectRect(&cursor_rect, &obj_rect, &result);
            if (inter == SDL_TRUE) {
                //Set to last clicked
                GUI::SetLastCliked(this);
            }
        }
    }
}

void Object::IgnoreClick(bool ignore) {
    _ignore_click = ignore;
}

void Object::OnUpdate() {
    //UpdateChildren();
}

void Object::OnRender() {
    //RenderChildren();
}

void Object::OnCollide(Object* obj) {

}

void Object::OnClick() {

}

void Object::UpdateChildren() {
    if (ChildrenList.empty()) {
        return;
    }

    for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
        (*it)->OnUpdate();
        (*it)->UpdateChildren();
    }
}

void Object::RenderChildren() {
    if (ChildrenList.empty()) {
        return;
    }

    for (auto it = ChildrenList.begin(); it != ChildrenList.end(); it++) {
        (*it)->OnRender();
        (*it)->RenderChildren();
    }
}
