#define IMGUI_IMPLEMENTATION
#define GLEW_STATIC
#include <GL/glew.h>

static int	gClientWidth = 1366;
static int	gClientHeight = 768;
static const char*	gWindowName = "PFE Demo";
static GLenum	gRasterMode = GL_FILL;

static double	lastMousePosX = 0;
static double	lastMousePosY = 0;
static bool	  firstTimeMouseInput = true;
static bool	  mouseMove = false;

static bool	  gKeysState[512];

#define SSE_ENABLE
#include "math.h"
#include "camera.h"
#include "demo.h"
#include "menu.h"
#include "gltools.h"

#include "gltools.cpp"
#include "menu.cpp"
#include "demo.cpp"
#include "math.cpp"
#include "camera.cpp"

static void	ErrorCallbackGLFW(int error, const char* desc);
static void	WindowResizeGLFW(GLFWwindow* window, int width, int height);
static void	KeyCallbackGLFW(GLFWwindow* window, int key, int scancode, int action, int mods);
static void	mouseCallbackGLFW(GLFWwindow* window, double xPos, double yPos);




int	main(int argc, char **argv)
{
	GLFWwindow*		window;
	glfwSetErrorCallback(ErrorCallbackGLFW);
	
	if (!glfwInit())
	{
		// TODO(Yassine): Error Handling and logging system.
		return (-1);
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	window = glfwCreateWindow(gClientWidth, gClientHeight, gWindowName,
							  NULL, NULL);
	if (!window)
	{
		return (-1);
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, WindowResizeGLFW);
	glfwSetKeyCallback(window, KeyCallbackGLFW);
	glfwSetCursorPosCallback(window, mouseCallbackGLFW);
	glfwSwapInterval(1);
	
	glEnable(GL_DEPTH_TEST);
	
	
	if(!InitImGui(window))
	{
		// TODO(Yassine): error logging.
		return (1);
	}
	bool	show_demo_window = true;
	
	
	// NOTE(Yassine): Triangle Demo Initialization
	InitTriangleDemo();
	InitSquareDemo();
	InitCubeDemo();
	InitLightDemo();
	InitTerrainDemo();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.8f, 0.0f, 1.0f);
	//glViewport(0, 0, 10, gClientHeight);
	
	
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
		{
			Camera*	currentCamera = NULL;
			
			if (gCurrentMenuType == MENUTYPE::CUBE)
				currentCamera = &(gCubeDemo.camera);
			else if (gCurrentMenuType == MENUTYPE::LIGHTING)
				currentCamera = &(gLightDemo.camera);
			else if (gCurrentMenuType == MENUTYPE::TERRAIN_GEN)
				currentCamera = &(gTerrainDemo.camera);
			
			if (currentCamera)
			{
				if (gKeysState[GLFW_KEY_UP] || gKeysState[GLFW_KEY_W])
					CameraForwardStep(*currentCamera, 0.25f);
				if (gKeysState[GLFW_KEY_DOWN] || gKeysState[GLFW_KEY_S])
					CameraForwardStep(*currentCamera, -0.25f);
				if (gKeysState[GLFW_KEY_RIGHT] || gKeysState[GLFW_KEY_D])
					CameraSideStep(*currentCamera, 0.25f);
				if (gKeysState[GLFW_KEY_LEFT] || gKeysState[GLFW_KEY_A])
					CameraSideStep(*currentCamera, -0.25f);
				if (gKeysState[GLFW_KEY_LEFT_CONTROL])
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					mouseMove = true;
				}
				if (!gKeysState[GLFW_KEY_LEFT_CONTROL])
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					mouseMove = false;
				}
				
			}
		}
		
		CreateImGuiFrame();
		
		AppChooseMenu();
		
		DrawImGuiFrame();
		
		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return (0);
}

static void	ErrorCallbackGLFW(int error, const char* desc)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, desc);
}

static void	WindowResizeGLFW(GLFWwindow* window, int width, int height)
{
	if (width < 800 && height < 600)
	{
		glfwSetWindowSize(window, 800, 600);
		gClientWidth = 800;
		gClientHeight = 600;
	}
	else if (width < 800)
	{
		glfwSetWindowSize(window, 800, height);
		gClientWidth = 800;
		gClientHeight = height;
	}
	else if (height < 600)
	{
		glfwSetWindowSize(window, width, 600);
		gClientWidth = width;
		gClientHeight = 800;
	}
	else
	{
		gClientWidth = width;
		gClientHeight = height;
	}
	//glViewport(0, 0, gClientWidth * (1.0f - gMENURATIO), gClientHeight);
}


static void	KeyCallbackGLFW(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		if (gRasterMode == GL_FILL)
			gRasterMode = GL_LINE;
		else
			gRasterMode = GL_FILL;
	}
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
		gKeysState[key] = true;
	if (action == GLFW_RELEASE)
		gKeysState[key] = false;
	
}

static void	mouseCallbackGLFW(GLFWwindow* window, double xPos, double yPos)
{
	if (firstTimeMouseInput)
	{
		lastMousePosX = xPos;
		lastMousePosY = yPos;
		firstTimeMouseInput = false;
	}
	
	double yOffset = lastMousePosY - yPos;
	double xOffset = lastMousePosX - xPos;
	
	lastMousePosX = xPos;
	lastMousePosY = yPos;
	
	Camera*	currentCamera = NULL;
	
	if (gCurrentMenuType == MENUTYPE::CUBE)
		currentCamera = &(gCubeDemo.camera);
	else if (gCurrentMenuType == MENUTYPE::LIGHTING)
		currentCamera = &(gLightDemo.camera);
	else if (gCurrentMenuType == MENUTYPE::TERRAIN_GEN)
		currentCamera = &(gTerrainDemo.camera);
	
	if (currentCamera && mouseMove)
	{
		if (yOffset)
			CameraPitch(*currentCamera, yOffset * 0.1f);
		if (xOffset)
			CameraYaw(*currentCamera, xOffset * 0.1f);
	}
}