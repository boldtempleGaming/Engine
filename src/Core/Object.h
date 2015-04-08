/*
 * Object.h
 *
 *  Created on: 03 March 2015 г.
 *      Author: WinPooh32
 */

#ifndef SRC_CORE_OBJECT_H_
#define SRC_CORE_OBJECT_H_

#include <iostream>
#include <list>
#include <vector>

#include <SDL2/SDL.h>

#include <Core/Vec2.h>
#include <Render/Surface.h>

enum obj_type{
	OBJ_NONE = 0,
	OBJ_ENTITY,
	OBJ_GROUND,
	OBJ_WIDGET
};

/*
enum obj_draw_layer{
//TODO objects draw layers// Outside?
};
*/

class ScrollArea; // объявление класса

class Object {
public:
	Object();
	virtual ~Object();

	/**
	 * Set new Vec2 position
	 */
	void SetPos(const Vec2& new_pos);
    /**
     * Move object on Vec2 delta position (dx, dy)
     */
	void Move(const Vec2& delta_pos);

	Object* GetOwner();
	void Connect(Object* obj);
	void Disconnect(Object* obj);

	const Vec2& GetPos();
	const Vec2& GetGlobalPos();
	obj_type GetType();
	int GetId();

	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnCollide(Object* obj);

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
    std::list<Object*> GetChildrenList();

private:
    friend ScrollArea;

	static std::list<Object*> ObjList;
	static int _last_id; //last created object id

	std::list<Object*> ChildrenList;
	//std::list< /*subsystem type*/ > _subsystems; //TODO subsystem list

    Vec2 _pos;
    Vec2 _global_pos;
    SDL_Rect _draw_rect;

	int _id;
	obj_type _type;
	Object* _owner;

    void SetOwner(Object* obj);

	/**
	 * Move children when parent is moved
	 */
	void MoveChildern(const Vec2& delta_pos);

	std::list<Object*>::iterator FindChild(Object* obj);
};

#endif /* SRC_CORE_OBJECT_H_ */
