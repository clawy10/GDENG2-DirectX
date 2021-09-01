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
	this->orientation = {}; 
	this->orientation = AQuaternion(x, y, z);
}

void AGameObject::SetRotation(float x, float y, float z, float w)
{
	this->orientation = {};
	this->orientation = AQuaternion(x, y, z, w);
}

void AGameObject::SetRotation(Vector3D rotation)
{
	this->orientation = {};
	this->orientation = AQuaternion(rotation.x, rotation.y, rotation.z);
}

Vector3D AGameObject::GetRotation()
{
	return Vector3D(this->orientation.x, this->orientation.y, this->orientation.z);
}

AQuaternion AGameObject::GetOrientation()
{
	return this->orientation;
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

void AGameObject::Initialize(void* shaderByteCode, size_t sizeShader)
{
	
}

void AGameObject::Update(double deltaTime)
{
	//std::cout << this->GetName() << " gameobject updating." << std::endl;
}

void AGameObject::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	
}

void AGameObject::AttachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->AttachOwner(this);
}

void AGameObject::DetachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::FindComponentByName(std::string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->GetName() == name) {
			return this->componentList[i];
		}
	}

	return nullptr;
}

void AGameObject::release()
{
	delete this;
}

AGameObject::~AGameObject()
{
	
}

void AGameObject::Awake()
{
	
}
