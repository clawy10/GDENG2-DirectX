#pragma once
#include <iostream>
#include "AGameObject.h"

class EditorAction
{
public:
	EditorAction(AGameObject* gameObject);
	~EditorAction();

	std::string GetOwnerName();
	Vector3D GetStoredPos();
	AQuaternion GetStoredOrientation();
	Vector3D GetStoredScale();

private:
	std::string objectName;
	Vector3D localPos;
	AQuaternion orientation;
	Vector3D localScale;
	
};

