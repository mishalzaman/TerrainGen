#ifndef TERRAIN_H
#define TERRAIN_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../structs/meshStruct.h"
#include "primitives/Plane.h"
#include "utilities/OpenglSystem.h"
#include "Shader.h"
#include "stb_image.h"
#include <vector>
#include "utilities/easylogging++.h"

class Terrain
{
public:
	Terrain();
	Terrain(unsigned int width, unsigned int height);
	~Terrain();
	void init();
	void updateVerticesByScale();
	void draw(glm::vec3 lightPosition);
	float scale = 0.32;
private:
	void generateBuffers();
	void setImageDataWidthAndHeight();
	int width = 0;
	int height = 0;
	std::vector<MeshStruct> mesh;
	std::vector<glm::uvec3> indices;
	unsigned int VAO;
	unsigned int VBO;
	Shader shader;

	unsigned char *hmImageData;
	int imageWidth;
	int imageHeight;
};

#endif

