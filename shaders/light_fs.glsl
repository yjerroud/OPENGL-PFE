#version 330 core

out vec4	Color;

in vec3	outPos;
in vec3	outNor;

uniform float	ambientStrength;
uniform float	specularStrength;

uniform vec3	lightPos;
uniform vec3	viewPos;
uniform vec3	lightColor;
uniform vec4	cubeColor;

void main()
{
	vec3	ambient = ambientStrength * lightColor;
	
	vec3	lightDir = normalize(lightPos - outPos);
	float	diff = max(dot(outNor, lightDir), 0.0f);
	vec3	diffuse = diff * lightColor;
	
	
	vec3	viewDir = normalize(viewPos - outPos);
	vec3	reflectDir = reflect(-lightDir, outNor);
	float	spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
	vec3	specular = specularStrength * spec * lightColor;
	
	vec3	result = (ambient + diffuse + specular) * vec3(cubeColor);
	
	Color = vec4(result, 1.0f);
}