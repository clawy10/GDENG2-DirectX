#include "MenuScreen.h"
#include "UIManager.h"
#include "CreditsScreen.h"
#include "ColorPickerScreen.h"
#include "ResizeObjectScreen.h"
#include "GraphicsEngine.h"
#include "MeshManager.h"
#include "GameObjectManager.h"

MenuScreen::MenuScreen(std::string name) : AUIScreen(name)
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::DrawUI()
{
	ImGui::BeginMainMenuBar();

	UINames uinames;
	
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Open"))
		{
			// do something
		}
		if (ImGui::MenuItem("Save"))
		{
			// do something
		}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Objects"))
	{
		if (ImGui::MenuItem("Create Cube"))
		{
			Mesh* mesh = GraphicsEngine::getInstance()->GetMeshManager()->createPrimitiveMesh(Mesh::Cube);
			GameObjectManager::getInstance()->AddObject(mesh);
		}
		if (ImGui::MenuItem("Create Cylinder"))
		{
			Mesh* mesh = GraphicsEngine::getInstance()->GetMeshManager()->createPrimitiveMesh(Mesh::Cylinder);
			GameObjectManager::getInstance()->AddObject(mesh);
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Windows"))
	{
		if (ImGui::MenuItem("Color Picker"))
		{
			UIManager::getInstance()->AddUIScreen(new ColorPickerScreen(uinames.COLORPICKER_SCREEN));
		}
		if (ImGui::MenuItem("Object Resizer"))
		{
			UIManager::getInstance()->AddUIScreen(new ResizeObjectScreen(uinames.OBJECTRESIZER_SCREEN));
		}
		ImGui::EndMenu();
	}
	
	if (ImGui::BeginMenu("About"))
	{
		if (ImGui::MenuItem("Credits"))
		{
			UIManager::getInstance()->AddUIScreen(new CreditsScreen(uinames.CREDITS_SCREEN));
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}
