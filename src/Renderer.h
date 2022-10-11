#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/vec4.hpp>
#include "Material.h"


#define Rect glm::vec4

class Renderer
{
	GLuint vbo_, vao_, attrib_size_;
	std::vector<GLfloat> buffer_;
	Material* current_material_;
	GLuint max_sprites_;

public:
	Renderer(std::vector<GLuint> attributes, GLuint max_sprites);
	~Renderer();

	void begin();
	void end();
	void draw(Rect dest_rect, Rect src_rect, Material& material);
	void flush();

};