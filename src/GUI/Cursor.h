#ifndef CURSOR_H_
#define CURSOR_H_

#include <SDL2/SDL.h>
#include "Render/Surface.h"

class Cursor {
public:
    static SDL_Texture* cursor_texture;
    static SDL_Rect cursor_rect;

    static void Init(SDL_Texture* cursor, int w, int h);
    static void SetTexture(SDL_Texture* new_cursor);
    static void Draw();
};

#endif /* CURSOR_H_ */

