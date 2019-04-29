#ifndef SPHERE_H
#define SPHERE_H

#include "../structs/meshStruct.h"
#include <glm/glm.hpp>
#include <vector>

namespace Sphere
{
	void verticesAndIndices(
		int stacks,
		int slices,
		std::vector<MeshStruct>& mesh,
		std::vector<glm::uvec3> &indices
	);
	void normals(std::vector<MeshStruct> &mesh, std::vector<glm::uvec3> &indices);
}

#endif
