#include "EditorActionScreen.h"
#include "ActionHistory.h"
#include "GameObjectManager.h"
#include "EngineBackend.h"

EditorActionScreen::EditorActionScreen(std::string name) : AUIScreen(name)
{
}

EditorActionScreen::~EditorActionScreen()
{
}

void EditorActionScreen::DrawUI()
{
	if (EngineBackend::getInstance()->GetMode() != EngineBackend::EDITOR)
	{
		return;
	}
	
	ImGui::Begin("Actions");

	ImGui::SameLine();
	if (ImGui::Button("Undo"))
	{
		if (ActionHistory::getInstance()->HasRemainingUndoActions())
		{
			GameObjectManager::getInstance()->ApplyEditorAction(ActionHistory::getInstance()->UndoAction());
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Redo"))
	{
		if (ActionHistory::getInstance()->HasRemainingRedoActions()) {
			std::cout << "Redo" << std::endl;
			GameObjectManager::getInstance()->ApplyEditorAction(ActionHistory::getInstance()->RedoAction());
		}
	}

	ImGui::End();
}
