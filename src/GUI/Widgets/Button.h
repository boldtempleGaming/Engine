#ifndef ENGINE_BUTTON_H
#define ENGINE_BUTTON_H

#include <functional>
#include "GUI/Widgets/Box.h"

class Button: public Box {
public:
    Button(const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size);
    virtual ~Button();

    void SetStyle(const std::string& style,
                  const Vec2& pos_normal,
                  const Vec2& pos_pressed,
                  const Vec2 &pos_hovered,
                  int tile_resolution);
    virtual void SetText(const std::string& str);

private:
    std::string _back_style;
    Vec2 _pos_normal;
    Vec2 _pos_pressed;
    Vec2 _pos_hovered;
    int _tile_resolution;
};

#endif //ENGINE_BUTTON_H
