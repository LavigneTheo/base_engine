#include "Terrain.h"

float arr[] = {
	0.f, 0.f, 0.f,
	1.f, 0.f, 0.f,
	1.f, 0.f, 1.f,
	0.f, 0.f, 1.f
};


Terrain::Terrain(int x, int z) : m_x(x), m_z(z) {
	m_transform = new glm::mat4(1);
	*m_transform = glm::translate(*m_transform, glm::vec3(m_x * 100, 0, m_z * 100));
	*m_transform = glm::scale(*m_transform, glm::vec3(100, 100, 100));
	m_patch = new TerrainMesh(arr, 16);
}

Terrain::~Terrain() {
	delete m_transform;
	delete m_patch;
}

glm::mat4*Terrain:: get_transform() const {
	return m_transform;
}

void Terrain::set_position(const int& x, const int& z) {
	m_x = x;
	m_z = z;
}

void Terrain::draw() {
	m_patch->draw();
}