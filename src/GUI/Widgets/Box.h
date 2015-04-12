/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/Box.h
!*/

#ifndef SRC_GUI_BOX_H_
#define SRC_GUI_BOX_H_

#include <GUI/Widget.h>

class Box: public Widget {
public:
    Box(Object* owner, const Vec2& pos, const Vec2& size);
    virtual ~Box();

    virtual void OnRender();
};

#endif /* SRC_GUI_BOX_H_ */
