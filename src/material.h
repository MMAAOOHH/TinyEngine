#pragma once

#include "glad/glad.h"
#include "shader.h"
#include "texture.h"

namespace Component
{
	class Material
	{
		static GLuint id_gen;
		GLuint tex_unit_;

	public:
		Texture& texture;
		Shader& shader;
		GLuint id;

		Material(Texture& texture, Shader& shader, GLint tex_unit)
			: texture(texture), shader(shader), id(id_gen++), tex_unit_(tex_unit)
		{}

		~Material()
		{}

		void compile(); //setup up shader uniforms
		void bind(); //setup textures
	};
}