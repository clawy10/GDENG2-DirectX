#include "GameObjectManager.h"
#include "EditorAction.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize(void* shaderByteCode, size_t size)
{
	sharedInstance = new GameObjectManager();
	sharedInstance->shader_byte_code = shaderByteCode;
	sharedInstance->sizeShader = size;
}

void GameObjectManager::destroy()
{
	if (sharedInstance != nullptr)
	{
		sharedInstance->DeleteAllObjects();
	}
}

void GameObjectManager::AddObject(AGameObject* object)
{
	object->Initialize(this->shader_byte_code, this->sizeShader);
	this->objectList.push_back(object);

	if (this->objectMap[object->GetName()] != nullptr)
	{
		int count = 1;
		std::string revisedName = object->GetName() + "(" + std::to_string(count) + ")";
		while (this->objectMap[revisedName] != nullptr) {
			count++;
			revisedName = object->GetName() + "(" + std::to_string(count) + ")";
		}
		object->SetName(revisedName);
	}

	this->objectMap[object->GetName()] = object;
}

void GameObjectManager::DeleteObject(AGameObject* object)
{
	int index = -1;
	for (int i = 0; i < this->objectList.size(); i++)
	{
		if (this->objectList[i] == object)
		{
			index = i;
			break;
		}
	}

	if (index != -1) {
		std::cout << "Deleted " + this->objectList[index]->GetName() << std::endl;
		this->objectList[index]->release();
		this->objectList.erase(this->objectList.begin() + index);
	}
}

void GameObjectManager::DeleteAllObjects()
{
	for (int i = 0; i < this->objectList.size(); i++)
	{
		this->objectList[i]->release();
	}
}

void GameObjectManager::SelectObject(std::string name)
{
	this->selectedObject = this->GetObjectByName(name);
}

void GameObjectManager::SelectObject(AGameObject* object)
{
	this->selectedObject = object;
}

void GameObjectManager::SaveEditStates()
{
	for (int i = 0; i < this->objectList.size(); i++)
	{
		this->objectList[i]->SaveEditState();
	}
}

void GameObjectManager::RestoreEditStates()
{
	for (int i = 0; i < this->objectList.size(); i++)
	{
		this->objectList[i]->RestoreEditState();
	}
}

void GameObjectManager::ApplyEditorAction(EditorAction* action)
{
	AGameObject* gameObject = this->GetObjectByName(action->GetOwnerName());
	if (gameObject != nullptr)
	{
		gameObject->SetPosition(action->GetStoredPos());
		gameObject->SetRotation(action->GetStoredOrientation());
		gameObject->SetScale(action->GetStoredScale());
	}
}

AGameObject* GameObjectManager::GetSelectedObject()
{
	return this->selectedObject;
}

AGameObject* GameObjectManager::GetObjectByName(std::string name)
{
	return this->objectMap[name];
}

std::vector<AGameObject*> GameObjectManager::GetAllObjects()
{
	return this->objectList;
}

void GameObjectManager::UpdateObjects(double deltaTime)
{
	for (int i = 0 ; i < this->objectList.size(); i++)
	{
		this->objectList[i]->Update(deltaTime);
	}
}

void GameObjectManager::DrawObjects(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (int i = 0; i < this->objectList.size(); i++)
	{
		this->objectList[i]->Draw(width, height, vertexShader, pixelShader);
	}
}

GameObjectManager::GameObjectManager()
{
	
}

GameObjectManager::~GameObjectManager()
{
	
}
