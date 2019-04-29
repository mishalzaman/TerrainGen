#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "primitives/Sphere.h"
#include "Shader.h"
#include "../structs/meshStruct.h"
#include <vector>

class Light
{
public:
	Light(glm::vec3 position);
	~Light();
	void load();
	void update();
	void draw();
	void cleanup();
	glm::vec3 getPosition();
	void updatePosition(glm::vec3 position);
private:
	std::vector<MeshStruct> mesh;
	std::vector<glm::uvec3> indices;
	glm::vec3 position;
	unsigned int VAO;
	Shader shader;
};

#endif

