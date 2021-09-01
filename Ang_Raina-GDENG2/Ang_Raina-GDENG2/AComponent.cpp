#include "AComponent.h"

AComponent::AComponent(std::string name, ComponentType type, AGameObject* owner)
{
	this->name = name;
	this->type = type;
	this->owner = owner;
}

AComponent::~AComponent()
{
}

void AComponent::AttachOwner(AGameObject* owner)
{
	this->owner = owner; 
}

void AComponent::DetachOwner()
{
	this->owner = nullptr;
	delete this;
}

AGameObject* AComponent::GetOwner()
{
	return this->owner;
}

AComponent::ComponentType AComponent::GetType()
{
	return this->type;
}

std::string AComponent::GetName()
{
	return this->name;
}
