#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 coords;

out vec2 TexCoords;
out vec2 f_Position;

uniform mat4 projection;

void main()
{	
	TexCoords = coords;
	gl_Position = projection * vec4(position, 0.0, 1.0);
	f_Position = gl_Position.xy;
}
