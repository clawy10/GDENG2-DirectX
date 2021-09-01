#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(std::string name) : CubeObject(name)
{
	
}

PhysicsCube::~PhysicsCube()
{
	
}

void PhysicsCube::Initialize(void* shaderByteCode, size_t sizeShader)
{
	CubeObject::Initialize(shaderByteCode, sizeShader);

	this->AttachComponent(new PhysicsComponent("PhysicsComponent", this));
	PhysicsComponent* physicsComponent = (PhysicsComponent*)this->FindComponentByName("PhysicsComponent");
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
