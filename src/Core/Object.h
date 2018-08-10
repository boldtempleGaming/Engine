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
#include <unordered_map>

#include <SDL2/SDL.h>

#include "Core/Vec2.h"
#include "Render/Surface.h"
#include "Render/Camera.h"

enum obj_type {
    OBJ_NONE = 0,
    OBJ_ENTITY,
    OBJ_GROUND,
    OBJ_WIDGET
};

class ScrollArea;
class Object;

typedef std::vector<Object*> ObjListType;

class Object {
public:
    static ObjListType DeleteCandidates;

    static Object* FindByLabel(const std::string& label);

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

    void SetLabel(const std::string& label);
    const std::string& GetLabel();

    void SetVel(const Vec2& vel);
    Vec2 GetVel() const;

    obj_type GetType() const;
    int GetId() const;

    void SetSize(const Vec2& size);
    const Vec2& GetSize() const;

    void SetCamera(Camera* cam);
    Camera* GetCamera();

    //Check top object for mouse events
    void CheckTop();

    void IgnoreClick(bool ignored);
    void IgnoreWheel(bool ignored);

    bool IsClickIgnored();
    bool IsWheelIgnored();

    bool IsDeletedLater();

    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnCollide(Object* obj);
    virtual void OnMouse();
    virtual void OnTopMouseEvent();
    virtual void OnTopMouseWheelEvent();

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
    ObjListType _ChildrenList;

private:
    friend ScrollArea;

    static int _last_id; //last created object id
    static std::unordered_map<std::string, Object*> _AllObjects;

    bool _delete_later;
    bool _ignore_click;
    bool _ignore_wheel;
    Vec2 _pos;
    Vec2 _size;
    Vec2 _global_pos;
    Vec2 _vel;

    Camera* _camera = nullptr;

    SDL_Rect _draw_rect;

    int _id;
    obj_type _type;
    Object* _owner;

    std::string _label;

    void SetOwner(Object* obj);

    /**
     * Move children when parent is moved
     */
    void MoveChildern(const Vec2& delta_pos);

    ObjListType::iterator FindChild(Object* obj);

    void SetDefaults();
};

#endif /* SRC_CORE_OBJECT_H_ */
