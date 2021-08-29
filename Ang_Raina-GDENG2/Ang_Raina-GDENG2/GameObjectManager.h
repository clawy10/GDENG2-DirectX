#pragma once
#include <vector>
#include <unordered_map>
#include "AGameObject.h"

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	static void initialize(void* shaderByteCode, size_t size);
	static void destroy();

	void AddObject(AGameObject* object, Vector3D color);
	void UpdateObjects(double deltaTime);
	void DrawObjects(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);

	void DeleteObject(AGameObject* object);
	void DeleteAllObjects();

	AGameObject* GetObjectByName(std::string);
	
private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

	void* shader_byte_code = nullptr;
	size_t sizeShader = 0;
	
	std::vector<AGameObject*> objectList;
	std::unordered_map< std::string, AGameObject*> objectMap;
};

