#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include <iostream>

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1; 
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_projection;

	//unsigned int m_time;
	float m_angle;
};

class AGameObject
{
public:
	AGameObject(std::string name);
	
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	std::string GetName();

	virtual void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color);
	virtual void Update(double deltaTime);
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);

	void release();
	
	~AGameObject();

protected:
	std::string name; 
	
	Vector3D position = Vector3D(0, 0, 0);
	Vector3D rotation = Vector3D(0, 0, 0);
	Vector3D scale = Vector3D(1, 1, 1);

	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;

	float m_angle; 
};

