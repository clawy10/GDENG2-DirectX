#include "EditorModeScreen.h"
#include "EngineBackend.h"

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
		if (ImGui::Button("Play", ImVec2(100, 0)))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::PLAY);
		}
	}
	else if (EngineBackend::getInstance()->GetMode() == EngineBackend::PLAY)
	{
		if (ImGui::Button("Stop", ImVec2(100, 0)))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::EDITOR);
		}
		if (ImGui::Button("Pause", ImVec2(100, 0)))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::PAUSED);
		}
	}
	else if (EngineBackend::getInstance()->GetMode() == EngineBackend::PAUSED)
	{
		if (ImGui::Button("Stop", ImVec2(100, 0)))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::EDITOR);
		}
		if (ImGui::Button("Resume", ImVec2(100, 0)))
		{
			EngineBackend::getInstance()->SetMode(EngineBackend::PLAY);
		}
		if (ImGui::Button("Framestep", ImVec2(100, 0)))
		{
			EngineBackend::getInstance()->StartFrameStep();
		}
	}

	ImGui::End();
}
