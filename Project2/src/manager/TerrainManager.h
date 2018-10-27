#pragma once
#include <iostream>
#include <vector>

#include "../terrain/Terrain.h"
#include "../shader/TerrainShader.h"
#include "../kernel/Window.h"

class TerrainManager {
private:

	std::vector<Terrain*>* m_terrains;
	TerrainShader* m_shader;

public:

	TerrainManager();
	~TerrainManager();

	void add_terrain(const Terrain& terrain);

	void draw();
	void init_shader();
};