/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widget.cpp
!*/

#ifndef SRC_GUI_Widget_H_
#define SRC_GUI_Widget_H_

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

#include <Core/Vec2.h>
#include <Core/Object.h>
#include <Core/Resources.h>
#include <Render/Sprite.h>
#include <IO/Mouse.h>

enum widget_state{
    WIDGET_NORMAL = 0,
    WIDGET_RELEASED,
    WIDGET_HOVERED,
    WIDGET_PRESSED
};

class Widget: public Object {
public:
    Widget(const Vec2& pos, const Vec2& size);
    virtual ~Widget();
    void Show(bool show);
    void ShowBack(bool show_bg);
    virtual void SetBackGround(const std::string& tileset, const Vec2& skin, int tile_size);

    void AddAction(const std::string& action_name, std::function<void(void)> action, Object* listener);
    void DeleteAction(const std::string& action_name, Object* listener);
    void DeleteAllActions(Object* listener);

    virtual void OnTopMouseEvent();
    virtual void OnMouse();
    virtual void OnUpdate();

    const bool& IsVisible() const;
    const bool& BackIsVisible() const;

protected:
    typedef  struct {Object* listener;
                     std::unordered_map<std::string, std::function<void(void)>> Actions;} Actions;

    Camera* _camera = nullptr;
    Sprite _back;

    widget_state _prev_state = WIDGET_NORMAL;
    widget_state _state = WIDGET_NORMAL;

    bool _visible;
    bool _bg_visible;
    bool _clicked = false;
    bool _was_intersected = false;
    bool _intersected = false;

    std::function<void(void)> _click_action;
    std::vector<Actions> _Listeners;

    void EmitAction(const std::string& action_name);
};

#endif /* SRC_GUI_Widget_H_ */
