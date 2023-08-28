#ifndef GLTOOLS_H
#define GLTOOLS_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// NOTE(Yassine): expecting shaders to be in shader folder.
//				if name is provided then name_vs.glsl & name_fs.glsl
//				are the vertex & fragment shader in that order.
int			 compileShader(const char* name, unsigned int shaderType);
unsigned int	createShaderProgram(const char *name);

// TODO(Yassine): textures are expected to be in res folder
unsigned int	loadTexture(const char *filename);



#endif //GLTOOLS_H
