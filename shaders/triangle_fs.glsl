#version 330 core

in vec4	fsColor;
in vec2	aTexCoord;
out vec4	Color;

uniform sampler2D	tex;
uniform float	   blendValue;

void	main()
{
	vec4	texColor = texture(tex, aTexCoord);
	//Color = (1.0f - aBlendValue) * fsColor + aBlendValue * texColor;
	Color = mix(fsColor, texColor, blendValue);
}