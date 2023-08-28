#version 330 core

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TexCoord;
uniform vec4		Color1;
uniform vec4		Color2;
uniform vec4		Color3;


out vec4			fsColor;
out vec2			aTexCoord;

void	main()
{
	if (Position == vec2(-0.5f, -0.5f))
		fsColor = Color1;
	else if (Position == vec2(0.0f, 0.5f))
		fsColor = Color2;
	else
		fsColor = Color3;
	aTexCoord = TexCoord;
	gl_Position = vec4(Position, 0.0f, 1.0f);
}