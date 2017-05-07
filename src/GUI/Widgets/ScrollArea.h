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

    virtual void SetPos(const Vec2& new_pos);
    virtual void SetSize(const Vec2& size);

    virtual void OnRender();

    virtual void UpdateChildren();
    virtual void RenderChildren();
    virtual void Connect(Object* obj);

    void SetContentSize(const Vec2& size);
    void SetWidthLimit(const Vec2& width_limit);
    void SetHeightLimit(const Vec2& height_limit);

    void Scroll(const Vec2& direction);
    void ScrollV(int step);
    void ScrollH(int step);

private:
    Object* _container;

    Vec2 _width_limit = Vec2::ZERO; // no limits
    Vec2 _heigth_limit = Vec2::ZERO;

    SDL_Texture* _area = nullptr;

    void CreateTexture();
};

#endif /* SRC_GUI_SCROLLAREA_H_ */
