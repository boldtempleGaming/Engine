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

    virtual void SetSize(const Vec2 &size);

    virtual void OnRender();
    virtual void RenderChildren();

    void Scroll(const Vec2& direct);
    void ScrollV(int step);
    void ScrollH(int step);

private:
    SDL_Texture* _area = nullptr;

    void CreateTexture();
};

#endif /* SRC_GUI_SCROLLAREA_H_ */
