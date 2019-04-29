#include "Terrain.h"
#include <iostream>

// https://www.redblobgames.com/maps/terrain-from-noise/

Terrain::Terrain()
	: shader("shaders/material.vert", "shaders/material.frag")
{
}

Terrain::Terrain(unsigned int width, unsigned int height)
	: shader("shaders/material.vert", "shaders/material.frag")
{
	this->width = width;
	this->height = height;
}

Terrain::~Terrain()
{
}

void Terrain::init()
{
	if (this->width == 0 || this->height == 0)
	{
		this->setImageDataWidthAndHeight();
		Plane::vertices(this->width, this->height, this->mesh, this->indices, this->hmImageData);
	}
	else
	{
		Plane::vertices(this->width, this->height, this->mesh, this->indices);
	}
	
	Plane::normals(this->mesh, this->indices);
	
	this->generateBuffers();
}

void Terrain::draw(glm::vec3 lightPosition)
{
	float scale = 32.0;

	this->shader.use();
	glBindVertexArray(this->VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	this->shader.setMat4("model", model);

	// light properties
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	this->shader.setVec3("lightColor", lightColor);
	this->shader.setVec3("lightPos", lightPosition);
	this->shader.setVec3("objectColor", glm::vec3(0.6f, 0.6f, 0.6f));

	// OpenglSystem::enableCulling(true);
	// OpenglSystem::enableWireframe(true);
	glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size() * 3, GL_UNSIGNED_INT, 0);
	// OpenglSystem::enableWireframe(false);
	// OpenglSystem::enableCulling(false);
}

void Terrain::generateBuffers()
{
	unsigned int VBO;
	unsigned int IBO;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->mesh.size() * sizeof(MeshStruct), &this->mesh[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(glm::uvec3), glm::value_ptr(this->indices[0]), GL_STATIC_DRAW);

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshStruct), (void*)0);
	glEnableVertexAttribArray(0);

	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshStruct), (void*)offsetof(MeshStruct, normal));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Terrain::setImageDataWidthAndHeight()
{
	std::string path = "assets/hm.png";
	int nChannels;

	this->hmImageData = stbi_load(path.c_str(), &this->width, &this->height, &nChannels, 1);

	if (!this->hmImageData)
	{
		std::cout << "could not load image data" << std::endl; 
	}
}
