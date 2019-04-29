#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "../structs/meshStruct.h"
#include <vector>

namespace Plane
{
	void vertices(
		int width,
		int height,                                        
		std::vector<MeshStruct>& mesh,
		std::vector<glm::uvec3> &indices
	);
	void vertices(
		int width,
		int height,
		std::vector<MeshStruct>& mesh,
		std::vector<glm::uvec3> &indices,
		unsigned char* heightmapImageData
	);
	void textures(std::vector<MeshStruct> &mesh);
	void normals(std::vector<MeshStruct> &mesh, std::vector<glm::uvec3> &indices);
	int greatest_common_divisor(int a, int b);
}

#endif

