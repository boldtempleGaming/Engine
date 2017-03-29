/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widget.cpp
!*/

#ifndef SRC_GUI_Widget_H_
#define SRC_GUI_Widget_H_

#include "Core/Vec2.h"
#include "Core/Object.h"
#include <Core/Resources.h>
#include "Render/Sprite.h"


class Widget: public Object {
public:
    Widget(const Vec2& pos, const Vec2& size, Camera* cam = GUI::GetCamera());
    virtual ~Widget();
    void Show(bool show);
    void ShowBack(bool show_bg);
    void SetBackGround(const std::string& tileset, const Vec2& skin, int tile_size);
    void SetCamera(Camera* cam);

    virtual void Connect(Object *obj);

    const bool& IsVisible() const;
    const bool& BackIsVisible() const;

protected:
    Camera* _camera = nullptr;
    bool _visible;
    bool _bg_visible;
    Sprite _back;
};

#endif /* SRC_GUI_Widget_H_ */
