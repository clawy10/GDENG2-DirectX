#include "MenuScreen.h"
#include "UIManager.h"
#include "CreditsScreen.h"
#include "ColorPickerScreen.h"
#include "ResizeObjectScreen.h"
#include "ComponentsScreen.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"
#include "PhysicsComponent.h"
#include "EngineBackend.h"

MenuScreen::MenuScreen(std::string name) : AUIScreen(name)
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::CreateMesh(PrimitiveType type)
{
	Mesh* mesh = GraphicsEngine::getInstance()->GetMeshManager()->createPrimitiveMesh(type);
	GameObjectManager::getInstance()->AddObject(mesh);
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
			if (EngineBackend::getInstance()->GetMode() == EngineBackend::EDITOR)
			{
				SceneWriter writer = SceneWriter("..\\Assets\\Scenes");
				writer.WriteToFile();
			}
			else
			{
				std::cout << "Cannot save in current mode!";
			}
			
		}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Objects"))
	{
		if (ImGui::MenuItem("Create Cube"))
		{
			this->CreateMesh(PrimitiveType::Cube);
		}

		if (ImGui::MenuItem("Create Plane"))
		{
			this->CreateMesh(PrimitiveType::Plane);
		}
		
		if (ImGui::MenuItem("Create Cylinder"))
		{
			this->CreateMesh(PrimitiveType::Cylinder);
		}

		if (ImGui::MenuItem("Create Capsule"))
		{
			this->CreateMesh(PrimitiveType::Capsule);
		}

		if (ImGui::MenuItem("Create Sphere"))
		{
			this->CreateMesh(PrimitiveType::Sphere);
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Windows"))
	{
		if (ImGui::MenuItem("Components"))
		{
			UIManager::getInstance()->AddUIScreen(new ComponentsScreen(uinames.COMPONENTS_SCREEN));
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

