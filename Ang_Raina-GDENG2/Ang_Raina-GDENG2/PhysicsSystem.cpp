#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "EngineTime.h"

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings); 
}

PhysicsSystem::~PhysicsSystem()
{
	delete this->physicsCommon;
}

void PhysicsSystem::RegisterComponent(PhysicsComponent* physicsComponent)
{
	this->componentList.push_back(physicsComponent);
	this->componentTable.insert({ physicsComponent->GetName(), physicsComponent });
}

void PhysicsSystem::UnregisterComponent(PhysicsComponent* physicsComponent)
{
	if (this->componentTable[physicsComponent->GetName()] != nullptr)
	{
		this->componentTable.erase(physicsComponent->GetName());

		int index = -1;
		for (int i = 0; i < this->componentList.size(); i++)
		{
			if (this->componentList[i] == physicsComponent)
			{
				index = i;
				break;
			}
		}

		if (index != -1) {
			std::cout << "Deleted " + this->componentList[index]->GetName() << std::endl;
			this->componentList.erase(this->componentList.begin() + index);
		}
	}
}

void PhysicsSystem::UnregisterComponentByName(std::string name)
{
	if (this->componentTable[name] != nullptr)
	{
		this->UnregisterComponent(this->componentTable[name]);
	}
}

PhysicsComponent* PhysicsSystem::FindComponentByName(std::string name)
{
	return this->componentTable[name];
}

std::vector<PhysicsComponent*> PhysicsSystem::GetAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::UpdateAllComponents()
{
	if (EngineTime::GetDeltaTime() > 0)
	{
		this->physicsWorld->update(EngineTime::GetDeltaTime());
		for (int i = 0; i < this->componentList.size(); i++)
		{
			this->componentList[i]->perform(EngineTime::GetDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::GetPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::GetPhysicsCommon()
{
	return this->physicsCommon;
}
