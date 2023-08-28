#version 330 core

out vec4	color;

uniform vec4	terrainColor;
uniform sampler2D	tex;
in vec2	outUV;

void	main()
{
	vec4 texColor = texture(tex, outUV);
	color = texColor;
}