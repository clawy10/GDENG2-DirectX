#include "SceneReader.h"
#include <iostream>
#include <rapidjson/filereadstream.h>
#include "MeshManager.h"
#include "Mesh.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"
#include "PhysicsComponent.h"

SceneReader::SceneReader(std::string directory)
{
	this->directory = directory;
}

SceneReader::~SceneReader()
{
}

void SceneReader::ReadFile()
{
	if (FILE* file = fopen(this->directory.append("\\scene.json").c_str(), "rb"))
	{
		char readBuffer[65536];
		FileReadStream is(file, readBuffer, sizeof(readBuffer));

		Document document;
		document.ParseStream(is);

		Value& objects = document["ObjectList"];
		if (objects.IsArray())
		{
			for (Value::ConstValueIterator itr = objects.Begin(); itr != objects.End(); ++itr) //iterate through array
			{
				this->CreateMesh(*itr);
			}
		}

		fclose(file);
	}
	else
	{
		std::cout << "Save file not found!" << std::endl;
	}
}

void SceneReader::CreateMesh(const Value& obj)
{
	Mesh* mesh = GraphicsEngine::getInstance()->GetMeshManager()->createPrimitiveMesh((PrimitiveType) obj["ObjectType"].GetInt());
	mesh->SetName(obj["ObjectName"].GetString());

	float posX = obj["Position"]["X"].GetFloat();
	float posY = obj["Position"]["Y"].GetFloat();
	float posZ = obj["Position"]["Z"].GetFloat();
	mesh->SetPosition(posX, posY, posZ);

	float rotX = obj["Rotation"]["X"].GetFloat();
	float rotY = obj["Rotation"]["Y"].GetFloat();
	float rotZ = obj["Rotation"]["Z"].GetFloat();
	mesh->SetRotation(rotX, rotY, rotZ);

	float scaleX = obj["Scale"]["X"].GetFloat();
	float scaleY = obj["Scale"]["Y"].GetFloat();
	float scaleZ = obj["Scale"]["Z"].GetFloat();
	mesh->SetScale(scaleX, scaleY, scaleZ);

	if (obj.HasMember("RigidBodyComponent"))
	{
		mesh->AttachComponent(new PhysicsComponent("PhysicsComponent", mesh));
		PhysicsComponent* physicsComponent = (PhysicsComponent*) mesh->FindComponentByName("PhysicsComponent");
		physicsComponent->SetBodyType((BodyType) obj["RigidBodyComponent"]["Type"].GetInt());
		physicsComponent->SetMass(obj["RigidBodyComponent"]["Mass"].GetFloat());
		physicsComponent->EnableGravity(obj["RigidBodyComponent"]["GravityEnabled"].GetBool());
	}
	
	
	GameObjectManager::getInstance()->AddObject(mesh);
	//std::cout << obj["Object Name"].GetString() << std::endl;
}
