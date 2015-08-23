#ifndef ENGINE_BUTTON_H
#define ENGINE_BUTTON_H

#include <functional>
#include "GUI/Widgets/Box.h"

enum button_state{
    BUTTON_NORMAL = 0,
    BUTTON_RELEASED,
    BUTTON_HOVERED
};

class Button: public Box {
public:
    Button(Object* owner, const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size);
    virtual ~Button();

    void SetStyle(const std::string& style, const Vec2& pos_normal, const Vec2& pos_pressed, int tile_resolution);
    void RegisterAction(std::function<void(void)> action);
   // void RegisterAction(std::Mem_fn<void(void)> mem_action);

    virtual void OnUpdate();
    virtual void SetPos(const Vec2& pos);
    virtual void OnClick();
    virtual void Action();

protected:
    std::function<void(void)> _action;

private:
    bool _clicked;
    button_state _state = BUTTON_NORMAL;
    std::string _back_style;
    Vec2 _pos_normal;
    Vec2 _pos_pressed;
    int _tile_resolution;
};


#endif //ENGINE_BUTTON_H
