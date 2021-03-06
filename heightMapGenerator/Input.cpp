#include "Input.h"

using namespace std;

Input::Input()
{
}

Input::~Input()
{
}

void Input::update(float deltaTime)
{
	while (SDL_PollEvent(&this->event)) {
		// Update input events for Imgui
		ImGui_ImplSDL2_ProcessEvent(&event);

		this->mouseMotion = false;

		switch (this->event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w && event.key.repeat == 0) { this->forward = true; }
			if (event.key.keysym.sym == SDLK_s && event.key.repeat == 0) { this->backward = true; }
			if (event.key.keysym.sym == SDLK_a && event.key.repeat == 0) { this->strafeLeft = true; }
			if (event.key.keysym.sym == SDLK_d && event.key.repeat == 0) { this->strafeRight = true; }
			// left shift
			if (event.key.keysym.sym == SDLK_LSHIFT && event.key.repeat == 0) { this->lShift = true; }
			// quit
			if (event.key.keysym.sym == SDLK_ESCAPE) { this->quit = true; }
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_w && event.key.repeat == 0) { this->forward = false; }
			if (event.key.keysym.sym == SDLK_s && event.key.repeat == 0) { this->backward = false; }
			if (event.key.keysym.sym == SDLK_a && event.key.repeat == 0) { this->strafeLeft = false; }
			if (event.key.keysym.sym == SDLK_d && event.key.repeat == 0) { this->strafeRight = false; }
			// left shift
			if (event.key.keysym.sym == SDLK_LSHIFT && event.key.repeat == 0) { this->lShift = false; }
			break;
		case SDL_MOUSEMOTION:
			this->mouseMotion = true;
		default:
			break;
		}
	}
}

bool Input::isForward() { return this->forward; }
bool Input::isBackward() { return this->backward; }
bool Input::isStrafeLeft() { return this->strafeLeft; }
bool Input::isStrafeRight() { return this->strafeRight; }
bool Input::isMouseMotion()
{ 
	return this->mouseMotion;

	//if (this->mouseMotion)
	//{
	//	this->mouseMotion = false;
	//	return true;
	//}

	//this->mouseMotion = true;
	//return false;
}
bool Input::isLShift() { return this->lShift; }
bool Input::isTab() { return this->tab; }
bool Input::isQuit() { return this->quit; }

