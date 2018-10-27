#include "TerrainManager.h"


TerrainManager::TerrainManager() {
	m_terrains = new std::vector<Terrain*>;
	m_terrains->push_back(
		new Terrain(0, 0)
	);
	init_shader();
}

TerrainManager::~TerrainManager() {
	for (int i = 0; i < m_terrains->size(); i++)
		delete m_terrains->at(i);
	delete m_terrains;
	delete m_shader;
}

void TerrainManager::add_terrain(const Terrain& terrain) {
	//m_terrains->push_back(&terrain);
}

void TerrainManager::draw() {

	m_shader->start();
	m_shader->load_mat4x4("view", *Camera::get_instance()->get_view_matrix());
	for (int i = 0; i < m_terrains->size(); i++) {
		m_shader->load_mat4x4("transform", *(*(*m_terrains).at(i)).get_transform());
		(*(*m_terrains).at(i)).draw();
	}
		

	m_shader->stop();
}

void TerrainManager::init_shader() {
	m_shader = new TerrainShader;
	m_shader->addVertexShader("shader/terrain/VS.glsl");
	m_shader->addFragmentShader("shader/terrain/FS.glsl");
	m_shader->linkProgram();
	m_shader->get_uniforms_location();

	m_shader->start();
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)1400/ (float)1050, 0.1f, 1000.f);
	m_shader->load_mat4x4("projection", proj);
	m_shader->stop();
}