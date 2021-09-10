#include "TransformObjectScreen.h"
#include "MathTools.h"
#include "GameObjectManager.h"
#include "ActionHistory.h"

TransformObjectScreen::TransformObjectScreen(std::string name) : AUIScreen(name)
{
}

TransformObjectScreen::~TransformObjectScreen()
{
}

void TransformObjectScreen::DrawUI()
{
	ImGui::Begin("Resize Object");

	if (GameObjectManager::getInstance()->GetSelectedObject() != nullptr)
	{
		ImGui::Text("Selected object: %s",  GameObjectManager::getInstance()->GetSelectedObject()->GetName().c_str());
		this->GetObjectTransform();

		if (ImGui::DragFloat3("Position", this->position, 0.05))
		{
			ActionHistory::getInstance()->RecordAction(GameObjectManager::getInstance()->GetSelectedObject());
			this->UpdatePosition();
		}

		if (ImGui::DragFloat3("Rotation", this->rotation, 0.05))
		{
			ActionHistory::getInstance()->RecordAction(GameObjectManager::getInstance()->GetSelectedObject());
			this->UpdateRotation();
		}
		
		if (ImGui::DragFloat3("Scale", this->scale, 0.05))
		{
			ActionHistory::getInstance()->RecordAction(GameObjectManager::getInstance()->GetSelectedObject());
			this->UpdateScale();
		}
	}
	else
	{
		ImGui::Text("No object selected!");
	}

	ImGui::End();
}

void TransformObjectScreen::GetObjectTransform()
{
	AGameObject* selectedObject = GameObjectManager::getInstance()->GetSelectedObject();

	this->position[0] = selectedObject->GetPosition().x;
	this->position[1] = selectedObject->GetPosition().y;
	this->position[2] = selectedObject->GetPosition().z;

	Vector3D objectRotation = MathTools::QuaternionToEuler(selectedObject->GetOrientation());

	objectRotation.x = MathTools::ConvertRadiansToDegrees(objectRotation.x);
	objectRotation.y = MathTools::ConvertRadiansToDegrees(objectRotation.y);
	objectRotation.z = MathTools::ConvertRadiansToDegrees(objectRotation.z);
	
	this->rotation[0] = objectRotation.x;
	this->rotation[1] = objectRotation.y;
	this->rotation[2] = objectRotation.z;

	this->scale[0] = selectedObject->GetScale().x;
	this->scale[1] = selectedObject->GetScale().y;
	this->scale[2] = selectedObject->GetScale().z;
}

void TransformObjectScreen::UpdatePosition()
{
	Vector3D newPosition(this->position[0], this->position[1], this->position[2]);
	GameObjectManager::getInstance()->GetSelectedObject()->SetPosition(newPosition);
}

void TransformObjectScreen::UpdateRotation()
{
	Vector3D newRotation(this->rotation[0], this->rotation[1], this->rotation[2]);
	AQuaternion orientation = MathTools::EulerToQuaternion(newRotation);
	GameObjectManager::getInstance()->GetSelectedObject()->SetRotation(orientation);
}

void TransformObjectScreen::UpdateScale()
{
	Vector3D newScale(this->scale[0], this->scale[1], this->scale[2]);
	GameObjectManager::getInstance()->GetSelectedObject()->SetScale(newScale);
}
