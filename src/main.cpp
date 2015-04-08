#include <iostream>

#include "Engine.h"
#include "constants.h"
#include "GUI/Cursor.h"
#include "Core/sys.h"
#include "Core/FPScounter.h"
#include "Demo/Ship.h"
#include "GUI/Button.h"
#include "GUI/CheckBox.h"

using namespace std;

MessageBox* text;
MessageBox* test, * test2;

FPS_counter fps;

void OnClick(){
    std::cout << "clicked :) " << std::endl;
}

void Engine::OnInit(){
	Window::SetMode(800, 600, false, "Shoot yourself!");

	Ship *ship = new Ship;
	ship->OnLoad("ship.png", 44, 44, 0);

	Entity* block = new Entity;
	block->OnLoad("NOIMAGE", 200, 50, 0);
	block->Move(Vec2(200, 200));


    /*
        cout << "text = ";
        SDL_Rect rct = {0,0,0,0};
	text = new MessageBox(GUI::GetRoot(), rct, "", false);
        text->Move(100, 100);
        
        
        rct = {300,400,24,47};
	    CheckBox* box = new CheckBox(&rct, "Box");
        box->SetParent(GUI::GetRoot());
        //box->Move(0, 0);
        

        cout << "test = ";
        test = new MessageBox(GUI::GetRoot());
        test->SetText(  "Пробный текст\nНовая строка Бла бла бла блаббла\nЕще новая строка\nЕще строка\nВот новая опять строка");
        test->Move(0, 12);
        
        
        cout << "button = ";
        SDL_Rect btn_pos = {250, 250, 60, 34};
        Button* button = new Button(btn_pos, "Button", OnClick);
        button->SetParent(GUI::GetRoot());
       
        cout << "test2 = ";
        test2 = new MessageBox(test);
        test2->SetText("Тест2");
        test2->Move(100, 100);
        //test2->SetCallback(OnClick);
        //тест
//test commit*/


}

void Engine::OnEvent(SDL_Event* event, const Uint8* keyboardState){

}

void Engine::OnUpdate(){
	fps.OnUpdate();

        
	//text->SetText("FPS: " + int_to_str(fps.GetFPS()));
	
            if(Cursor::button == SDL_BUTTON_LEFT){
               // text->Move(Cursor::X() - 32, Cursor::Y() + 32);
            }
        //text->Move(Cursor::X() - 32, Cursor::Y() + 32);
}

void Engine::OnRender(){

}

void Engine::OnCleanUp(){
	
}

#undef main
int main()
{
	//-static-libgcc -static-libstdc++
	Engine engine;
	engine.Start();
	return 0;
}
