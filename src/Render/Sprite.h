/*
 * Sprite.h
 *
 *  Created on: 05 марта 2015 г.
 *      Author: snickers
 */

#ifndef SRC_RENDER_SPRITE_H_
#define SRC_RENDER_SPRITE_H_


#include <cmath>

#include "Core/Resources.h"

#include "Render/Surface.h"
#include "Render/Animation.h"
#include "Render/Camera.h"

class Sprite {
public:
    Sprite();
    virtual ~Sprite();

    void Draw(const Vec2& pos, const Vec2& size, const Camera* camera);
    void Draw(const Vec2& pos, const Vec2& size){
        Draw(pos, size, Window::GetCamera());
    }

    void SetTexture(SDL_Texture* texture);
    void SetTexture(const std::string& file);
    void SetAngle(int angle);
    void SetFlip(SDL_RendererFlip flip);

    SDL_Texture* GetTexture() const;
    int GetAngle() const;
    SDL_RendererFlip GetFlip() const;

    /*==Animation control==*/
    void SetAnimation(const Animation& anim);
    void SetFrameSize(const Vec2& frame_size);
    void SetAnimation(int begin_frame, int end_frame);
    void SetFrame(int frame);
    void SetAnimationRate(int frame_rate);

    Sprite& operator = (Sprite const & right);

private:
    SDL_Texture* _texture;
    SDL_RendererFlip _flip;
    int _angle;
    int _frames_per_width;
    int _frames_per_height;
    SDL_Rect _src_rect;//real size of texture
    SDL_Rect _anim_rect;
    Animation _anim_control;
};

#endif /* SRC_RENDER_SPRITE_H_ */
