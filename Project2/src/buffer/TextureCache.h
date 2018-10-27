#pragma once

#include <inc/glew.h>
#include "stb/stb.h"
#include <iostream>
#include <map>
#include "Mesh.h"

class TextureCache {
private:
	std::map<std::string, unsigned int> m_textures;
	static TextureCache* INSTANCE;

	TextureCache(){}
public:
	~TextureCache();
	
	MeshTexture load_texture(std::string& path);
	MeshTexture load_texture_from_file(std::string& path);
	static TextureCache* get_texture_cache();
};




