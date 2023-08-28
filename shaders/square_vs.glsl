#version 330 core

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TexCoord;
uniform vec4		squareColor;
uniform int		 projectionEnabled;
uniform mat4		projection;
uniform mat4		view;

out vec4			fsColor;
out vec2			aTexCoord;

void	main()
{
	fsColor = squareColor;
	aTexCoord = TexCoord;
	if (projectionEnabled == 1)
		gl_Position = projection * view * vec4(Position, 1.0f, 1.0f);
	else
		gl_Position = vec4(Position, 0.0f , 1.0f);
}