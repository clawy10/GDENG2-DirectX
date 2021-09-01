#include "ResizeObjectScreen.h"
#include "GameObjectManager.h"
ResizeObjectScreen::ResizeObjectScreen(std::string name) :AUIScreen(name)
{
	
}

ResizeObjectScreen::~ResizeObjectScreen()
{
}

void ResizeObjectScreen::DrawUI()
{
	ImGui::Begin("Resize Object");
	
	if (GameObjectManager::getInstance()->GetSelectedObject() != nullptr)
	{
		AGameObject* selectedObject = GameObjectManager::getInstance()->GetSelectedObject();
		this->size[0] = selectedObject->GetScale().x;
		this->size[1] = selectedObject->GetScale().y;
		this->size[2] = selectedObject->GetScale().z;
		
		if (ImGui::DragFloat3("Scale", this->size))
		{
			Vector3D newScale(this->size[0], this->size[1], this->size[2]);
			GameObjectManager::getInstance()->GetSelectedObject()->SetScale(newScale);
		}
	}
	else
	{
		ImGui::Text("No object selected!");
	}
	
	ImGui::End();
}
