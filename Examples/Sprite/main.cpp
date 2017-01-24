#include <Engine.h>

#include <Core/Vec2.h>
#include <Core/Resources.h>

#include <Render/Sprite.h>
#include <Render/Camera.h>

#include <Render/Animation.h>

#include <GUI/Window.h>

Sprite spriteTorch;
Sprite animatedTorch;
Sprite rotatedTorch;
Sprite trackedToMouseTorch;

Vec2 size(32, 64);
Vec2 doubledSize = size * 2.0f;

void Engine::OnInit(){

    //Initializing sprite
    spriteTorch.SetTexture(Resources::GetTexture("animated_torch_0.png"));

    //Set frame size 32 pixels width and 64 pixels height
    spriteTorch.SetFrameSize(size);

    //Set current frame in our sprite-sheet
    spriteTorch.SetFrame(0);


    //Animation example
    animatedTorch = spriteTorch;

    Animation fire;
    fire.SetBeginFrame(0);
    fire.SetMaxFrame(8);
    fire.SetCurrentFrame(5);

    //Set frame rate, default is 100 ms
    //Lower is faster
    fire.SetFrameRate(200);

    animatedTorch.SetAnimation(fire);


    //Rotated torch
    rotatedTorch = animatedTorch;
    //Rotete on 90 degrees
    rotatedTorch.SetAngle(90);


    trackedToMouseTorch = animatedTorch;
}

void Engine::OnUpdate(){
    Vec2 mouse_pos = Mouse::GetPos();
    Vec2 torch_center_pos = doubledSize + doubledSize*0.5f;
    Vec2 direction = mouse_pos - torch_center_pos;

    trackedToMouseTorch.SetAngle(direction.GetAngle());
}

void Engine::OnRender(){
    Camera* camera = Window::GetCamera();

    //Sprites has to be drawn explicitly
    //arg1: current position of sprite
    //arg2: size of it
    //arg3: screen camera
    spriteTorch.Draw(Vec2(0, 0), doubledSize, camera);


    //Draw animated torch
    animatedTorch.Draw(Vec2(doubledSize.x, 0), doubledSize, camera);

    //Draw rotated torch
    rotatedTorch.Draw(Vec2(0, doubledSize.y), doubledSize, camera);

    //Draw tracked to mouse torch
    trackedToMouseTorch.Draw(doubledSize, doubledSize, camera);
}

#undef main
int main(){
    Engine engine;
    engine.Start();

	return 0;
}
