#include "Material.h"

Material::Material(Texture& texture, Shader& shader, GLuint tex_unit)
	: texture(texture), shader(shader), tex_unit_(tex_unit), id(id_gen++)
{}

GLuint Material::id_gen = 0;
void Material::compile()
{
	shader.use();
	shader.set_int("image", tex_unit_);
}

void Material::bind()
{
	glActiveTexture(GL_TEXTURE0 + tex_unit_);
	texture.bind();
}
