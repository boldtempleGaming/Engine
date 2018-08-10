#include "Surface.h"

double Surface::_interpolation = 0;
std::vector<Surface::viewport> Surface::_ViewportsStack;

void Surface::Draw(SDL_Texture* texture, SDL_Rect* dstrect) {
    SDL_Rect tmp = MoveToViewport(dstrect);

    if (texture) {
        SDL_RenderCopy(Window::GetRenderer(), texture, nullptr, &tmp);
    } else {
        DrawRect(&tmp, COLOR_MAGENTA);
    }
}

void Surface::Draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect) {
    SDL_Rect tmp = MoveToViewport(dstrect);

    if (texture) {
        SDL_RenderCopy(Window::GetRenderer(), texture, srcrect, &tmp);
    } else {
        DrawRect(&tmp, COLOR_MAGENTA);
    }
}

void Surface::Draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect,
        const double angle) {
    SDL_Rect tmp = MoveToViewport(dstrect);

    if (texture) {
        SDL_RendererFlip flip = SDL_FLIP_NONE;
        SDL_RenderCopyEx(Window::GetRenderer(), texture, srcrect, &tmp,
                angle, nullptr, flip);
    } else {
        DrawRect(&tmp, COLOR_MAGENTA);
    }
}

void Surface::Draw(SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect,
        const double angle, SDL_RendererFlip flip) {
    SDL_Rect tmp = MoveToViewport(dstrect);

    if (texture) {
        SDL_RenderCopyEx(Window::GetRenderer(), texture, srcrect, &tmp,  angle, nullptr, flip);
    } else {
        DrawRect(&tmp, COLOR_MAGENTA);
    }
}

void Surface::DrawRect(SDL_Rect* rect, const Uint8 r, const Uint8 g,
        const Uint8 b, const Uint8 a, bool filled) {
    SDL_Rect tmp = MoveToViewport(rect);

    SDL_SetRenderDrawColor(Window::GetRenderer(), r, g, b, a);
    if(filled){
        SDL_RenderFillRect(Window::GetRenderer(), &tmp);
    }else{
        SDL_RenderDrawRect(Window::GetRenderer(), &tmp);
    }
    SDL_Color background = Window::GetBackgroundColor();
    SDL_SetRenderDrawColor(Window::GetRenderer(), background.r,
                           background.g, background.b, 255);
}

void Surface::DrawRect(SDL_Rect* rect, SDL_Color color, bool filled) {
    SDL_Rect tmp = MoveToViewport(rect);

    SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
    if(filled){
        SDL_RenderFillRect(Window::GetRenderer(), &tmp);
    }else{
        SDL_RenderDrawRect(Window::GetRenderer(), &tmp);
    }
    SDL_Color background = Window::GetBackgroundColor();
    SDL_SetRenderDrawColor(Window::GetRenderer(), background.r,
                           background.g, background.b, 255);
}

void Surface::DrawTexturedRect(SDL_Texture* src, SDL_Rect* src_rect, SDL_Rect* dst_rect, int tile_size) {
    for (int h_step = dst_rect->y; h_step < dst_rect->h; h_step += tile_size) {
        for (int w_step = dst_rect->x; w_step < dst_rect->w; w_step += tile_size) {
            SDL_Rect dst_tmp = { w_step, h_step, tile_size, tile_size };
            Surface::Draw(src, src_rect, &dst_tmp);
        }
    }
}

void Surface::GetSkinnedRect(SDL_Texture* src, SDL_Texture* dst, const Vec2* pos, SDL_Rect* dst_rect, int size) {

    if (dst == nullptr) {
        return;
    }

    int x = pos->x;
    int y = pos->y;

    //change the rendering target
    SDL_SetRenderTarget(Window::GetRenderer(), dst);

    if (src == nullptr) {
        //Fill texture by MAGENTA color
        SDL_SetRenderDrawColor(Window::GetRenderer(), COLOR_MAGENTA.r,
                COLOR_MAGENTA.g, COLOR_MAGENTA.b, 255);
        SDL_RenderClear(Window::GetRenderer());

    } else {
        SDL_Color background = Window::GetBackgroundColor();
        SDL_SetRenderDrawColor(Window::GetRenderer(), background.r,
                               background.g, background.b, 0);
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

void Surface::BeginViewport(const Vec2& scr_offset, const Vec2& viewport_size){
    _ViewportsStack.emplace_back(scr_offset, viewport_size);
}

void Surface::EndViewport(){
    _ViewportsStack.pop_back();
}

const Surface::viewport& Surface::GetLastViewport(){
    return _ViewportsStack.back();
}

void Surface::CullViewport(Vec2& l_offset, Vec2& l_size,
                           const Vec2& r_offset, const Vec2& r_size){

    if(l_offset.x < r_offset.x){
        l_offset.x = r_offset.x;
    }
    else if(l_offset.x + l_size.x > r_offset.x + r_size.x){
        l_size.x = (r_offset.x + r_size.x) - l_offset.x;
    }

    if(l_offset.y < r_offset.y){
        l_offset.y = r_offset.y;
    }
    else if(l_offset.y + l_size.y > r_offset.y + r_size.y){
        l_size.y = (r_offset.y + r_size.y) - l_offset.y;
    }
}

SDL_Rect Surface::MoveToViewport(SDL_Rect* rect){
    viewport tmp =  _ViewportsStack.back();

    return {
        rect->x - static_cast<int>(tmp._offset.x),
        rect->y - static_cast<int>(tmp._offset.y),
        rect->w,
        rect->h
    };
}
