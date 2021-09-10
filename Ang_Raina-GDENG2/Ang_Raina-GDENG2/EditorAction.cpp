#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
	this->objectName = gameObject->GetName();
	this->localPos = gameObject->GetPosition();
	this->orientation = gameObject->GetOrientation();
	this->localScale = gameObject->GetScale();
}

EditorAction::~EditorAction()
{
}

std::string EditorAction::GetOwnerName()
{
	return this->objectName;
}

Vector3D EditorAction::GetStoredPos()
{
	return this->localPos;
}

AQuaternion EditorAction::GetStoredOrientation()
{
	return this->orientation;
}

Vector3D EditorAction::GetStoredScale()
{
	return this->localScale;
}
