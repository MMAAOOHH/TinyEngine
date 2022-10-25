#include "material.h"

GLuint Component::Material::id_gen = 0;

void Component::Material::compile()
{
	shader.use();
	shader.set_int("image", tex_unit_);
}

void Component::Material::bind()
{
	glActiveTexture(GL_TEXTURE0 + tex_unit_);
	texture.bind();
}