#include "Sphere.h"

// https://github.com/Erkaman/cute-deferred-shading/blob/master/src/main.cpp#L573

void Sphere::verticesAndIndices(
	int stacks,
	int slices,
	std::vector<MeshStruct>& mesh,
	std::vector<glm::uvec3>& indices)
{
	const float PI = 3.14;

	// vertices
	for (int i = 0; i <= stacks; ++i)
	{
		float v = (float)i / (float)stacks;
		float phi = v * PI;

		for (int j = 0; j <= slices; ++j)
		{
			float u = (float)j / (float)slices;
			float theta = u * (PI * 2);

			float x = cos(theta) * sin(phi);
			float y = cos(phi);
			float z = sin(theta) * sin(phi);

			MeshStruct tMesh;

			tMesh.position = glm::vec3(x, y, z);
			mesh.push_back(tMesh);
		}
	}

	// indices
	for (int i = 0; i < slices * stacks + slices; ++i)
	{
		indices.push_back(glm::uvec3(
			i,
			i + slices + 1,
			i + slices
		));

		indices.push_back(glm::uvec3(
			i + slices + 1,
			i,
			i + 1
		));
	}
}

void Sphere::normals(std::vector<MeshStruct>& mesh, std::vector<glm::uvec3>& indices)
{
	for (int i = 0; i < indices.size(); i++)
	{
		glm::vec3 v1 = mesh[indices[i].x].position;
		glm::vec3 v2 = mesh[indices[i].y].position;
		glm::vec3 v3 = mesh[indices[i].z].position;

		glm::vec3 edge1 = v1 - v2;
		glm::vec3 edge2 = v1 - v3;
		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

		mesh[indices[i].x].normal += normal;
		mesh[indices[i].y].normal += normal;
		mesh[indices[i].z].normal += normal;
	}
}
