#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <iterator>
#include <list>

#include <GUI/Widget.h>
#include <GUI/Widgets/Box.h>
#include <GUI/Widgets/Button.h>
#include <GUI/Widgets/ScrollArea.h>

class ComboBox : public Box{
public:
    ComboBox(const Vec2& pos, const Vec2& size);

    void AddItem(const std::string& item);
    void SetItems(const std::list<std::string>& Items);
    void SetSelected(int item);

    virtual void SetText(const std::string& str);

private:
    int _selected;
    std::list<std::string> _Items;

    void ShowItems();
    void HideItems();
};

#endif // COMBOBOX_H
