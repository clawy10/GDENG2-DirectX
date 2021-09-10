#pragma once
#include <vector>
#include <unordered_map>
#include "AGameObject.h"

class EditorAction;

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	static void initialize(void* shaderByteCode, size_t size);
	static void destroy();

	void AddObject(AGameObject* object);
	void UpdateObjects(double deltaTime);
	void DrawObjects(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);

	void DeleteObject(AGameObject* object);
	void DeleteAllObjects();

	void SelectObject(std::string name);
	void SelectObject(AGameObject* object);

	void SaveEditStates();
	void RestoreEditStates();

	void ApplyEditorAction(EditorAction* action);
	
	AGameObject* GetSelectedObject();
	AGameObject* GetObjectByName(std::string name);
	std::vector<AGameObject*> GetAllObjects();
	
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

	AGameObject* selectedObject = nullptr; 
};

