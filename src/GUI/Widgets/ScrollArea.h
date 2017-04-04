/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/ScrollArea.cpp
!*/

#ifndef SRC_GUI_SCROLLAREA_H_
#define SRC_GUI_SCROLLAREA_H_

#include "GUI/Widget.h"
#include "Render/Camera.h"

//Draws all children on this widget
class ScrollArea: public Widget {
public:
    ScrollArea(const Vec2& pos, const Vec2& size);
    virtual ~ScrollArea();

    //virtual const Vec2& GetGlobalPos() const;

    virtual void SetCamera(Camera* cam);

    virtual void OnUpdate();
    virtual void OnRender();
    virtual void RenderChildren();
    virtual void UpdateChildren();

    virtual void SetSize(const Vec2 &size);

    virtual void Connect(Object* obj);

    virtual void Move(const Vec2 &delta_pos);
    virtual void SetPos(const Vec2& new_pos);

    void Scroll(const Vec2& direct);
    //Vertical scroll
    void ScrollV(int step);
    //Horizontal scroll
    void ScollH(int step);

private:
    Vec2 _old_cam_pos;
    bool _scroll_cam_scope;
    void SetTmpCam();

};

#endif /* SRC_GUI_SCROLLAREA_H_ */
