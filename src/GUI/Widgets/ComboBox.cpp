#include "ComboBox.h"

ComboBox::ComboBox(const Vec2& pos, const Vec2& size):
    Box(pos, size, Resources::GetDefaultFont(), Resources::GetDefaultFontPtsize())
{
    ShowBack(true);
    SetBackGround("pgui.png", Vec2(0,0), 8);
    _selected = 0;

    this->AddAction("mouseup", [this](){
        this->IgnoreClick(true);

        ScrollArea* btns_list = new ScrollArea(Vec2::ZERO, Vec2::ZERO);
        btns_list->Show(false);
        Connect(btns_list);

        //ShowItems();

        Vec2 combo_size = GetSize();

        btns_list->SetSize(Vec2(combo_size.x, combo_size.y * 5));// 5 items in view

        int idx = 0;
        for(auto it = _Items.begin(); it != _Items.end(); ++it, ++idx){
            Button* btn_item = new Button(Vec2(0, idx * combo_size.y),
                                          Vec2(combo_size.x, combo_size.y),
                                          Resources::GetDefaultFont(),
                                          Resources::GetDefaultFontPtsize());
            int my_idx = idx;
            btn_item->ShowBack(true);
            btn_item->SetText(*it);
            btn_item->SetStyle("pgui.png", Vec2(94,0), Vec2(94,0), Vec2(72,0), 8);

            btn_item->AddAction("mouseup", [this, my_idx, btns_list](){
               this->IgnoreClick(false);
               this->SetSelected(my_idx);
               btns_list->Show(false);

               Disconnect(btns_list);
               btns_list->DeleteLater();
            }, btns_list);

            btns_list->Connect(btn_item);
        }

        btns_list->Show(true);
        btns_list->SetBackGround("pgui.png", Vec2(0,24), 8);
        btns_list->ShowBack(true);
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

    std::cout << GetGlobalPos().x << std::endl;

    _text_offset.x = (GetSize().x - _text_size.x)/2;
    _text_offset.y = (GetSize().y - _text_size.y)/2;

    Box::SetText(str);
    CalcTextPos();
}

void ComboBox::ShowItems(){

}

void ComboBox::HideItems(){

}
