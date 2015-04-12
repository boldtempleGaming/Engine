/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/ScrollArea.cpp
!*/

#ifndef SRC_GUI_SCROLLAREA_H_
#define SRC_GUI_SCROLLAREA_H_

#include <GUI/Widget.h>

//Draws all children on this widget
class ScrollArea: public Widget {
public:
    ScrollArea(Object* owner, const Vec2& pos, const Vec2& size);
    virtual ~ScrollArea();

    const Vec2& GetGlobalPos();

    void OnUpdate();
    void OnRender();
    void RenderChildren();

    void Scroll(const Vec2& direct);
    //Vertical scroll
    void ScrollV(int step);
    //Horizontal scroll
    void ScollH(int step);
private:
    Vec2 _area_pos;
};

#endif /* SRC_GUI_SCROLLAREA_H_ */
