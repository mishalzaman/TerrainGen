#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include <sdl/SDL.h>
#include <iostream>

class Input
{
public:
	Input();
	~Input();
	int mouseX;
	int mouseY;
	void update(float deltaTime);
	bool isForward();
	bool isBackward();
	bool isStrafeLeft();
	bool isStrafeRight();
	bool isMouseMotion();
	bool isTab();
	bool isLShift();
	bool isQuit();
private:
	SDL_Event event;
	bool forward = false;
	bool backward = false;
	bool strafeRight = false;
	bool strafeLeft = false;
	bool lShift = false;
	bool mouseMotion = false;
	bool tab = false;
	bool quit = false;
};

