#include "Cursor.h"

SDL_Texture* Cursor::cursor_texture = nullptr;
SDL_Rect Cursor::cursor_rect;

void Cursor::Init(SDL_Texture* cursor, int w, int h) {
    SDL_ShowCursor(0);
    SDL_SetRelativeMouseMode(SDL_bool(0));

    cursor_texture = cursor;
    cursor_rect = {0, 0, w, h};
}

void Cursor::SetTexture(SDL_Texture* new_cursor) {
    cursor_texture = new_cursor;
}

void Cursor::Draw() {
    SDL_GetMouseState(&cursor_rect.x, &cursor_rect.y);
    Surface::Draw(cursor_texture, &cursor_rect);
}