#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <iostream>

struct vertex
{
	Vector3D position;
	Vector3D color; 
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
	void SetRotation(Vector3D rotation);
	Vector3D GetRotation();
	
	void SetScale(float x, float y, float z);
	void SetScale(Vector3D scale);
	Vector3D GetScale();

	std::string GetName();

	virtual void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color);
	virtual void Update(double deltaTime);
	virtual void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

	void release();
	
	~AGameObject();

protected:
	std::string name; 
	
	Vector3D position = Vector3D(0, 0, 0);
	Vector3D rotation = Vector3D(0, 0, 0);
	Vector3D scale = Vector3D(1, 1, 1);
};

