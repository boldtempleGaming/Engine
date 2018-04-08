#include <Render/Drawer.h>
#include <Engine.h>

double angle = 0;
Vec2 pos;
Vec2 center;

void Engine::OnInit() {
    center = Vec2( Window::GetWidth()/2, Window::GetHeight()/2);
    pos = center - Vec2(15, 15);
}

void Engine::OnUpdate() {
    angle = (Mouse::GetPos() - center).GetAngle();

    Camera* cam = Window::GetCamera();

    if(Keyboard::isKeyDown(KEY_DOWN)){
        cam->Move(Vec2(0, 5));
    }
    if(Keyboard::isKeyDown(KEY_UP)){
        cam->Move(Vec2(0, -5));
    }
    if(Keyboard::isKeyDown(KEY_LEFT)){
        cam->Move(Vec2(-5, 0));
    }
    if(Keyboard::isKeyDown(KEY_RIGHT)){
        cam->Move(Vec2(5, 0));
    }

}

void Engine::OnRender() {
    Vec2 screen_mouse_pos =  Window::GetCamera()->GetPos() + Mouse::GetPos();

    Drawer::Line(Vec2(0, 0), screen_mouse_pos, COLOR_YELLOW);
    Drawer::Line(Vec2(Window::GetWidth(), 0), screen_mouse_pos, COLOR_YELLOW);
    Drawer::Line(Vec2(0, Window::GetHeight()), screen_mouse_pos, COLOR_YELLOW);
    Drawer::Line(Vec2(Window::GetWidth(), Window::GetHeight()), screen_mouse_pos, COLOR_YELLOW);

    Drawer::Rect(pos, Vec2(30, 30), COLOR_PURPLE, true, angle);
    Drawer::Line(pos + Vec2(15, 15), screen_mouse_pos, COLOR_MAGENTA);

    Drawer::Circle(screen_mouse_pos, screen_mouse_pos.GetLength()/3, COLOR_RED, true, (center - screen_mouse_pos).GetAngle() );

    Drawer::RenderAll(Window::GetRenderer(), Window::GetCamera());
    Window::SetBackgroundColor(Window::GetBackgroundColor());
}

void Engine::OnEvent(SDL_Event *event, const Uint8 *keyboardState) {

}

void Engine::OnCleanUp() {

}

int main() {
    Engine engine;
    engine.Start();
    return 0;
}
