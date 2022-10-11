#pragma once

#include "glad/glad.h"
#include "Shader.h"
#include "Texture.h"

class Material
{
	static GLuint id_gen;
	GLuint tex_unit_;

public:
	Texture& texture;
	Shader& shader;
	GLuint id;

	Material(Texture& texture, Shader& shader, GLuint tex_unit);
	~Material() = default;


	void compile(); //setup up shader uniforms
	void bind(); //setup textures

};
