#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(std::string name, AGameObject* owner) : AComponent(name, ComponentType::Physics, owner)
{
	BaseComponentSystem::getInstance()->GetPhysicsSystem()->RegisterComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->GetPhysicsSystem()->GetPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->GetPhysicsSystem()->GetPhysicsWorld();

	Vector3D scale = this->GetOwner()->GetScale();	
	Vector3 position(this->GetOwner()->GetPosition().x, this->GetOwner()->GetPosition().y, this->GetOwner()->GetPosition().z);	
	Quaternion rotation = Quaternion(this->GetOwner()->GetOrientation().x, this->GetOwner()->GetOrientation().y, this->GetOwner()->GetOrientation().z, this->GetOwner()->GetOrientation().w);

	Transform transform(position, rotation);
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2, scale.y / 2, scale.z / 2));
	
	this->rigidBody = physicsWorld->createRigidBody(transform);
	transform.setToIdentity();
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);
	this->rigidBody->enableGravity(true);
	this->rigidBody->setIsAllowedToSleep(false);
}

PhysicsComponent::~PhysicsComponent()
{
	
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->GetOwner()->SetPosition(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z);
	this->GetOwner()->SetRotation(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z, transform.getOrientation().w);
}

RigidBody* PhysicsComponent::GetRigidBody()
{
	return this->rigidBody;
}
