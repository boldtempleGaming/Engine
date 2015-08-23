#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include <iostream>

#include <SDL2/SDL.h>

#include "GUI/GUI.h"
#include "Render/Camera.h"

class Window {
public:
	static SDL_Window* GetWindow();
	static SDL_Renderer* GetRenderer();
	static Camera* GetCamera();
	static int GetWidth();
	static int GetHeight();

	static const std::string& GetTitle();

	static bool SetMode(int w, int h, bool full_screen, std::string title = "boldtemple Game Engine");
	static void SetWidth(const int& w);
	static void SetHeight(const int& h);

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
	static Camera _camera;
	static SDL_Window* _window;
	static SDL_Renderer* _renderer;
	static std::string _title;
	static int _w, _h;
	static bool _full_screen;
	static SDL_Color _color_background;

	static bool Init();
};

#endif /* WINDOW_H_ */
