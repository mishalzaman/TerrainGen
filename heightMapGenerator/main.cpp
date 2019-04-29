#include <iostream>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include "utilities/OpenglSystem.h"
#include "Engine.h"
#include "utilities/GUI.h"
#include "utilities/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

const int width = 1280;
const int height = 720;
const int MINIMUM_FPS_FRAME = 6;
float minimum_fps_delta_time = 1000 / MINIMUM_FPS_FRAME;
float previous_timestep = SDL_GetTicks();

using namespace std;

int main(int argc, char *argv[])
{
	// Initialize OpenGl/SDL subsystem
	if (!OpenglSystem::initSDL())
	{
		LOG(ERROR) << "Failed to initialize SDL";
		return 1;
	}

	SDL_Window* window = OpenglSystem::initWindow(width, height);
	if (!window)
	{
		LOG(ERROR) << "Failed to initialize window";
		return 1;
	}

	SDL_GLContext context = OpenglSystem::initContext(window);
	if (!context)
	{
		LOG(ERROR) << "Failed to initialize context";
		return 1;
	}

	if (!OpenglSystem::initGlew())
	{
		LOG(ERROR) << "Failed to initialize GLEW";
		return 1;
	}
	OpenglSystem::initGlAttributes(3, 3);
	OpenglSystem::enableMouseCursor(true);
	OpenglSystem::enableMouseCapture(true);
	OpenglSystem::setMouseToCenter(window, width, height);
	OpenglSystem::enableDepthTest(true);

	Engine* engine = new Engine(width, height);

	engine->initialize(window);
	engine->load();

	GUI::initImgui(window, context);
	// imgui style https://www.unknowncheats.me/forum/direct3d/189635-imgui-style-settings.html

	float deltaTime, lastTime = 0.0f;

	while (!engine->isShutDown())
	{
		float current_timestep = SDL_GetTicks();
		
		if (previous_timestep < current_timestep) {

			float deltaTime = current_timestep - previous_timestep;

			if (deltaTime > minimum_fps_delta_time) {
				deltaTime = minimum_fps_delta_time; // slow down if the computer is too slow
			}

			// update
			engine->update(deltaTime);

			previous_timestep = current_timestep;

			// render
			GUI::initImguiFrame(window);
			// GUI::draw();

			engine->render();
			GUI::renderGUI();

			SDL_GL_SwapWindow(window);
		}
		else {
			SDL_Delay(1);
		}

	}

	OpenglSystem::cleanUp(context, window);
	GUI::cleanup();

	delete engine;

	return 0;
}