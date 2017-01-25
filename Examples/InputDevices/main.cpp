#include <iostream>

#include <Engine.h>

#include <Core/Object.h>
#include <Core/Vec2.h>
#include <Core/Resources.h>

#include <GUI/Window.h>

#include <Render/Sprite.h>
#include <Render/Camera.h>

#include <IO/Keyboard.h>

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

        //Track our torch sprite to mouse cursor
        Vec2 mouse_pos = Mouse::GetPos();
        Vec2 torch_center_pos =  Object::GetGlobalPos() + Object::GetSize()*0.5f;
        Vec2 direction = mouse_pos - torch_center_pos;

        torch.SetAngle(direction.GetAngle() + 90.0f);


        //Handle pressed keyboard keys
        const float step = 5.0f;
        const Vec2 up_step(0, -step);
        const Vec2 down_step(0, step);
        const Vec2 left_step(-step, 0);
        const Vec2 right_step(step, 0);

        if(Keyboard::isKeyDown(KEY_UP)){
            Object::Move(up_step);
        }
        else  if(Keyboard::isKeyDown(KEY_DOWN)){
            Object::Move(down_step);
        }
        else  if(Keyboard::isKeyDown(KEY_LEFT)){
            Object::Move(left_step);
        }
        else  if(Keyboard::isKeyDown(KEY_RIGHT)){
            Object::Move(right_step);
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
}

void Engine::OnUpdate(){

}

void Engine::OnRender(){

}

int main(){
    Engine engine;
    engine.Start();

    return 0;
}
