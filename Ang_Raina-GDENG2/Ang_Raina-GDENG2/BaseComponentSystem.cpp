#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
	return sharedInstance;
}

void BaseComponentSystem::initialize()
{
	sharedInstance = new BaseComponentSystem();
}

void BaseComponentSystem::destroy()
{
}

PhysicsSystem* BaseComponentSystem::GetPhysicsSystem()
{
	return this->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
	this->physicsSystem = new PhysicsSystem();
}

BaseComponentSystem::~BaseComponentSystem()
{
	
}
