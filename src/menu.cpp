#include "menu.h"

bool	InitImGui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	gGuiIO = ImGui::GetIO();
	
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	if (!ImGui_ImplOpenGL3_Init("#version 330"))
		return (false);
	return (true);
}

void	 CreateImGuiFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize(ImVec2(gClientWidth * gMENURATIO, gClientHeight));
	ImGui::SetNextWindowPos(ImVec2(gClientWidth * (1.0f - gMENURATIO), 0));
}

void	 AppChooseMenu()
{
	bool	menuDrawn = true;
	ImGuiWindowFlags	menuFlags = ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_AlwaysAutoResize
		| ImGuiWindowFlags_NoCollapse;
	if (ImGui::Begin(" ", &menuDrawn, menuFlags))
	{
		switch(gCurrentMenuType)
		{
			case MENUTYPE::TRIANGLE:{
				if (ImGui::Button("Previous"))
					gCurrentMenuType = MENUTYPE::MAIN;
				ImGui::ColorEdit4("Color1", &(gTriangleDemo.Color1.r));
				ImGui::ColorEdit4("Color2", &(gTriangleDemo.Color2.r));
				ImGui::ColorEdit4("Color3", &(gTriangleDemo.Color3.r));
				ImGui::SliderFloat("Blend Value", &(gTriangleDemo.blendValue), 0.0f, 1.0f);
				RenderTriangleDemo();
			}break;
			case MENUTYPE::SQUARE:{
				if (ImGui::Button("Previous"))
					gCurrentMenuType = MENUTYPE::MAIN;
				ImGui::ColorEdit4("Color", &(gSquareDemo.Color.r));
				ImGui::SliderFloat("Blend Value", &(gSquareDemo.blendValue), 0.0f, 1.0f);
				ImGui::Checkbox("Enable Orthographic Projection", &(gSquareDemo.projectionEnabled));
				/*if (gSquareDemo.projectionEnabled)
				{
					ImGui::SliderFloat("Left", &(gSquareDemo.left), -19.0f , 19.0f);
					ImGui::SliderFloat("Right", &(gSquareDemo.right), -19.0f , 19.0f);
					ImGui::SliderFloat("Bottom", &(gSquareDemo.bottom), -10.0f , 10.0f);
					ImGui::SliderFloat("Top", &(gSquareDemo.top), -10.0f , 10.0f);
				}*/
				RenderSquareDemo();
			}break;
			case MENUTYPE::CUBE:{
				if (ImGui::Button("Previous"))
					gCurrentMenuType = MENUTYPE::MAIN;
				
				ImGui::ColorEdit4("Color", &(gCubeDemo.CubeColor.r));
				ImGui::Text("Edit Cube");
				ImGui::SliderFloat3("Position", gCubeDemo.translate.e, -10.0f, 10.0f);
				ImGui::SliderFloat3("Scale", gCubeDemo.scale.e, 0.0f, 10.0f);
				ImGui::SliderFloat3("Rotation Axis", gCubeDemo.rotationAxis.e, 0.0f, 1.0f);
				ImGui::SliderFloat("Rotation Angle", &(gCubeDemo.rotationAngle), 0.0f, 359.9f);
				
				RenderCubeDemo();
			}break;
			case MENUTYPE::LIGHTING:{
				if (ImGui::Button("Previous"))
					gCurrentMenuType = MENUTYPE::MAIN;
				ImGui::ColorEdit4("Cube Color", &(gLightDemo.cubeColor.r));
				ImGui::Text("Edit Light");
				ImGui::ColorEdit4("Color", &(gLightDemo.lightColor.r));
				ImGui::SliderFloat3("Position", gLightDemo.lightPosition.e, -20.0f, 20.f);
				ImGui::SliderFloat("Ambient Strength", &(gLightDemo.ambientStrength), 0.0f, 1.0f);
				ImGui::SliderFloat("Specular Strength", &(gLightDemo.specularStrength), 0.0f, 1.0f);
				
				RenderLightDemo();
			}break;
			case MENUTYPE::TERRAIN_GEN:{
				if (ImGui::Button("Previous"))
					gCurrentMenuType = MENUTYPE::MAIN;
				ImGui::SliderFloat("Max Height", &(gTerrainDemo.currentMaxHeight), 0.0f, 5.0f);
				
				RenderTerrainDemo();
			}break;
			default:
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearColor(0.2f, 0.8f, 0.0f, 1.0f);
				
				if (ImGui::CollapsingHeader("ABOUT", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::TextWrapped("About this Demo: ");;
					ImGui::Indent();
					ImGui::TextWrapped("This Demo was Created to present A Uni Project Entitled");
					ImGui::TextWrapped("Introduction To Computer Graphics Using OpenGL");
					ImGui::TextWrapped("originally written the summer of 2016");
					ImGui::TextWrapped("The code was modified to make the whole project compile as one compilation unit & updated to the latest DearImGui version");
					ImGui::Unindent();
				}
				if (ImGui::CollapsingHeader("CONTROLS", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Bullet();
					ImGui::TextWrapped("Arrows, WSDA: Move The Camera");
					ImGui::Bullet();
					ImGui::TextWrapped("M: Switch Between Fill and Line Modes");
					ImGui::Bullet();
					ImGui::TextWrapped("Left Click : Focus Mode");
					ImGui::Bullet();
					ImGui::TextWrapped("Mouse Movement : Hold Left Control (FOCUS)");
					ImGui::Bullet();
					ImGui::TextWrapped("Esc: Quit Focus Mode");;
				}
				if (ImGui::CollapsingHeader("Demos", ImGuiTreeNodeFlags_DefaultOpen))
				{
					if (ImGui::Button("TRIANGLE", ImVec2(gClientWidth * gMENURATIO, 20.0f)))
					{
						gCurrentMenuType = MENUTYPE::TRIANGLE;
						break;
					}
					if (ImGui::Button("SQUARE", ImVec2(gClientWidth * gMENURATIO, 20.0f)))
					{
						gCurrentMenuType = MENUTYPE::SQUARE;
						break;
					}
					if (ImGui::Button("GOING 3D WITH A CUBE", ImVec2(gClientWidth * gMENURATIO, 20.0f)))
					{
						gCurrentMenuType = MENUTYPE::CUBE;
						break;
					}
					if (ImGui::Button("LIGHTING", ImVec2(gClientWidth * gMENURATIO, 20.0f)))
					{
						gCurrentMenuType = MENUTYPE::LIGHTING;
						break;
					}
					if (ImGui::Button("TERRAIN GENRATION", ImVec2(gClientWidth * gMENURATIO, 20.0f)))
					{
						gCurrentMenuType = MENUTYPE::TERRAIN_GEN;
						break;
					}
				}
			}break;
		}
		
		ImGui::End();
	}
	
	
}

void	 DrawImGuiFrame()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}