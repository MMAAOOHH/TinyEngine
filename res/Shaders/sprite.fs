#version 330 core

in vec2 TexCoords;
in vec2 f_Position;

out vec4 color;

uniform sampler2D image;
uniform vec3 u_color;

void main()
{	
	// Multiplies spritecolour with texture and the vertexposition on the screen
	color = vec4(u_color, 1.0) * texture(image, TexCoords) * vec4(f_Position.x, f_Position.y, 1.0, 1.0);
}