#include "Engine.h"

Engine::Engine(unsigned int screenWidth, unsigned int screenHeight)
	: terrain(), 
	framebuffer(screenWidth, screenHeight),
	uniformBufferMatrices(),
	input(),
	camera(screenWidth, screenHeight),
	light(glm::vec3(1, 2, 2))
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
	this->input.update(deltaTime);

	if (this->input.isLShift())
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_None);

		if (this->enteredRenderViewMovement == false)
		{
			SDL_WarpMouseInWindow(this->window, this->screenWidth / 2.0f, this->screenHeight / 2.0f);
			this->enteredRenderViewMovement = true;
		}
		else
		{
			if (this->input.isMouseMotion())
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				this->camera.mousePositionUpdate(deltaTime, x, y);
				SDL_WarpMouseInWindow(this->window, this->screenWidth / 2.0f, this->screenHeight / 2.0f);
			}
		}

		// camera movement
		if (this->input.isForward()) { this->camera.forward(deltaTime); };
		if (this->input.isBackward()) { this->camera.backward(deltaTime); };
		if (this->input.isStrafeLeft()) { this->camera.strafeLeft(deltaTime); };
		if (this->input.isStrafeRight()) { this->camera.strafeRight(deltaTime); };
	}
	else
	{
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		this->enteredRenderViewMovement = false;
	}

	if (this->input.isQuit()) { this->shutDown = true; }

	this->view = this->camera.getViewMatrix();
	this->uniformBufferMatrices.updateUBOMatricesView(view);
}

void Engine::render()
{
	// render frambuffer
	this->framebuffer.beginDrawingSceneToColourTexture();
		OpenglSystem::enableWireframe(this->isWireframe);
		this->terrain.draw(this->light.getPosition());
		OpenglSystem::enableWireframe(false);
		this->light.draw();
	this->framebuffer.BindToFrameBuffer();
	
	this->framebuffer.render();

	// render gui
	ImGui::SetNextWindowPos(ImVec2(0,0)); // sets position of window
	ImGui::Begin("Terrain", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
	ImGui::Checkbox("Wireframe", &this->isWireframe);
	ImGui::PushItemWidth(200);
	ImGui::End();
}

bool Engine::isShutDown()
{
	return this->shutDown;
}

