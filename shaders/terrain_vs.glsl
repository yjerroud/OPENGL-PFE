#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 UV;

uniform mat4	projection;
uniform mat4	view;

out vec2 outUV;

void	main()
{
	outUV = UV;
	gl_Position = projection * view * vec4(Position, 1.0f);
}