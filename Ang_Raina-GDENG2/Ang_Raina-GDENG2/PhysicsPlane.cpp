#include "PhysicsPlane.h"
#include "PhysicsComponent.h"

PhysicsPlane::PhysicsPlane(std::string name) : PlaneObject(name)
{
	this->SetScale(10, 1, 10);
	this->SetPosition(0, -5, 0);
}

PhysicsPlane::~PhysicsPlane()
{
}

void PhysicsPlane::Initialize(void* shaderByteCode, size_t sizeShader)
{
	PlaneObject::Initialize(shaderByteCode, sizeShader);

	this->AttachComponent(new PhysicsComponent("PhysicsComponent", this));
	PhysicsComponent* physicsComponent = (PhysicsComponent*)this->FindComponentByName("PhysicsComponent");
	physicsComponent->GetRigidBody()->setMass(this->mass);
	physicsComponent->GetRigidBody()->setType(BodyType::KINEMATIC);
}

void PhysicsPlane::Update(double deltaTime)
{
	PlaneObject::Update(deltaTime);
}

void PhysicsPlane::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	PlaneObject::Draw(width, height, vertexShader, pixelShader);
}
