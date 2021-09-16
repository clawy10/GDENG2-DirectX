#include "ComponentsScreen.h"
#include "GameObjectManager.h"
#include "PhysicsComponent.h"
#include "EngineBackend.h"

ComponentsScreen::ComponentsScreen(std::string name) :AUIScreen(name)
{
}

ComponentsScreen::~ComponentsScreen()
{
}

void ComponentsScreen::DrawUI()
{
	if (EngineBackend::getInstance()->GetMode() != EngineBackend::EDITOR)
	{
		return;
	}
	
	ImGui::Begin("Components");

	if (GameObjectManager::getInstance()->GetSelectedObject() != nullptr)
	{
		AGameObject* selectedObject = GameObjectManager::getInstance()->GetSelectedObject();
		if (selectedObject->FindComponentByName("PhysicsComponent") != nullptr)
		{
			PhysicsComponent* physicsComponent = (PhysicsComponent*) selectedObject->FindComponentByName("PhysicsComponent");
			
			float mass = physicsComponent->GetMass(); 
			if (ImGui::InputFloat("Mass", &mass))
			{
				physicsComponent->SetMass(mass);
			}

			int bodyType = (int) physicsComponent->GetBodyType();
			const char* types[] = { "STATIC", "KINEMATIC", "DYNAMIC" };
			if (ImGui::Combo("Body Type", &bodyType, types, IM_ARRAYSIZE(types)))
			{
				physicsComponent->SetBodyType((BodyType)bodyType);
			}

			bool gravityEnabled = physicsComponent->IsGravityEnabled();
			if (ImGui::Checkbox("Enable Gravity", &gravityEnabled))
			{
				physicsComponent->EnableGravity(gravityEnabled);
			}
		}
		else
		{
			if (ImGui::Button("Attach Physics Component"))
			{
				selectedObject->AttachComponent(new PhysicsComponent("PhysicsComponent", selectedObject));
			}
		}
	}
	else
	{
		ImGui::Text("No object selected!");
	}

	ImGui::End();
}
