#include "Engine.h"

Engine::Engine(unsigned int screenWidth, unsigned int screenHeight)
	: terrain(), 
	framebuffer(screenWidth, screenHeight),
	uniformBufferMatrices(),
	input(),
	camera(screenWidth, screenHeight),
	light(glm::vec3(40, 10, 40))
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

Engine::~Engine()
{
}

void Engine::initialize(SDL_Window* window)
{
	this->window = window;
	this->terrain.init();
}

void Engine::load()
{
	this->projection = glm::perspective(
		glm::radians(45.0f),
		(float)this->screenWidth / (float)this->screenHeight,
		0.1f,
		100.0f
	);
	this->uniformBufferMatrices.updateUBOMatricesProjection(projection);
	this->light.load();
	this->framebuffer.load();
}

void Engine::update(float deltaTime)
{
	glm::vec3 lightPosition = this->light.getPosition();

	this->input.update(deltaTime);
	if (this->input.isForward()) { this->camera.forward(deltaTime); };
	if (this->input.isBackward()) { this->camera.backward(deltaTime); };
	if (this->input.isStrafeLeft()) { this->camera.strafeLeft(deltaTime); };
	if (this->input.isStrafeRight()) { this->camera.strafeRight(deltaTime); };
	if (this->input.isArrowForward()) 
	{ 
		this->light.updatePosition(glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z - 0.1));
	};
	if (this->input.isArrowBackward())
	{
		this->light.updatePosition(glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z + 0.1));
	};
	if (this->input.isArrowLeft())
	{
		this->light.updatePosition(glm::vec3(lightPosition.x - 0.1, lightPosition.y, lightPosition.z));
	};
	if (this->input.isArrowRight())
	{
		this->light.updatePosition(glm::vec3(lightPosition.x + 0.1, lightPosition.y, lightPosition.z));
	};
	if (this->input.isMouseMotion())
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		this->camera.mousePositionUpdate(deltaTime, x, y);
		SDL_WarpMouseInWindow(this->window, this->screenWidth / 2.0f, this->screenHeight / 2.0f);
	}
	if (this->input.isQuit()) { this->shutDown = true; }

	this->view = this->camera.getViewMatrix();
	this->uniformBufferMatrices.updateUBOMatricesView(view);
}

void Engine::render()
{
	this->framebuffer.beginDrawingSceneToColourTexture();
		this->terrain.draw(this->light.getPosition());
		this->light.draw();
	this->framebuffer.BindToFrameBuffer();
	
	this->framebuffer.render();
}

bool Engine::isShutDown()
{
	return this->shutDown;
}

