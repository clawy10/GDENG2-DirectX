#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

class PhysicsComponent;

using namespace reactphysics3d;

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	void RegisterComponent(PhysicsComponent* physicsComponent);
	void UnregisterComponent(PhysicsComponent* physicsComponent);
	void UnregisterComponentByName(std::string name);
	PhysicsComponent* FindComponentByName(std::string name);
	std::vector<PhysicsComponent*> GetAllComponents();

	void UpdateAllComponents();
	PhysicsWorld* GetPhysicsWorld();
	PhysicsCommon* GetPhysicsCommon();

private:
	reactphysics3d::PhysicsCommon* physicsCommon;
	reactphysics3d::PhysicsWorld* physicsWorld;

	std::vector<PhysicsComponent*> componentList;
	std::unordered_map<std::string, PhysicsComponent*> componentTable;
};

