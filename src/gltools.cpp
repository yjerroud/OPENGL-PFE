#include "glTools.h"
#include <string.h>
#include <stdlib.h>


int		compileShader(const char* name, unsigned int shaderType)
{
	if (shaderType != GL_VERTEX_SHADER &&
		shaderType != GL_FRAGMENT_SHADER)
	{
		// NOTE(Yassine): error logging.
		printf("ShaderType Not Supported\n");
		return (0);
	}
	char	filename[256];
	strcpy(filename, "shaders/");
	strcpy(filename + strlen(filename), name);
	if (shaderType == GL_VERTEX_SHADER)
		strcpy(filename + strlen(filename), "_vs.glsl");
	else
		strcpy(filename + strlen(filename), "_fs.glsl");
	FILE*	file = fopen(filename, "rb");
	if(!file)
	{
		// TODO(Yassine): error logging.
		return (0);
	}
	fseek(file, 0, SEEK_END);
	long int	fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	char*	shaderBuffer = (char *)malloc(fileSize + 1);
	shaderBuffer[fileSize] = '\0';
	fread((void *)shaderBuffer, 1, fileSize, file);
	
	int	result = glCreateShader(shaderType);
	glShaderSource(result, 1, &shaderBuffer, NULL);
	glCompileShader(result);
	
	int	compilationStatus;
	glGetShaderiv(result, GL_COMPILE_STATUS, &compilationStatus);
	if (compilationStatus != GL_TRUE)
	{
		int	logLength = 0;
		char	errorMessage[2048];
		glGetShaderInfoLog(result, 2048, &logLength, errorMessage);
		// TODO(Yassine): error logging
		printf("%s\n", errorMessage);
		glDeleteShader(result);
		result = 0;
	}
	free(shaderBuffer);
	return (result);
}

unsigned int	createShaderProgram(const char *name)
{
	unsigned int	result;
	unsigned int	shaders[2];
	
	result = glCreateProgram();
	if (result == 0)
	{
		// TODO(Yassine): error logging.
		return (result);
	}
	bool failed = false;
	shaders[0] = compileShader(name, GL_VERTEX_SHADER);
	shaders[1] = compileShader(name, GL_FRAGMENT_SHADER);
	
	for (int i = 0; i < 2; ++i)
	{
		if (shaders[i] == 0)
		{
			glDeleteShader(shaders[i]);
			failed = true;
		}
	}
	if (failed)
	{
		glDeleteProgram(result);
		return (0);
		
	}
	for (int i = 0; i < 2; ++i)
	{
		glAttachShader(result, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glLinkProgram(result);
	return (result);
}

unsigned int	loadTexture(const char *filename)
{
	unsigned int	TextureID = 0;
	glGenTextures(1, &TextureID);
	
	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename, &width, &height, &nrComponents, 0);
	if (data)
	{
		unsigned int format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		stbi_image_free(data);
	}
	else
	{
		// TODO(Yassine): error Logs
		stbi_image_free(data);
	}
	
	return TextureID;
}