#include <iostream>

#include <Engine.h>

#include <Core/Object.h>
#include <Core/Vec2.h>
#include <Core/Resources.h>

#include <GUI/Window.h>

#include <Render/Sprite.h>
#include <Render/Camera.h>

using namespace std;


class MyObject: public Object{
public:
    MyObject(){
        cout << "Hello MyObject constructor!" << endl;

        this->CheckTop();

        //Setup object pos and size
        Object::SetPos(Vec2(0, 0));
        Object::SetSize(Vec2(32, 64));

        //Setup sprite
        torch.SetTexture(Resources::GetTexture("animated_torch_0.png"));
        torch.SetFrameSize(Object::GetSize());
    }

    void OnUpdate(){
        //required for OnTopMouseEvent
        this->CheckTop();
    }

    void OnTopMouseEvent(){
        cout << "MyObject hovered by mouse!" << endl;

        if(Mouse::AnyPressed()){
            if(Mouse::Pressed(MOUSE_LEFT) || Mouse::Pressed(MOUSE_RIGHT)){
                cout << "MyObject pressed!" << endl;
            }
        }
    }

    void OnRender(){
        //Draw our sprite
        torch.Draw(Object::GetGlobalPos(), Object::GetSize(), Window::GetCamera());
    }

private:
    Sprite torch;
};

//All game Objects have to be created in dynamic memory
MyObject* myObject;

void Engine::OnInit(){
    //Create object after engine initialization
    //Cause Resource manager will not work correctly
    myObject = new MyObject;

    //Get Engine's root object at 1'st layer
    Engine::AddLayer();
    Object* root = Engine::GetRootAtLayer(0);

    //Add our object to game
    root->Connect(myObject);

    //Move root and children will be moved with it
    //But children will save their local coordinates
    root->Move(Vec2(300, 300));
}

void Engine::OnUpdate(){

}

void Engine::OnRender(){

}

void Engine::OnCleanUp(){
    cout << "Do something before engine closing :)" << endl;
}

void Engine::OnEvent(SDL_Event *event, const Uint8 *keyboardState){

}

int main(){
    Engine engine;
    engine.Start();

    return 0;
}
