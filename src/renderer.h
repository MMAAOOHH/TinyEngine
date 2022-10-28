#pragma once

#include <glad/glad.h>
#include <vector>
#include "material.h"
#include "rect.h"

struct drawable;

namespace Component
{
	class Renderer
	{
		GLuint vbo_, vao_, attrib_size_;
		std::vector<GLfloat> buffer_;
		Component::Material* current_material_;
		GLuint max_sprites_;

	public:
		Renderer(std::vector<GLuint> attributes, GLuint max_sprites);
		~Renderer();

		void begin();
		void end();
		void draw(drawable& drawable_struct);
		void flush();
	};
}
