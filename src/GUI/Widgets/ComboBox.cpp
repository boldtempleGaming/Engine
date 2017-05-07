#include "ComboBox.h"
#include <iostream>

ComboBox::ComboBox(const Vec2& pos, const Vec2& size):
    Box(pos, size, Resources::GetDefaultFont(), Resources::GetDefaultFontPtsize())
{
    ShowBack(true);
    SetBackGround(Resources::GetDefaultStyle(), Vec2::ZERO, 8);

    this->AddAction("mouseup", [this](){
        if(this->_btns_area){
            HideItems();
        }else{
            ShowItems();
        }
    }, this);
}

void ComboBox::AddItem(const std::string& item){
    _Items.push_back(item);
}

void ComboBox::SetItems(const std::list<std::string>& Items){
    _Items = Items;
    SetSelected(0);
}

void ComboBox::SetSelected(int item){
    if(item >= 0 || item < _Items.size()){
        _selected = item;

        if(!_Items.empty()){
            auto iter = _Items.begin();
            std::advance(iter, _selected);

            SetText(*iter);
        }else{
            SetText(std::string());
        }
        EmitAction("itemselected");
    }
}

void ComboBox::SetText(const std::string& str){
    Box::SetText(str);

    _text_offset.x = (GetSize().x - _text_size.x)/2;
    _text_offset.y = (GetSize().y - _text_size.y)/2;

    Box::SetText(str);
    CalcTextPos();
}

void ComboBox::ShowItems(){
    Vec2 combo_size = GetSize();

    _btns_area = new ScrollArea(Vec2(0.0f, combo_size.y),
                                           Vec2(combo_size.x, combo_size.y * max_items));
    _btns_area->SetBackGround(Resources::GetDefaultStyle(), Vec2(0,24), 8);
    _btns_area->ShowBack(true);

    _btns_area->SetContentSize(Vec2(combo_size.x, combo_size.y * _Items.size()));
    _btns_area->SetHeightLimit(Vec2(combo_size.y * max_items - combo_size.y * _Items.size(),
                                    combo_size.y * _Items.size() + (combo_size.y * max_items - combo_size.y * _Items.size()) ));

    Connect(_btns_area);

    _btns_area->AddAction("mousepressout",[this](){
        if(this->_btns_area && GUI::GetLastClicked() != this){
            HideItems();
        }
    }, _btns_area);

    _btns_area->AddAction("wheelup",[this](){
        this->_btns_area->ScrollV(10);
    }, _btns_area);

    _btns_area->AddAction("wheeldown",[this](){
       this->_btns_area->ScrollV(-10);
    }, _btns_area);

    int idx = 0;
    for(auto it = _Items.begin(); it != _Items.end(); ++it, ++idx){
        Button* btn_item = new Button(Vec2(0, idx * combo_size.y),
                                      Vec2(combo_size.x, combo_size.y),
                                      Resources::GetDefaultFont(),
                                      Resources::GetDefaultFontPtsize());
        int my_idx = idx;
        btn_item->ShowBack(true);
        btn_item->SetText(*it);
        btn_item->SetStyle(Resources::GetDefaultStyle(),
                           Vec2(94,0),
                           Vec2(94,0),
                           Vec2(72,0),
                           8);

        btn_item->AddAction("mouseup", [this, my_idx](){
           this->HideItems();
           this->SetSelected(my_idx);
        }, _btns_area);

        _btns_area->Connect(btn_item);
    }
}

void ComboBox::HideItems(){
    _btns_area->DeleteLater();
    _btns_area = nullptr;
}
