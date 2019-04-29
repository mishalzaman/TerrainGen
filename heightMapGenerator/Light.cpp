#include "Light.h"

Light::Light(glm::vec3 position)
	: shader("shaders/lamp.vert", "shaders/lamp.frag")
{
	// this->shader.setUBOMatrices();
	this->position = position;
}

Light::~Light()
{
	this->cleanup();
}

void Light::load()
{
	Sphere::verticesAndIndices(10, 10, this->mesh, this->indices);
	// Sphere::normals(this->mesh, this->indices);

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

void Light::update()
{
}

void Light::draw()
{
	this->shader.use();
	glBindVertexArray(this->VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
	this->shader.setMat4("model", model);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size() * 3, GL_UNSIGNED_INT, 0);
}

glm::vec3 Light::getPosition()
{
	return this->position;
}

void Light::updatePosition(glm::vec3 position)
{
	this->position = position;
}

void Light::cleanup()
{
	if (this->VAO) {
		glDeleteVertexArrays(1, &this->VAO);
	}
}
