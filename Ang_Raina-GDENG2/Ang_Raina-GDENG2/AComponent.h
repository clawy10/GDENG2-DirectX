#pragma once
#include <string>

class AGameObject;

class AComponent
{
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3};
	AComponent(std::string name, ComponentType type, AGameObject* owner);
	~AComponent();

	void AttachOwner(AGameObject* owner);
	void DetachOwner();
	AGameObject* GetOwner();
	ComponentType GetType();
	std::string GetName();
	
	virtual void perform(float deltaTime) = 0;

protected:
	AGameObject* owner;
	ComponentType type;
	std::string name; 
};

