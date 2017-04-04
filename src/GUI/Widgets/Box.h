/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.
  
  BGE - boldtemple Cross Platform Game Engine
  /GUI/Widgets/Box.h
!*/

#ifndef SRC_GUI_BOX_H_
#define SRC_GUI_BOX_H_

#include <string>
#include <sstream>

#include "Render/Sprite.h"
#include "GUI/Widget.h"
#include "GUI/Text.h"
#include "Core/Resources.h"

class Box: public Widget {
public:
    Box(const Vec2& pos, const Vec2& size, const std::string& font, int font_pt_size);
    virtual ~Box();

    virtual void SetSize(const Vec2& size);
    virtual void OnRender();

    virtual void Move(const Vec2& delta_pos);
    virtual void SetPos(const Vec2& pos);

    void SetIcon(const std::string& icon);
    virtual void SetText(const std::string& str);

    void SetOffset(const SDL_Rect& offset);
    SDL_Rect GetOffset();

    Vec2 GetTextSize() const;


protected:
    int _pt_size;
    int _line_spacing = 0;
    SDL_Rect _text_offset = {4, 4, 4, 4};

    std::string _str_text;

    SDL_Texture* _text_texture;
    Text _text;
    SDL_Rect _text_draw_rect;
    Vec2 _text_size;

    bool _has_icon;
    Sprite _icon;

    void CalcTextPos();
};

#endif /* SRC_GUI_BOX_H_ */
