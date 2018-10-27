#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../buffer/TerrainMesh.h"

class Terrain {
private:
	glm::mat4* m_transform;
	int m_x, m_z;

	TerrainMesh* m_patch;
public:
	Terrain(int x, int z);
	~Terrain();

	glm::mat4* get_transform() const;
	void set_position(const int& x, const int& z);

	void draw();
};