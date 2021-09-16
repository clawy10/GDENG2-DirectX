#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(std::string name, AGameObject* owner);
	~PhysicsComponent();

	void start(); 
	void perform(float deltaTime) override;
	RigidBody* GetRigidBody();

	void SetMass(float mass);
	void SetBodyType(BodyType bodyType);
	void EnableGravity(bool isEnabled);

	float GetMass();
	BodyType GetBodyType();
	bool IsGravityEnabled();

private:
	RigidBody* rigidBody;
	
	float mass = 1000.0f;
	BodyType bodyType;
	bool isGravityEnabled = true; 
};

