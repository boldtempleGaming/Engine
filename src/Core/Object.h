/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Core/Object.h
!*/

#ifndef SRC_CORE_OBJECT_H_
#define SRC_CORE_OBJECT_H_

#include <iostream>
#include <list>
#include <vector>

#include <SDL2/SDL.h>

#include <Core/Vec2.h>
#include <Render/Camera.h>

enum obj_type {
    OBJ_NONE = 0,
    OBJ_ENTITY,
    OBJ_GROUND,
    OBJ_WIDGET
};

class ScrollArea; // объявление класса
class Object;

typedef std::vector<Object*> ObjListType;

class Object {
public:
    static ObjListType DeleteCandidates;

    Object();
    Object(const std::string& label);
    virtual ~Object();

    void DeleteLater();

    /**
     * Set new Vec2 position
     */
    virtual void SetPos(const Vec2& new_pos);
    /**
     * Move object on Vec2 delta position (dx, dy)
     */
    virtual void Move(const Vec2& delta_pos);

    Object* GetOwner() const;
    virtual void Connect(Object* obj);
    virtual void Disconnect(Object* obj);

    virtual const Vec2& GetPos() const;
    virtual const Vec2& GetGlobalPos() const;

    void SetVel(const Vec2& vel);
    Vec2 GetVel() const;

    obj_type GetType() const;
    int GetId() const;
    const std::string& GetLabel();

    void SetSize(const Vec2& size);
    const Vec2& GetSize() const;

    //if you want to your object to be clicked call this function
    void CheckClick(const Camera* camera);
    void IgnoreClick(bool ignore);

    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnCollide(Object* obj);
    virtual void OnClick();

    /**
     * Update all children
     */
    virtual void UpdateChildren();
    /**
     * Render all children
     */
    virtual void RenderChildren();

protected:
    void SetType(obj_type type);
    ObjListType GetChildrenList();

private:
    friend ScrollArea;

    static int _last_id; //last created object id

    ObjListType ChildrenList;
    //std::list< /*subsystem type*/ > _subsystems; //TODO subsystem list

    bool _delete_later;
    bool _ignore_click;
    Vec2 _pos;
    Vec2 _size;
    Vec2 _global_pos;
    Vec2 _vel;
    SDL_Rect _draw_rect;

    int _id;
    std::string _label;
    obj_type _type;
    Object* _owner;

    void SetOwner(Object* obj);

    /**
     * Move children when parent is moved
     */
    void MoveChildern(const Vec2& delta_pos);

    ObjListType::iterator FindChild(Object* obj);

    void SetDefaults();
};

#endif /* SRC_CORE_OBJECT_H_ */
