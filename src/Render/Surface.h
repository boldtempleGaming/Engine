/*
 * Surface.h
 *
 *  Created on: 21 июля 2014 г.
 *      Author: snickers
 */

#ifndef SURFACE_H_
#define SURFACE_H_

#include <utility>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Core/Vec2.h>

#include <GUI/colors.h>
#include <GUI/Window.h>

#include <Render/Camera.h>

#include <Common/constants.h>

class Surface {
public:
    struct viewport {
        Vec2 _offset;
        Vec2 _size;

        viewport(const Vec2 offset,
                 const Vec2 size):
            _offset(std::move(offset)),
            _size(std::move(size)) {}
    };

    static void Draw(SDL_Texture* texture, SDL_Rect* dstrect);
    static void Draw(SDL_Texture* texture, SDL_Rect* srcrect,
            SDL_Rect* dstrect);
    static void Draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect,
            const double angle);
    static void DrawRect(SDL_Rect* rect, SDL_Color color);
    static void DrawRect(SDL_Rect* rect, const Uint8 r, const Uint8 g,
            const Uint8 b, const Uint8 a);
    static void Draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect,
            const double angle, SDL_RendererFlip flip);
    static void DrawTexturedRect(SDL_Texture* src, SDL_Rect* src_rect,
            SDL_Rect* dst_rect, int tile_size);

    static void GetSkinnedRect(SDL_Texture* src, SDL_Texture* dst, const Vec2* pos,
            SDL_Rect* dst_rect, int size = 8);

    static void OnCleanUp();

    static void SetInterpolation(const double& inter);
    static double GetInterpolation();

    static void BeginViewport(const Vec2& scr_offset, const Vec2& viewport_size);
    static void EndViewport();

    static const viewport& GetLastViewport();
    static void CullViewport(Vec2& l_offset, Vec2& l_size,
                             const Vec2& r_offset, const Vec2& r_size);

private:
    static double _interpolation;
    static std::vector<viewport> _ViewportsStack;

    static SDL_Rect MoveToViewport(SDL_Rect* rect);
};

#endif /* SURFACE_H_ */
