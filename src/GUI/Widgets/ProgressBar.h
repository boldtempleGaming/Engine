#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "GUI/Widgets/Box.h"

class ProgressBar : public Box{
public:
    ProgressBar(const Vec2& pos, const Vec2& size);
    virtual ~ProgressBar();

    virtual void SetPos(const Vec2& pos);
    virtual void Move(const Vec2& delta_pos);
    virtual void OnRender();

    void SetValue(int value);
    int GetValue();

protected:
    int _value;

    SDL_Texture* _progress_texture;
    SDL_Rect _progress_draw_rect;

    void RenderProgress();
    void CalcProgressPos();

    virtual void SetText(const std::string& str);
    void UpdateProgressText();
};

#endif // PROGRESSBAR_H
