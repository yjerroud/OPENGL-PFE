#include "demo.h"
#include "glm/glm/gtc/random.hpp"


static void	InitTriangleDemo()
{
	float	vertices[] = {
		-0.5f, -0.5f,		0.0f, 0.0f,
		0.5f, -0.5f,		 1.0f, 0.0f,
		0.0f, 0.5f,		  0.5f, 1.0f
	};
	
	glGenVertexArrays(1, &(gTriangleDemo.vao));
	glBindVertexArray(gTriangleDemo.vao);
	
	glGenBuffers(1, &(gTriangleDemo.vbo));
	glBindBuffer(GL_ARRAY_BUFFER, gTriangleDemo.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	gTriangleDemo.tex = loadTexture("res/wall.png");
	gTriangleDemo.blendValue = 0.0f;
	gTriangleDemo.shaderProgram = createShaderProgram("triangle");
	gTriangleDemo.Color1 = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
	gTriangleDemo.Color2 = Vec4(0.0f, 1.0f, 0.0f, 1.0f);
	gTriangleDemo.Color3 = Vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

static void	RenderTriangleDemo()
{
	glPolygonMode(GL_FRONT_AND_BACK, gRasterMode);
	glViewport(0, 0, gClientWidth * (1.0f - gMENURATIO), gClientHeight);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(gTriangleDemo.ClearColor.r, gTriangleDemo.ClearColor.g, gTriangleDemo.ClearColor.b,gTriangleDemo.ClearColor.a);
	glBindVertexArray(gTriangleDemo.vao);
	glUseProgram(gTriangleDemo.shaderProgram);
	
	glUniform1f(glGetUniformLocation(gTriangleDemo.shaderProgram, "tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTriangleDemo.tex);
	
	glUniform1f(glGetUniformLocation(gTriangleDemo.shaderProgram, "blendValue"), (gTriangleDemo.blendValue));
	glUniform4fv(glGetUniformLocation(gTriangleDemo.shaderProgram, "Color1"),
				 1, &gTriangleDemo.Color1.r);
	
	glUniform4fv(glGetUniformLocation(gTriangleDemo.shaderProgram, "Color2"),
				 1, &gTriangleDemo.Color2.r);
	glUniform4fv(glGetUniformLocation(gTriangleDemo.shaderProgram, "Color3"),
				 1, &gTriangleDemo.Color3.r);
	glBindVertexArray(gTriangleDemo.vao);
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


static void	InitSquareDemo()
{
	float	vertices[] = {
		0.5f, 0.5f,	1.0f, 1.0f,
		-0.5f, 0.5f,	1.0f, 0.0f,
		-0.5f,-0.5f,	0.0f, 0.0f,
		0.5f, -0.5f,	0.0f, 1.0f
	};
	
	unsigned int	indices[] ={
		0, 1, 2,
		0, 2, 3
	};
	
	glGenVertexArrays(1, &(gSquareDemo.vao));
	glBindVertexArray(gSquareDemo.vao);
	
	glGenBuffers(1, &(gSquareDemo.vbo));
	glBindBuffer(GL_ARRAY_BUFFER, gSquareDemo.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	
	glGenBuffers(1, &(gSquareDemo.ebo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gSquareDemo.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	gSquareDemo.tex = loadTexture("res/wall.png");
	gSquareDemo.shaderProgram = createShaderProgram("square");
	gSquareDemo.Color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
	
	
	
	gSquareDemo.projectionEnabled = false;
	gSquareDemo.view = lookAtRH(Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
}

static void	RenderSquareDemo()
{
	glPolygonMode(GL_FRONT_AND_BACK, gRasterMode);
	glViewport(0, 0, gClientWidth * (1.0f - gMENURATIO), gClientHeight);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(gSquareDemo.ClearColor.r, gSquareDemo.ClearColor.g, gSquareDemo.ClearColor.b, gSquareDemo.ClearColor.a);
	if (gSquareDemo.projectionEnabled == true)
	{
		float	aspectRatio = (float)gClientWidth * (1.0f - gMENURATIO) / gClientHeight;
		gSquareDemo.projection = orthographicRH(-1.0f * aspectRatio, 1.0f * aspectRatio, -1.0f, 1.0f, -1.0f, 100.0f);
		glUniform1i(glGetUniformLocation(gSquareDemo.shaderProgram, "projectionEnabled"), 1);
		glUniformMatrix4fv(glGetUniformLocation(gSquareDemo.shaderProgram, "projection"), 1, false, &(gSquareDemo.projection.elems[0][0]));
		glUniformMatrix4fv(glGetUniformLocation(gSquareDemo.shaderProgram, "view"), 1, false, &(gSquareDemo.view.elems[0][0]));
	}
	else
		glUniform1i(glGetUniformLocation(gSquareDemo.shaderProgram, "projectionEnabled"), 0);
	
	glBindVertexArray(gSquareDemo.vao);
	
	glUseProgram(gSquareDemo.shaderProgram);
	
	glUniform1f(glGetUniformLocation(gSquareDemo.shaderProgram, "tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gSquareDemo.tex);
	
	glUniform4fv(glGetUniformLocation(gSquareDemo.shaderProgram, "squareColor"), 1, &gSquareDemo.Color.r);
	
	glUniform1f(glGetUniformLocation(gSquareDemo.shaderProgram, "blendValue"), (gSquareDemo.blendValue));
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


static void	InitCubeDemo()
{
	float	vertices[] =
	{
		-0.5f, -0.5f, -0.5f,	//0
		0.5f, -0.5f, -0.5f,	//1
		0.5f,  0.5f, -0.5f,	//2
		-0.5f,  0.5f, -0.5f,	//3
		
		-0.5f, -0.5f, 0.5f,	//4
		0.5f, -0.5f, 0.5f,	//5
		0.5f,  0.5f, 0.5f,	//6
		-0.5f,  0.5f, 0.5f,	//7
	};
	
	unsigned int	indices[] = {
		0, 1, 2,
		2, 3, 0,
		
		4, 5, 6,
		6, 7, 4,
		
		7, 3, 0,
		0, 4, 7,
		
		6, 2, 1,
		1, 5, 6,
		
		0, 1, 5,
		5, 4, 0,
		
		3, 2, 6,
		6, 7, 3
	};
	
	glGenVertexArrays(1, &(gCubeDemo.vao));
	glBindVertexArray(gCubeDemo.vao);
	
	glGenBuffers(1, &(gCubeDemo.vbo));
	glBindBuffer(GL_ARRAY_BUFFER, gCubeDemo.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glGenBuffers(1, &(gCubeDemo.ebo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gCubeDemo.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	gCubeDemo.ClearColor = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gCubeDemo.CubeColor = Vec4(0.85f, 0.0f, 0.0f, 1.0f);
	
	gCubeDemo.camera = InitCamera(Vec3(0.0f, 0.0f, -20.0f),
								  Vec3(0.0f, 1.0f, 0.0f),
								  Vec3(0.0f, 0.0f, 0.0f),
								  50.0f);
	
	gCubeDemo.projection = perspectiveRH(gCubeDemo.camera.fov,
										 (float)gClientWidth * (1.0f - gMENURATIO) / gClientHeight,
										 0.1f, 1000.0f);
	gCubeDemo.view = lookAtRH(gCubeDemo.camera.position,
							  gCubeDemo.camera.at,
							  gCubeDemo.camera.worldUp);
	
	gCubeDemo.world = M4x4(1.0f);
	gCubeDemo.rotationAxis = Vec3(1.0f, 0.0f, 0.0f);
	gCubeDemo.rotationAngle = 0.0f;
	gCubeDemo.scale = Vec3(1.0f, 1.0f, 1.0f);
	gCubeDemo.translate = Vec3(0.0f, 0.0f, 0.0f);
	
	
	gCubeDemo.shaderProgram = createShaderProgram("cube");
	
	glUniform4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "cubeColor"), 1, &(gCubeDemo.CubeColor.r));
}

static void	RenderCubeDemo()
{
	glPolygonMode(GL_FRONT_AND_BACK, gRasterMode);
	glViewport(0, 0, gClientWidth * (1.0f - gMENURATIO), gClientHeight);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(gCubeDemo.ClearColor.r, gCubeDemo.ClearColor.g, gCubeDemo.ClearColor.b, gCubeDemo.ClearColor.a);
	
	gCubeDemo.projection = perspectiveRH(gCubeDemo.camera.fov,
										 (float)gClientWidth * (1.0f - gMENURATIO) / gClientHeight,
										 0.1f, 1000.0f);
	
	gCubeDemo.view = lookAtRH(gCubeDemo.camera);
	
	gCubeDemo.rotationAxis = normalize(gCubeDemo.rotationAxis);
	M4x4	rotMat = rotateAxis(toRadians(gCubeDemo.rotationAngle), gCubeDemo.rotationAxis);
	M4x4	tranMat = translate(gCubeDemo.translate.x, gCubeDemo.translate.y, gCubeDemo.translate.z);
	M4x4	scalMat = scale(gCubeDemo.scale.x , gCubeDemo.scale.y, gCubeDemo.scale.z);
	
	gCubeDemo.world = M4x4(1.0f);
	
	gCubeDemo.world = gCubeDemo.world * scalMat;
	gCubeDemo.world = gCubeDemo.world * tranMat;
	gCubeDemo.world = gCubeDemo.world * rotMat;
	
	glUseProgram(gCubeDemo.shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "view"), 1, false, &(gCubeDemo.view.elems[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "projection"), 1, false, &(gCubeDemo.projection.elems[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "world"), 1, false, &(gCubeDemo.world.elems[0][0]));
	glUniform4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "cubeColor"), 1, &(gCubeDemo.CubeColor.r));
	glBindVertexArray(gCubeDemo.vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}



static void	InitLightDemo()
{
	float vertices[] = {
		//Positions				//Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	
	glGenVertexArrays(1, &(gLightDemo.vao));
	glBindVertexArray(gLightDemo.vao);
	
	glGenBuffers(1, &(gLightDemo.vbo));
	glBindBuffer(GL_ARRAY_BUFFER, gLightDemo.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	
	gLightDemo.shaderProgram = createShaderProgram("light");
	gLightDemo.clearColor = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gLightDemo.cubeColor = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
	
	gLightDemo.lightColor = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	gLightDemo.lightPosition = Vec4(0.0f, 5.0f, -5.0, 0.0f);
	gLightDemo.ambientStrength = 0.2f;
	gLightDemo.specularStrength = 0.5f;
	
	gLightDemo.camera = InitCamera(Vec3(0.0f, 0.0f, -20.0f),
								   Vec3(0.0f, 1.0f, 0.0f),
								   Vec3(0.0f, 0.0f, 0.0f),
								   50.0f);
	
	gLightDemo.view = lookAtRH(gLightDemo.camera.position,
							   gLightDemo.camera.at,
							   gLightDemo.camera.worldUp);
}

static void	RenderLightDemo()
{
	glPolygonMode(GL_FRONT_AND_BACK, gRasterMode);
	glViewport(0, 0, gClientWidth * (1.0f - gMENURATIO), gClientHeight);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(gLightDemo.clearColor.r, gLightDemo.clearColor.g, gLightDemo.clearColor.b, gLightDemo.clearColor.a);
	
	
	gLightDemo.projection = perspectiveRH(gLightDemo.camera.fov,
										  (float)gClientWidth * (1.0f - gMENURATIO) / gClientHeight,
										  0.1f, 1000.0f);
	
	gLightDemo.view = lookAtRH(gLightDemo.camera);
	
	glUseProgram(gLightDemo.shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(gLightDemo.shaderProgram, "view"), 1, false, &(gLightDemo.view.elems[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(gLightDemo.shaderProgram, "projection"), 1, false, &(gLightDemo.projection.elems[0][0]));
	glUniform4fv(glGetUniformLocation(gLightDemo.shaderProgram, "cubeColor"), 1, &(gLightDemo.cubeColor.r));
	glUniform3fv(glGetUniformLocation(gLightDemo.shaderProgram, "lightPos"), 1, &(gLightDemo.lightPosition.x));
	glUniform3fv(glGetUniformLocation(gLightDemo.shaderProgram, "lightColor"), 1, &(gLightDemo.lightColor.r));
	glUniform3fv(glGetUniformLocation(gLightDemo.shaderProgram, "viewPos"), 1, &(gLightDemo.camera.position.x));
	glUniform1fv(glGetUniformLocation(gLightDemo.shaderProgram, "ambientStrength"), 1, &(gLightDemo.ambientStrength));
	glUniform1fv(glGetUniformLocation(gLightDemo.shaderProgram, "specularStrength"), 1, &(gLightDemo.specularStrength));
	glBindVertexArray(gLightDemo.vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	
	glUseProgram(gCubeDemo.shaderProgram);
	
	M4x4	world = scale(0.25f, 0.25f, 0.25f);
	
	world = world * translate(gLightDemo.lightPosition.x, gLightDemo.lightPosition.y, gLightDemo.lightPosition.z);
	
	glUniformMatrix4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "view"), 1, false, &(gLightDemo.view.elems[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "projection"), 1, false, &(gLightDemo.projection.elems[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "world"), 1, false, &(world.elems[0][0]));
	glUniform4fv(glGetUniformLocation(gCubeDemo.shaderProgram, "cubeColor"), 1, &(gLightDemo.lightColor.r));
	
	glBindVertexArray(gCubeDemo.vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


static void	InitTerrainDemo()
{
	
	gTerrainDemo.currentMaxHeight = 0.0f;;
	gTerrainDemo.lastMaxHeight = 5.0f;
	
	gTerrainDemo.divisions = 64;
	gTerrainDemo.terrainSize = 20;
	
	gTerrainDemo.verticesSize = ((gTerrainDemo.divisions + 1) * (gTerrainDemo.divisions + 1) * 3) + ((gTerrainDemo.divisions + 1) * (gTerrainDemo.divisions + 1) * 2);
	gTerrainDemo.indicesSize = (gTerrainDemo.divisions) * (gTerrainDemo.divisions) * 3 * 2;
	
	
	glGenVertexArrays(1, &(gTerrainDemo.vao));
	glBindVertexArray(gTerrainDemo.vao);
	
	glGenBuffers(1, &(gTerrainDemo.vbo));
	glBindBuffer(GL_ARRAY_BUFFER, gTerrainDemo.vbo);
	glBufferData(GL_ARRAY_BUFFER, gTerrainDemo.verticesSize * sizeof(float), NULL, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	
	glGenBuffers(1, &(gTerrainDemo.ebo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gTerrainDemo.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, gTerrainDemo.indicesSize * sizeof(unsigned int), NULL, GL_DYNAMIC_DRAW);
	
	gTerrainDemo.clearColor = Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	gTerrainDemo.terrainColor = Vec4(0.0f, 154.0f / 255.0f, 23.0f / 255.0f, 1.0f);
	
	
	gTerrainDemo.camera = InitCamera(Vec3(0.0f, 10.0f, -20.0f),
									 Vec3(0.0f, 1.0f, 0.0f),
									 Vec3(0.0f, 0.0f, 0.0f),
									 50.0f);
	
	gTerrainDemo.projection = perspectiveRH(gTerrainDemo.camera.fov,
											(float)gClientWidth * (1.0f - gMENURATIO) / gClientHeight,
											0.1f, 1000.0f);
	gTerrainDemo.view = lookAtRH(gTerrainDemo.camera.position,
								 gTerrainDemo.camera.at,
								 gTerrainDemo.camera.worldUp);
	
	gTerrainDemo.shaderProgram = createShaderProgram("terrain");
	
	gTerrainDemo.tex = loadTexture("res/grass.jpg");
}

static void	__DiamondSquare(int row, int col, int size, float offset, Vec3* verts)
{
	unsigned int divisions = gTerrainDemo.divisions;
	int halfsz = (int)(size * 0.5f);
	
	int topLeft = row * (divisions + 1) + col;
	int bottomLeft = (row + size) *(divisions + 1) + col;
	
	int middle = (row + halfsz)*(divisions + 1) + (col + halfsz);
	
	verts[middle].y = (verts[topLeft].y + verts[topLeft + size].y + verts[bottomLeft + size].y + verts[bottomLeft + size].y) / 4 + glm::linearRand(-offset, offset);
	
	verts[topLeft + halfsz].y = (verts[topLeft].y + verts[topLeft + size].y + verts[middle].y) / 3 + glm::linearRand(-offset, offset);
	verts[middle - halfsz].y = (verts[topLeft].y + verts[bottomLeft].y + verts[middle].y) / 3 + glm::linearRand(-offset, offset);
	verts[middle + halfsz].y = (verts[topLeft + size].y + verts[bottomLeft + size].y + verts[middle].y) / 3 + glm::linearRand(-offset, offset);
	verts[bottomLeft + halfsz].y = (verts[bottomLeft].y + verts[bottomLeft + size].y + verts[middle].y) / 3 + glm::linearRand(-offset, offset);
}

static void	RenderTerrainDemo()
{
	glPolygonMode(GL_FRONT_AND_BACK, gRasterMode);
	glViewport(0, 0, gClientWidth * (1.0f - gMENURATIO), gClientHeight);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(gTerrainDemo.clearColor.r, gTerrainDemo.clearColor.g, gTerrainDemo.clearColor.b, gTerrainDemo.clearColor.a);
	
	
	gTerrainDemo.projection = perspectiveRH(gTerrainDemo.camera.fov,
											(float)gClientWidth * (1.0f - gMENURATIO) / gClientHeight,
											0.1f, 1000.0f);
	
	gTerrainDemo.view = lookAtRH(gTerrainDemo.camera);
	
	glUseProgram(gTerrainDemo.shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(gTerrainDemo.shaderProgram, "view"), 1, false, &(gTerrainDemo.view.elems[0][0]));
	glUniformMatrix4fv(glGetUniformLocation(gTerrainDemo.shaderProgram, "projection"), 1, false, &(gTerrainDemo.projection.elems[0][0]));
	glUniform4fv(glGetUniformLocation(gTerrainDemo.shaderProgram, "terrainColor"), 1, &(gTerrainDemo.terrainColor.r));
	
	if (gTerrainDemo.currentMaxHeight != gTerrainDemo.lastMaxHeight)
	{
		float*	vertices = (float*)alloca(sizeof(float) * gTerrainDemo.verticesSize);
		unsigned int*	indices = (unsigned int*)alloca(sizeof(unsigned int) * gTerrainDemo.indicesSize);
		__GenerateTerrain(vertices, indices);
		
		glBindVertexArray(gTerrainDemo.vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, gTerrainDemo.vbo);
		void* address = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		memcpy(address, (void*)vertices, gTerrainDemo.verticesSize * sizeof(float));
		glUnmapBuffer(GL_ARRAY_BUFFER);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gTerrainDemo.ebo);
		address = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		memcpy(address, (void*)indices, gTerrainDemo.indicesSize * sizeof(unsigned int));
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		
		gTerrainDemo.lastMaxHeight = gTerrainDemo.currentMaxHeight;
	}
	
	glUniform1f(glGetUniformLocation(gTerrainDemo.shaderProgram, "tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gTerrainDemo.tex);
	
	glBindVertexArray(gTerrainDemo.vao);
	glDrawElements(GL_TRIANGLES, gTerrainDemo.indicesSize, GL_UNSIGNED_INT, 0);
}

static void	__GenerateTerrain(float* vertices, u32* indices)
{
	float	divisionSize = (float)gTerrainDemo.terrainSize /(float)gTerrainDemo.divisions;
	float	halfSize = (float)gTerrainDemo.terrainSize * 0.5f;
	float	maxHeight = gTerrainDemo.currentMaxHeight;
	unsigned int divisions = gTerrainDemo.divisions;
	
	Vec3*	positions = (Vec3*)alloca(sizeof(Vec3) * (divisions + 1) * (divisions + 1));
	Vec2*	uvs = (Vec2*)alloca(sizeof(Vec2) * (divisions + 1) * (divisions + 1));
	
	for (unsigned int row = 0; row <= divisions; row++)
	{
		for (unsigned int col = 0; col <= divisions; col++)
		{
			positions[row*(divisions + 1) + col] = Vec3(-halfSize + divisionSize * col, 0.0f, halfSize - divisionSize * row);
			uvs[row*(divisions + 1) + col] = Vec2((float)row / (float)divisions, (float)col / (float)divisions);
		}
	}
	if (gTerrainDemo.currentMaxHeight != 0.0f)
	{
		positions[0].y = glm::linearRand(-maxHeight, maxHeight);
		positions[divisions + 1].y = glm::linearRand(-maxHeight, maxHeight);
		positions[(divisions + 1)*(divisions + 1) - 1].y = glm::linearRand(-maxHeight, maxHeight);
		positions[((divisions + 1)*(divisions + 1)) - 1 - divisions].y = glm::linearRand(-maxHeight, maxHeight);
		
		int iterations = log2(divisions);
		
		int numcarre = 1;
		int carreDiv = divisions;
		
		for (unsigned int i = 0; i < iterations; i++)
		{
			unsigned int row = 0;
			for (unsigned int j = 0; j < numcarre; j++)
			{
				unsigned int col = 0;
				for (unsigned int k = 0; k < numcarre; k++)
				{
					__DiamondSquare(row, col, carreDiv, maxHeight, positions);
					col += carreDiv;
				}
				row += carreDiv;
			}
			numcarre *= 2;
			carreDiv /= 2;
			maxHeight *= 0.5f;
		}
	}
	unsigned int pointer = 0; 
	unsigned int i = 0; 
	int sz = ((divisions + 1)*(divisions + 1) * 3) + ((divisions + 1)*(divisions + 1) * 2);
	while ((i < sz) && (pointer < (divisions + 1)*(divisions + 1)))
	{
		vertices[i] = positions[pointer].x;
		vertices[i + 1] = positions[pointer].y;
		vertices[i + 2] = positions[pointer].z;
		vertices[i + 3] = uvs[pointer].x;
		vertices[i + 4] = uvs[pointer].y;
		i += 5;
		pointer += 1;
	}
	
	
	i = 0;
	
	for (unsigned int row = 0; row <= divisions; row++)
	{
		for (unsigned int col = 0; col <= divisions; col++)
		{
			if (row < divisions && col < divisions)
			{
				int topLeft = row * (divisions + 1) + col;
				int bottomLeft = (row + 1)*(divisions + 1) + col;
				
				indices[i] = topLeft;
				indices[i + 1] = topLeft + 1;
				indices[i + 2] = bottomLeft + 1;
				
				indices[i + 3] = topLeft;
				indices[i + 4] = bottomLeft + 1;
				indices[i + 5] = bottomLeft;
				
				i += 6;
			}
		}
	}
}

