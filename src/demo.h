#ifndef DEMO_H
#define DEMO_H

#include "math.h"
#include "camera.h"

struct	TriangleObject
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int shaderProgram;
	unsigned int tex;
	float		blendValue;
	Vec4	 Color1;
	Vec4	 Color2;
	Vec4	 Color3;
	Vec4	 ClearColor;
};

struct	SquareObject
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shaderProgram;
	unsigned int tex;
	float		blendValue;
	Vec4		   Color;
	Vec4		   ClearColor;
	
	M4x4		projection;
	M4x4		view;
	bool		projectionEnabled;
};

struct	CubeObject
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shaderProgram;
	//unsigned int tex;
	Vec4		   ClearColor;
	Vec4		   CubeColor;
	
	Camera	  camera;
	M4x4		projection;
	M4x4		view;
	M4x4		world;
	Vec3		rotationAxis;
	float	   rotationAngle;
	Vec3		scale;
	Vec3		translate;
	
};


struct	LightObject
{
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	shaderProgram;
	
	Vec4			clearColor;
	Vec4			cubeColor;
	
	Vec4			lightColor;
	Vec4			lightPosition;
	float		   ambientStrength;
	float		   specularStrength;
	
	Camera		  camera;
	M4x4			projection;
	M4x4			view;
};

struct	TerrainObject
{
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	ebo;
	unsigned int	tex;
	unsigned int	shaderProgram;
	
	unsigned int	divisions;
	unsigned int	terrainSize;
	
	unsigned int	verticesSize;
	unsigned int	indicesSize;
	
	float		   currentMaxHeight;
	float		   lastMaxHeight;
	
	Vec4			clearColor;
	Vec4			terrainColor;
	
	Camera		  camera;
	M4x4			projection;
	M4x4			view;
};


static TriangleObject		gTriangleDemo;
static SquareObject		  gSquareDemo;
static CubeObject			gCubeDemo;
static LightObject		   gLightDemo;
static TerrainObject		 gTerrainDemo;

static void	InitTriangleDemo();
static void	RenderTriangleDemo();
static void	CleanTriangleDemo();

static void	InitSquareDemo();
static void	RenderSquareDemo();
static void	CleanSquareDemo();

static void	InitCubeDemo();
static void	RenderCubeDemo();
static void	CleanCubeDemo();

static void	InitLightDemo();
static void	RenderLightDemo();
static void	CleanLightDemo();

static void	InitTerrainDemo();
static void	__DiamondSquare(int row, int col, int size, float offset, Vec3* verts);
static void	__GenerateTerrain(float* vertices, u32* indices);
static void	RenderTerrainDemo();
static void	CleanTerrainDemo();

#endif //DEMO_H
