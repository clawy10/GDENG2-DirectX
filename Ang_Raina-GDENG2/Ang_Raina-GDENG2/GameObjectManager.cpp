#include "GameObjectManager.h"

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

	this->objectMap.insert({ object->GetName(), object });
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

AGameObject* GameObjectManager::GetObjectByName(std::string name)
{
	return this->objectMap[name];
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
