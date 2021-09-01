#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(std::string name) : CubeObject(name)
{
	
}

PhysicsCube::~PhysicsCube()
{
	
}

void PhysicsCube::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	CubeObject::Initialize(shaderByteCode, sizeShader, color);

	this->AttachComponent(new PhysicsComponent("PhysicsComponent", this));
	PhysicsComponent* physicsComponent = (PhysicsComponent*)this->componentList[0];
	physicsComponent->GetRigidBody()->setMass(this->mass);
}

void PhysicsCube::Update(double deltaTime)
{
	CubeObject::Update(deltaTime);
}

void PhysicsCube::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	CubeObject::Draw(width, height, vertexShader, pixelShader);
}
