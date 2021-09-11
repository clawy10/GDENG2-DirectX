#pragma once
#include <string>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AQuaternion.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "AComponent.h"
#include <iostream>
#include <vector>
#include "MathTools.h"

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
};

class EditorAction;

class AGameObject
{
public:
	AGameObject(std::string name);
	
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3D position);
	Vector3D GetPosition();
	
	void SetRotation(float x, float y, float z, float w);
	void SetRotation(Vector3D rotation, float w);
	void SetRotation(AQuaternion quaternion);
	Vector3D GetRotation();
	AQuaternion GetOrientation();
	
	void SetScale(float x, float y, float z);
	void SetScale(Vector3D scale);
	Vector3D GetScale();

	std::string GetName();
	void SetName(std::string name);

	virtual void Initialize(void* shaderByteCode, size_t sizeShader);
	virtual void Update(double deltaTime);
	virtual void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);

	void AttachComponent(AComponent* component);
	void DetachComponent(AComponent* component);
	
	AComponent* FindComponentByName(std::string name); 

	void SaveEditState();
	void RestoreEditState();
	
	void release();
	
	~AGameObject();

protected:
	std::string name; 
	
	Vector3D position = Vector3D(0, 0, 0);
	AQuaternion orientation;
	Vector3D scale = Vector3D(1, 1, 1);

	std::vector<AComponent*> componentList;

	virtual void Awake();

private:
	EditorAction* lastEditState = nullptr;
	
private:
	friend class GameObjectManager;
};

