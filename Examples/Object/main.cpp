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

        //Setup object pos and size
        Object::SetPos(Vec2(0, 0));
        Object::SetSize(Vec2(32, 64));

        //Setup sprite
        torch.SetTexture(Resources::GetTexture("animated_torch_0.png"));
        torch.SetFrameSize(Object::GetSize());
    }

    void OnUpdate(){
        Object::CheckClick(Window::GetCamera());
    }

    void OnRender(){
        //Draw our sprite
        torch.Draw(Object::GetGlobalPos(), Object::GetSize(), Window::GetCamera());
    }

    void OnClick(){
        cout << "MyObject clicked!" << endl;
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

int main(){
    Engine engine;
    engine.Start();

    return 0;
}
