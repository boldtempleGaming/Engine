/*
 * Surface.cpp
 *
 *  Created on: 21 июля 2014 г.
 *      Author: snickers
 */

#include "Surface.h"

double Surface::_interpolation = 0;
std::map<std::string, SDL_Texture*> Surface::Textures;

SDL_Texture* Surface::LoadTexture(const std::string& fpath) {

    std::string real_path = SPRITES_PATH + fpath;

    std::cout << "Loading texture \"" << real_path << "\"..." << std::endl;

    SDL_Texture* texture = Textures[fpath];

    if (texture == nullptr) {

        texture = IMG_LoadTexture(Window::GetRenderer(), real_path.c_str());

        if (texture != nullptr) {
            Textures[fpath] = texture;
        } else {
            std::cout << " >> !WARNING! << " << SDL_GetError() << std::endl;
            if (!Window::GetRenderer())
                std::cout << " Is Renderer initialized?" << std::endl;
        }

    }

    return texture;
}

void Surface::Draw(SDL_Texture* texture, SDL_Rect* dstrect) {

    if (texture) {
        SDL_RenderCopy(Window::GetRenderer(), texture, nullptr, dstrect);
    } else {
        DrawRect(dstrect, COLOR_MAGENTA);
    }

}

void Surface::Draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect) {

    if (texture) {
        SDL_RenderCopy(Window::GetRenderer(), texture, srcrect, dstrect);
    } else {
        DrawRect(dstrect, COLOR_MAGENTA);
    }

}

void Surface::Draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect,
        const double angle) {
    if (texture) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        SDL_RenderCopyEx(Window::GetRenderer(), texture, srcrect, dstrect,
                angle, nullptr, flip);
    } else {
        DrawRect(dstrect, COLOR_MAGENTA);
    }
}

void Surface::Draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect,
        const double angle, SDL_RendererFlip flip) {
    if (texture) {
        SDL_RenderCopyEx(Window::GetRenderer(), texture, srcrect, dstrect,
                angle, nullptr, flip);
    } else {
        DrawRect(dstrect, COLOR_MAGENTA);
    }
}

void Surface::DrawRect(SDL_Rect* rect, const Uint8 r, const Uint8 g,
        const Uint8 b, const Uint8 a) {

    SDL_SetRenderDrawColor(Window::GetRenderer(), r, g, b, a);
    SDL_RenderFillRect(Window::GetRenderer(), rect);
    SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r,
            BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);

}

void Surface::DrawRect(SDL_Rect* rect, SDL_Color color) {
    SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b,
            color.a);
    SDL_RenderFillRect(Window::GetRenderer(), rect);
    SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r,
            BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 255);
}

void Surface::DrawTexturedRect(SDL_Texture* src, SDL_Rect* src_rect,
        SDL_Rect* dst_rect, int tile_size) {
    for (int h_step = dst_rect->y; h_step < dst_rect->h; h_step += tile_size) {
        for (int w_step = dst_rect->x; w_step < dst_rect->w; w_step +=
                tile_size) {
            SDL_Rect dst_tmp = { w_step, h_step, tile_size, tile_size };
            Surface::Draw(src, src_rect, &dst_tmp);
        }
    }
}

void Surface::OnCleanUp() {

    auto iterator = Textures.begin();

    while (iterator != Textures.end()) {
        SDL_DestroyTexture((*iterator).second);
        iterator++;
    }

    Textures.clear();
}

void Surface::GetSkinnedRect(SDL_Texture* src, SDL_Texture* dst, const Vec2* pos,
        SDL_Rect* dst_rect, int size) {

    if(dst == nullptr){
        return;
    }

    int x = pos->x;
    int y = pos->y;

    //change the rendering target
    SDL_SetRenderTarget(Window::GetRenderer(), dst);

    if (src == nullptr) {
        //Fill texture by MAGENTA color
        SDL_SetRenderDrawColor(Window::GetRenderer(),COLOR_MAGENTA.r,
                COLOR_MAGENTA.g, COLOR_MAGENTA.b, 255);
        SDL_RenderClear(Window::GetRenderer());

    } else {

        SDL_SetRenderDrawColor(Window::GetRenderer(), BACKGROUND_COLOR.r,
                BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 0);
        SDL_RenderClear(Window::GetRenderer());

        SDL_Rect src_tmp, dst_tmp;

        src_tmp = {x + size, y + size, size, size};
        dst_tmp = {size, size, dst_rect->w - size, dst_rect->h - size}; // == {x0, y0, x, y}
        Surface::DrawTexturedRect(src, &src_tmp, &dst_tmp, size);

        //left border
        src_tmp = {x, y + size, size, size};
        dst_tmp = {0, size, size, dst_rect->h - size}; //Координаты нашего прямоугольника и его размер
        Surface::DrawTexturedRect(src, &src_tmp, &dst_tmp, size);

        //right border
        src_tmp = {x + 2*size, y + size, size, size};
        dst_tmp = {dst_rect->w - size, size, dst_rect->w, dst_rect->h - size};
        Surface::DrawTexturedRect(src, &src_tmp, &dst_tmp, size);

        //upper border
        src_tmp = {x + size, y, size, size};
        dst_tmp = {size, 0, dst_rect->w - size, size};
        Surface::DrawTexturedRect(src, &src_tmp, &dst_tmp, size);

        //bottom border
        src_tmp = {x + size, y + 2*size, size, size};
        dst_tmp = {size, dst_rect->h - size, dst_rect->w - size, dst_rect->h};
        Surface::DrawTexturedRect(src, &src_tmp, &dst_tmp, size);

        // upper Left corner
        src_tmp = {x, y, size, size};
        dst_tmp = {0, 0, size, size};
        Surface::Draw(src, &src_tmp, &dst_tmp);

        //upper Right corner
        src_tmp = {x + 2*size, y, size, size};
        dst_tmp = {dst_rect->w - size, 0, size, size};
        Surface::Draw(src, &src_tmp, &dst_tmp);

        //bottom left corner border
        src_tmp = {x, y + 2*size, size, size};
        dst_tmp = {0, dst_rect->h - size, size, size};
        Surface::Draw(src, &src_tmp, &dst_tmp);

        //bottom right corner border
        src_tmp = {x + 2*size, y + 2*size, size, size};
        dst_tmp = {dst_rect->w - size, dst_rect->h - size, size, size};
        Surface::Draw(src, &src_tmp, &dst_tmp);

//    //Drawing shadows
//    SDL_Color shadow = {0, 0, 0, 70};
//    SDL_Rect rct_shadow = { 2, dst_rect->h, dst_rect->w, dst_rect->h+2};
//    Surface::DrawRect(&rct_shadow, shadow);
//    
//    rct_shadow = { dst_rect->w, 2, dst_rect->w, dst_rect->h-2};
//    Surface::DrawRect(&rct_shadow, shadow);

    }

    //change the target back to the default
    SDL_SetRenderTarget(Window::GetRenderer(), nullptr); //NULL SETS TO DEFAULT
}

void Surface::SetInterpolation(const double& inter) {
    _interpolation = inter;
}

double Surface::GetInterpolation() {
    return _interpolation;
}
