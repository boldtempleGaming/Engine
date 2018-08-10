#include "Drawer.h"

#include <cmath>
#include <iostream>

std::vector<Drawer::shape> Drawer::RenQueue;

void Drawer::Line(const Vec2& point1, const Vec2& point2, const SDL_Color& color){
    SDL_Point pt1 = {static_cast<int>(std::round(point1.x)), static_cast<int>(std::round(point1.y))};
    SDL_Point pt2 = {static_cast<int>(std::round(point2.x)), static_cast<int>(std::round(point2.y))};

    RenQueue.push_back({SHAPE_LINE, color, 0, 0, {0, 0}, {pt1, pt2}});
}

void Drawer::Rect(const Vec2& pos, const Vec2& size, const SDL_Color &color, bool dynamic, float angle){
    SDL_Point pt1 = {static_cast<int>(std::round(pos.x)), static_cast<int>(std::round(pos.y))};
    SDL_Point pt2 = {static_cast<int>(std::round(size.x)), static_cast<int>(std::round(size.y))};

    if(dynamic){
        RenQueue.push_back({SHAPE_RECT_DYN, color, angle * Vec2::GRADUS, 0, {0, 0}, {pt1, pt2}});
    }else{
        RenQueue.push_back({SHAPE_RECT, color, 0, 0, {0, 0},{pt1, pt2}});
    }
}

void Drawer::Circle(const Vec2& center, float radius, const SDL_Color &color, bool dynamic, float angle){
    if(dynamic){
        RenQueue.push_back({SHAPE_CIRCLE_DYN, color, angle, radius, {(int)center.x, (int)center.y}, {}});
    }else{
        RenQueue.push_back({SHAPE_CIRCLE, color, 0, radius, {(int)center.x, (int)center.y}, {}});
    }
}

inline
void RotatePoint(SDL_Point& pt, SDL_Point& center, float& tsin, float& tcos){
    pt.x -= center.x;
    pt.y -= center.y;

    int new_x = (pt.x * tcos - pt.y * tsin);
    int new_y = (pt.x * tsin + pt.y * tcos);

    pt.x = new_x + center.x;
    pt.y = new_y + center.y;
}

inline
void GetRotatetedRect(SDL_Point pos, SDL_Point* pts, int w, int h, double angle){
    SDL_Point center = {pos.x + w/2, pos.y + h/2};
    float tmp_sin = sin(angle);
    float tmp_cos = cos(angle);

    pts[0] = {pos.x,     pos.y};
    pts[1] = {pos.x + w, pos.y};
    pts[2] = {pts[1].x,  pos.y + h};
    pts[3] = {pos.x,     pts[2].y};

    RotatePoint(pts[0], center, tmp_sin, tmp_cos);
    RotatePoint(pts[1], center, tmp_sin, tmp_cos);
    RotatePoint(pts[2], center, tmp_sin, tmp_cos);
    RotatePoint(pts[3], center, tmp_sin, tmp_cos);

    pts[4] = pts[0];
}

inline
void GetCircle(std::vector<SDL_Point>& pts, int x0, int y0, int radius){
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        pts.push_back({x0 + x, y0 + y});
        pts.push_back({x0 + y, y0 + x});
        pts.push_back({x0 - y, y0 + x});
        pts.push_back({x0 - x, y0 + y});
        pts.push_back({x0 - x, y0 - y});
        pts.push_back({x0 - y, y0 - x});
        pts.push_back({x0 + y, y0 - x});
        pts.push_back({x0 + x, y0 - y});

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }

    //pts.push_back(pts[0]);
}

void Drawer::RenderAll(SDL_Renderer* renderer, Camera* camera){
    Vec2 camOffset = camera->GetPos();

    int size = RenQueue.size();
    shape* tmp;
    SDL_Rect rect_tmp;
    SDL_Point pts[5];

    for(int i = 0; i < size; ++i){
        tmp = &RenQueue[i];
        SDL_SetRenderDrawColor(renderer, tmp->color.r, tmp->color.g, tmp->color.b, tmp->color.a);

        switch(tmp->type){
        case SHAPE_LINE:
            SDL_RenderDrawLine(renderer, tmp->points[0].x - camOffset.x,
                                         tmp->points[0].y - camOffset.y,
                                         tmp->points[1].x - camOffset.x,
                                         tmp->points[1].y - camOffset.y);
            break;

        case SHAPE_RECT:
            rect_tmp.x = tmp->points[0].x - camOffset.x;
            rect_tmp.y = tmp->points[0].y - camOffset.y;
            rect_tmp.w = tmp->points[1].x;
            rect_tmp.h = tmp->points[1].y;

            SDL_RenderDrawRect(renderer, &rect_tmp);
            break;

        case SHAPE_RECT_DYN:
            GetRotatetedRect({static_cast<int>(tmp->points[0].x - camOffset.x),
                              static_cast<int>(tmp->points[0].y - camOffset.y)},
                              pts,
                              tmp->points[1].x,
                              tmp->points[1].y,
                              tmp->angle);

            SDL_RenderDrawLines(renderer, pts, 5);
            break;

        case SHAPE_CIRCLE:
            GetCircle(tmp->points, tmp->pos.x - camOffset.x,
                                   tmp->pos.y - camOffset.y,
                                   tmp->radius);
            SDL_RenderDrawPoints(renderer, &(tmp->points[0]), tmp->points.size());
            break;

        case SHAPE_CIRCLE_DYN:
            GetCircle(tmp->points, tmp->pos.x - camOffset.x,
                                   tmp->pos.y - camOffset.y,
                                   tmp->radius);
            SDL_RenderDrawPoints(renderer, &(tmp->points[0]), tmp->points.size());

            Vec2 line = Vec2(tmp->radius, 0).GetRotated(tmp->angle) + Vec2(tmp->pos.x, tmp->pos.y);

            SDL_RenderDrawLine(renderer, tmp->pos.x - camOffset.x,
                                         tmp->pos.y - camOffset.y,
                                         line.x - camOffset.x,
                                         line.y - camOffset.y);
            break;
        }
    }

    Flush();
}

void Drawer::Flush(){
    RenQueue.resize(0);
}

Drawer::Drawer(){}
