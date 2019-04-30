#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <sdl/SDL.h>
#include "utilities/OpenglSystem.h"
#include "uniform_buffers/UniformBufferMatrices.h"
#include "CameraFP.h"
#include "Terrain.h"
#include "FrameBuffer.h"
#include "Input.h"
#include "Light.h"

class Engine
{
public:
	Engine(unsigned int screenWidth, unsigned int screenHeight);
	~Engine();
	void initialize(SDL_Window* window);
	void load();
	void update(float deltaTime);
	void render();
	bool isShutDown();
	Input input;
private:
	// properties
	unsigned int screenWidth;
	unsigned int screenHeight;
	bool shutDown = false;
	SDL_Window* window;
	Terrain terrain;
	UniformBufferMatrices uniformBufferMatrices;
	CameraFP camera;
	Light light;
	FrameBuffer framebuffer;
	glm::mat4 projection;
	glm::mat4 view;
	bool enteredRenderViewMovement = false;
	bool isWireframe = false;
};

#endif
