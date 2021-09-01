#pragma once
#include <string>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "AComponent.h"
#include <iostream>
#include <vector>

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

struct AQuaternion
{
	AQuaternion()
	{
		
	}
	
	AQuaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	AQuaternion(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;
};

class AGameObject
{
public:
	AGameObject(std::string name);
	
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3D position);
	Vector3D GetPosition();
	
	void SetRotation(float x, float y, float z);
	void SetRotation(float x, float y, float z, float w);
	void SetRotation(Vector3D rotation);
	Vector3D GetRotation();
	AQuaternion GetOrientation();
	
	void SetScale(float x, float y, float z);
	void SetScale(Vector3D scale);
	Vector3D GetScale();

	std::string GetName();

	virtual void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color);
	virtual void Update(double deltaTime);
	virtual void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);

	void AttachComponent(AComponent* component);
	void DetachComponent(AComponent* component);
	
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
	friend class GameObjectManager;
};

