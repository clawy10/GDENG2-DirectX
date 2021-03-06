#include "AGameObject.h"
#include "EditorAction.h"

AGameObject::AGameObject(std::string name, PrimitiveType type)
{
	this->name = name;
	this->type = type;
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

void AGameObject::SetRotation(float x, float y, float z, float w)
{
	this->orientation = {};
	this->orientation = AQuaternion(x, y, z, w);
}

void AGameObject::SetRotation(float x, float y, float z)
{
	Vector3D rotation = Vector3D(x, y, z);
	this->orientation = {};
	this->orientation = MathTools::EulerToQuaternion(rotation);
}

void AGameObject::SetRotation(Vector3D rotation)
{
	this->orientation = {};
	this->orientation = MathTools::EulerToQuaternion(rotation);
}

void AGameObject::SetRotation(AQuaternion quaternion)
{
	this->orientation = quaternion;
}

Vector3D AGameObject::GetRotation()
{
	return MathTools::QuaternionToEuler(this->orientation);
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

void AGameObject::SetName(std::string name)
{
	this->name = name;
}

PrimitiveType AGameObject::GetType()
{
	return this->type;
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

void AGameObject::SaveEditState()
{
	this->lastEditState = new EditorAction(this);
}

void AGameObject::RestoreEditState()
{
	if (this->lastEditState != nullptr)
	{
		this->position = this->lastEditState->GetStoredPos();
		this->orientation = this->lastEditState->GetStoredOrientation();
		this->scale = this->lastEditState->GetStoredScale();
	}
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
