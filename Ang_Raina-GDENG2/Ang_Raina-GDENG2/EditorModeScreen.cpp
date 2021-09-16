#include "EditorModeScreen.h"
#include "BaseComponentSystem.h"
#include "EngineBackend.h"
#include "GameObjectManager.h"
#include "PhysicsSystem.h"

EditorModeScreen::EditorModeScreen(std::string name) : AUIScreen(name)
{
}

EditorModeScreen::~EditorModeScreen()
{
}

void EditorModeScreen::DrawUI()
{
	ImGui::Begin("Editor Mode");
	
	if (EngineBackend::getInstance()->GetMode() == EngineBackend::EDITOR)
	{
		if (ImGui::Button("Play"))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::PLAY);
			GameObjectManager::getInstance()->SaveEditStates();
		}
	}
	else if (EngineBackend::getInstance()->GetMode() == EngineBackend::PLAY)
	{
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::EDITOR);
			GameObjectManager::getInstance()->RestoreEditStates();
			BaseComponentSystem::getInstance()->GetPhysicsSystem()->StopUpdating();
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause"))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::PAUSED);
		}
	}
	else if (EngineBackend::getInstance()->GetMode() == EngineBackend::PAUSED)
	{
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::EDITOR);
			GameObjectManager::getInstance()->RestoreEditStates();
			BaseComponentSystem::getInstance()->GetPhysicsSystem()->StopUpdating();
		}
		ImGui::SameLine();
		if (ImGui::Button("Resume"))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::PLAY);
		}
		ImGui::SameLine();
		if (ImGui::Button("Framestep"))
		{
			EngineBackend::getInstance()->StartFrameStep();
		}
	}

	ImGui::End();
}
