#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include <iostream>

#include <SDL2/SDL.h>

#include <Core/Vec2.h>
#include <GUI/GUI.h>
#include <Render/Camera.h>

class Window {
public:
	static SDL_Window* GetWindow();
	static SDL_Renderer* GetRenderer();
	static Camera* GetCamera();
	static int GetWidth();
	static int GetHeight();
    static Vec2 GetSize();

	static const std::string& GetTitle();

    static bool SetMode(int w, int h, bool full_screen, const std::string& title = "boldtemple Game Engine");
	static void SetWidth(const int& w);
	static void SetHeight(const int& h);
    static void SetSize(const Vec2& size);

	static void SetInterpolation(const float& value);
	static float GetInterpolation();

	static void SetBackgroundColor(const SDL_Color& color);
	static SDL_Color GetBackgroundColor();

	static bool IsInitialised();
	static bool IsFullscreen();

	static void OnCleanUp();

	/* more Window functions are there https://wiki.libsdl.org/CategoryVideo */

private:
	Window();
	~Window();

    static SDL_Window* _window;
    static SDL_Renderer* _renderer;

	static Camera _camera;
    static Vec2 _size;
	static bool _full_screen;
	static SDL_Color _color_background;
    static std::string _title;

	static bool Init();
};

#endif /* WINDOW_H_ */
