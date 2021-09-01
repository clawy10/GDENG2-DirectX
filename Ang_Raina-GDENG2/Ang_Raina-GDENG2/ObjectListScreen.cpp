#include "ObjectListScreen.h"
#include "GameObjectManager.h"

ObjectListScreen::ObjectListScreen(std::string name) : AUIScreen(name)
{
}

ObjectListScreen::~ObjectListScreen()
{
}

void ObjectListScreen::DrawUI()
{
	ImGui::Begin("Object List");
	std::vector<AGameObject*> objectList = GameObjectManager::getInstance()->GetAllObjects();
	for (int i = 0; i < objectList.size(); i++)
	{
		if(ImGui::Button(objectList[i]->GetName().c_str(), ImVec2(100, 0)))
		{
			GameObjectManager::getInstance()->SelectObject(objectList[i]);
		}
	}
	
	ImGui::End();
}
