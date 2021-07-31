#include "AGameObject.h"
#include "CameraManager.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
}

void AGameObject::SetPosition(float x, float y, float z)
{
	this->position = Vector3D(x, y, z);
}

void AGameObject::SetPosition(Vector3D position)
{
	this->position = position;
}

Vector3D AGameObject::GetPosition()
{
	return this->position;
}

void AGameObject::SetRotation(float x, float y, float z)
{
	this->rotation = Vector3D(x, y, z);
}

void AGameObject::SetRotation(Vector3D rotation)
{
	this->rotation = rotation;
}

Vector3D AGameObject::GetRotation()
{
	return this->rotation;
}

void AGameObject::SetScale(float x, float y, float z)
{
	this->scale = Vector3D(x, y, z);
}

void AGameObject::SetScale(Vector3D scale)
{
	this->scale = scale;
}

Vector3D AGameObject::GetScale()
{
	return this->scale;
}

std::string AGameObject::GetName()
{
	return this->name;
}

void AGameObject::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	
}

void AGameObject::Update(double deltaTime)
{
	
}

void AGameObject::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	
}

void AGameObject::release()
{
	delete this;
}

AGameObject::~AGameObject()
{
	
}
