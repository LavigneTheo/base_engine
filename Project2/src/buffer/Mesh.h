#pragma once
#include <inc/glew.h>
#include <iostream>
#include <vector>

struct MeshTexture {
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh {
	private :
		unsigned int m_vbo, m_ibo, m_vao;
		unsigned int m_size;
		std::vector<MeshTexture> m_textures;
	public:
		Mesh(
			const float* vertices, 
			const int& vertices_count, 
			std::vector<unsigned int> indices,
			std::vector<MeshTexture>& textures
			);
		void draw();
		std::vector<MeshTexture> get_textures() const;
};
