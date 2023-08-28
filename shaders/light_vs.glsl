#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;

out vec3	outPos;
out vec3	outNor;

uniform mat4	view;
uniform mat4	projection;

void	main()
{
	outPos = Position;
	outNor = Normal;
	
	gl_Position = projection * view * vec4(Position, 1.0f);
	//gl_Position = vec4(Position, 1.0f);
}