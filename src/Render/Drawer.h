#ifndef DRAWER_H
#define DRAWER_H

#include <vector>
#include <SDL2/SDL_render.h>

#include "Core/Vec2.h"
#include "Render/Camera.h"

class Drawer{
public:
    static void Line(const Vec2& point1, const Vec2& point2, const SDL_Color& color);
    static void Rect(const Vec2& pos, const Vec2& size, const SDL_Color& color, bool dynamic = false, float angle = 0);
    //static void Poly(const Vec2& center, float radius, const SDL_Color& color);
    static void Circle(const Vec2& center, float radius, const SDL_Color& color, bool dynamic = false, float angle = 0);

    static void RenderAll(SDL_Renderer* renderer, Camera *camera);

private:
    enum ShapeType{
        SHAPE_LINE,
        SHAPE_RECT,
        SHAPE_RECT_DYN,
        SHAPE_CIRCLE,
        SHAPE_CIRCLE_DYN
    };

    struct shape{
        ShapeType type;
        SDL_Color color;
        float angle;
        float radius;
        SDL_Point pos;
        std::vector<SDL_Point> points;
    };
    static std::vector<shape> RenQueue;

    static void Flush();

    Drawer();
};

#endif // DRAWER_H
