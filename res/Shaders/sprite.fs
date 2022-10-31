#version 330 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D image;
uniform vec3 u_color;

void main()
{	
	color = vec4(u_color, 1.0) * texture(image, TexCoords);
}