#include "ResizeObjectScreen.h"
#include "GameObjectManager.h"
ResizeObjectScreen::ResizeObjectScreen(std::string name) :AUIScreen(name)
{
	this->selectedObject = GameObjectManager::getInstance()->GetObjectByName("teapot");
	this->size[0] = this->selectedObject->GetScale().x;
	this->size[1] = this->selectedObject->GetScale().y;
	this->size[2] = this->selectedObject->GetScale().z;
}

ResizeObjectScreen::~ResizeObjectScreen()
{
}

void ResizeObjectScreen::DrawUI()
{
	ImGui::Begin("Resize Teapot");
	ImGui::DragFloat3("Scale", this->size);
	
	if (this->selectedObject != nullptr)
	{
		
		this->selectedObject->SetScale(this->size[0], this->size[1], this->size[2]);
	}
	
	ImGui::End();
}

void ResizeObjectScreen::SelectObject(AGameObject* gameObject)
{
	this->selectedObject = gameObject;
}
