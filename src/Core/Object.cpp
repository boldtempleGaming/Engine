/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Core/Object.cpp
!*/

#include "Object.h"
#include "IO/Mouse.h" //FIXME WTF? THIS SHIT DOESNT COMPILE IN Object.h

ObjListType Object::DeleteCandidates;
std::unordered_map<std::string, Object*> Object::_AllObjects;
int Object::_last_id = 0;

Object* Object::FindByLabel(const std::string &label){
   auto found = _AllObjects.find(label);

   if(found != _AllObjects.end()){
       return found->second;
   }else{
       return nullptr;
   }
}

Object::Object() {
    SetDefaults();
}

Object::Object(const std::string& label){
   SetDefaults();
   SetLabel(label);
}

Object::~Object() {
    if (_owner) {
        _owner->Disconnect(this);
    }

    while (!_ChildrenList.empty()) {
        auto it = _ChildrenList.begin();
        delete (*it);
    }

    if (_id == _last_id - 1) {
        _last_id = 0; // reset when all objects are deleted
    }

    _AllObjects.erase(_label);
}

void Object::DeleteLater(){
    if(!_delete_later){
        DeleteCandidates.push_back(this);
    }
}

void Object::SetPos(const Vec2& new_pos) {
    _pos = new_pos;

    if (_owner) {
        auto tmp_global = _owner->GetGlobalPos();
        _global_pos = _owner->GetGlobalPos() + GetPos();
    } else {
        _global_pos = _pos;
    }

    if (!_ChildrenList.empty())
        MoveChildern(Vec2::ZERO);
}

void Object::Move(const Vec2& delta_pos) {
    _pos += delta_pos;

    if (_owner) {
        _global_pos = _owner->GetGlobalPos() + GetPos();
    } else {
        _global_pos = _pos;
    }

    if (!_ChildrenList.empty())
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
        std::cout << "[Warning!] Object {label: '"
                  << obj->_label <<"', id: "
                  << obj->_id << "} already connected to {label: '"
                  << this->_label <<"', id: "
                  << this->_id << "} " << std::endl;
    } 
    else if (FindChild(obj) == _ChildrenList.end()) {
        _ChildrenList.push_back(obj);
        obj->SetOwner(this);
        obj->Move(Vec2::ZERO); // update global pos
    }
}

void Object::Disconnect(Object* obj) {
    auto iter = FindChild(obj);
    if (iter != _ChildrenList.end()) {
        _ChildrenList.erase(iter);
        obj->SetOwner(nullptr);
    }
}

void Object::SetType(obj_type type) {
    _type = type;
}

ObjListType Object::GetChildrenList() {
    return _ChildrenList;
}

const Vec2& Object::GetPos() const {
    return _pos;
}

const Vec2& Object::GetGlobalPos() const {
    return _global_pos;
}

void Object::SetLabel(const std::string& label){
    auto found = _AllObjects.find(label);

    if(found != _AllObjects.end()){
        std::cerr << "Label '" << label << " has been already taken!" << std::endl;
    }else{
        _label = label;
        _AllObjects[label] = this;
    }
}

const std::string& Object::GetLabel(){
    return _label;
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

void Object::SetCamera(Camera* cam)
{
    _camera = cam;
}

Camera* Object::GetCamera()
{
    return _camera;
}

void Object::MoveChildern(const Vec2& delta_pos) {
    for (auto it = _ChildrenList.begin(); it != _ChildrenList.end(); it++) {
        (*it)->Move(delta_pos);
    }
}

ObjListType::iterator Object::FindChild(Object* obj) {
    for (auto it = _ChildrenList.begin(); it < _ChildrenList.end(); it++) {
        if ((*it)->_id == obj->_id) {
            return it;
        }
    }
    return _ChildrenList.end(); //not found
}

void Object::SetDefaults(){
    _delete_later = false;
    _owner = nullptr;
    _id = _last_id++;
    _type = OBJ_NONE;
    _ignore_click = false;
}

//if you want your object to be clicked call this function on update tick
void Object::CheckTop() {

    if(Mouse::Intersect(this)){
        const Surface::viewport* view = &(Surface::GetLastViewport());

        if(!_camera){
            SetCamera(Window::GetCamera());
        }

        if(Mouse::Intersect(view->_offset, view->_size, _camera)){
            OnMouse();

            if (!_ignore_click) {
                GUI::SetTopObject(this);
            }

            if(!_ignore_wheel){
                GUI::SetTopWheeled(this);
            }
        }
    }

}

void Object::IgnoreClick(bool ignored) {
    _ignore_click = ignored;
}

void Object::IgnoreWheel(bool ignored){
    _ignore_wheel = ignored;
}

bool Object::IsClickIgnored(){
    return _ignore_click;
}

bool Object::IsWheelIgnored(){
    return _ignore_wheel;
}

bool Object::IsDeletedLater(){
    return _delete_later;
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

void Object::OnTopMouseWheelEvent(){

}

void Object::UpdateChildren() {
    if (_ChildrenList.empty()) {
        return;
    }

    size_t len = _ChildrenList.size();

    for (size_t i = 0; i < len; ++i) {
        _ChildrenList[i]->OnUpdate();
        _ChildrenList[i]->UpdateChildren();
    }
}

void Object::RenderChildren() {
    if (_ChildrenList.empty()) {
        return;
    }

    size_t len = _ChildrenList.size();

    for (size_t i = 0; i < len; ++i) {
        _ChildrenList[i]->OnRender();
        _ChildrenList[i]->RenderChildren();
    }
}
