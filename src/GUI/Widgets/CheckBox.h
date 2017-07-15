#ifndef CHECKBOX_H
#define	CHECKBOX_H

#include "Common/constants.h"
#include "GUI/Widget.h"
#include "GUI/Widgets/Box.h"
#include "GUI/Widgets/Button.h"

#define BOX_SIZE 32

class CheckBox : public Widget {
public:
    CheckBox(const Vec2& pos, const Vec2& size,
            const int& widget_width, const std::string& label);
    virtual ~CheckBox();

    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnTopMouseEvent();

    void SetState(bool checked);
    bool GetState();

private:
    bool _checked;
    bool _clicked;

    Vec2 _style;
    Vec2 _style_unchecked;
    Vec2 _style_checked;

    Box* _box;
    Box* _label;
};

#endif	/* CHECKBOX_H */

