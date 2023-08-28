#ifndef MENU_H
#define MENU_H
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#ifdef IMGUI_IMPLEMENTATION
#include <imgui.cpp>
#include <imgui_demo.cpp>
#include <imgui_draw.cpp>
#include <imgui_tables.cpp>
#include <imgui_widgets.cpp>
#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_glfw.cpp>
#endif


enum MENUTYPE
{
	MAIN,
	TRIANGLE,
	SQUARE,
	CUBE,
	LIGHTING,
	TERRAIN_GEN,
};


static const float  gMENURATIO = 0.25f;
static ImGuiIO	  gGuiIO;
static MENUTYPE	 gCurrentMenuType = MENUTYPE::MAIN;

bool	 InitImGui(GLFWwindow* window);
void	 CreateImGuiFrame();
void	 AppChooseMenu();
void	 DrawImGuiFrame();


#endif
