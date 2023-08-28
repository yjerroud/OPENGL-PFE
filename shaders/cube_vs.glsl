#version 330 core

layout(location = 0) in vec3 Position;
uniform vec4		cubeColor;
uniform mat4		projection;
uniform mat4		view;
uniform mat4		world;

out vec4			fsColor;

void	main()
{
	fsColor = cubeColor;
	gl_Position = projection * view * world * vec4(Position, 1.0f);
}