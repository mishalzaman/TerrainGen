#include "Plane.h"

void Plane::vertices(
	int width,
	int height,
	std::vector<MeshStruct>& mesh,
	std::vector<glm::uvec3>& indices
)
{
	// get a width:height ratio in n:1 format
	int ratio_divisor_w = width / height;
	int ratio_divisor_h = height / height;

	// vertices
	for (int row = 0; row <= height; row++)
	{
		for (int column = 0; column <= width; column++)
		{
			MeshStruct tMesh;

			float x = (float)column / (float)width/ratio_divisor_h;
			float y = (float)row / (float)height/ratio_divisor_w;
			float z = 0.0f;
			// float z = sin(x*4.0f*3.141526f) * sin(y*4.0f*3.141526f) * 0.1f;

			tMesh.position = glm::vec3(x, y, z);
			tMesh.normal = glm::vec3(0, 0, 0);
			mesh.push_back(tMesh);
		}
	}

	// indices
	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			int row1 = row * (width + 1);
			int row2 = (row + 1) * (width + 1);

			// triangle 1
			indices.push_back(glm::uvec3(row1 + column, row1 + column + 1, row2 + column + 1));

			// triangle 2
			indices.push_back(glm::uvec3(row1 + column, row2 + column + 1, row2 + column));
		}
	}
}

void Plane::vertices(
	int width,
	int height,
	std::vector<MeshStruct>& mesh,
	std::vector<glm::uvec3>& indices,
	unsigned char* heightmapImageData,
	float scale
)
{
	// get a width:height ratio in n:1 format
	int ratio_divisor_w = width / height;
	int ratio_divisor_h = height / height;

	// vertices
	for (int row = 0; row <= height; row++)
	{
		for (int column = 0; column <= width; column++)
		{
			MeshStruct tMesh;

			float x = (float)column / (float)width/ratio_divisor_h;
			float y = (float)row / (float)height/ratio_divisor_w;

			float z;
			if (row == height || column == width || row == 0 || column == 0)
			{
				z = 0.0f;
			}
			else
			{
				float pixel = heightmapImageData[width * row + column];
				z = float(pixel / 256.0)*-scale;
			}

			tMesh.position = glm::vec3(x, y, z);
			tMesh.normal = glm::vec3(0, 0, 0);
			mesh.push_back(tMesh);
		}
	}

	// indices
	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			int row1 = row * (width + 1);
			int row2 = (row + 1) * (width + 1);

			// triangle 1
			indices.push_back(glm::uvec3(row1 + column, row1 + column + 1, row2 + column + 1));

			// triangle 2
			indices.push_back(glm::uvec3(row1 + column, row2 + column + 1, row2 + column));
		}
	}
}

void Plane::textures(std::vector<MeshStruct> &mesh)
{
	for (int i = 0; i < mesh.size(); i++)
	{
		mesh[i].texture = glm::vec2(mesh[i].position.x, mesh[i].position.y);
	}
}

void Plane::normals(std::vector<MeshStruct> &mesh, std::vector<glm::uvec3> &indices)
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

int Plane::greatest_common_divisor(int a, int b)
{
	// Everything divides 0  
	if (a == 0)
		return b;
	if (b == 0)
		return a;

	// base case 
	if (a == b)
		return a;

	// a is greater 
	if (a > b)
		return Plane::greatest_common_divisor(a - b, b);
	return Plane::greatest_common_divisor(a, b - a);
}
