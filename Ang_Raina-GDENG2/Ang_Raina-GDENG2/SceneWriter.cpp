#include "SceneWriter.h"
#include "GameObjectManager.h"
#include "MathTools.h"
#include "PhysicsComponent.h"

SceneWriter::SceneWriter(std::string directory)
{
	this->directory = directory;
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::WriteToFile()
{
	StringBuffer s;
	PrettyWriter<StringBuffer> writer(s);
	Document document;

	std::vector<AGameObject*> objectList = GameObjectManager::getInstance()->GetAllObjects();
	writer.StartObject();
	for (int i = 0; i < objectList.size(); i++)
	{
		std::string name = "Object_" + std::to_string(i);
		writer.Key(name.c_str());
		writer.StartObject();
		
		writer.Key("Object Name");
		writer.String(objectList[i]->GetName().c_str());

		writer.Key("Object Type");
		writer.Int(objectList[i]->GetType());
		
		writer.Key("Position");
		writer.StartObject();
		writer.Key("X");
		writer.Double(objectList[i]->GetPosition().x);
		writer.Key("Y");
		writer.Double(objectList[i]->GetPosition().y);
		writer.Key("Z");
		writer.Double(objectList[i]->GetPosition().z);
		writer.EndObject();

		writer.Key("Rotation");
		writer.StartObject();
		writer.Key("X");
		writer.Double(objectList[i]->GetRotation().x);
		writer.Key("Y");
		writer.Double(objectList[i]->GetRotation().y);
		writer.Key("Z");
		writer.Double(objectList[i]->GetRotation().z);
		writer.EndObject();

		writer.Key("Scale");
		writer.StartObject();
		writer.Key("X");
		writer.Double(objectList[i]->GetScale().x);
		writer.Key("Y");
		writer.Double(objectList[i]->GetScale().y);
		writer.Key("Z");
		writer.Double(objectList[i]->GetScale().z);
		writer.EndObject();

		if  (objectList[i]->FindComponentByName("PhysicsComponent") != nullptr)
		{
			PhysicsComponent* physicsComponent = (PhysicsComponent*) objectList[i]->FindComponentByName("PhysicsComponent");
			writer.Key("Rigid Body Component");
			writer.StartObject();
			writer.Key("Type");
			writer.Int((int) physicsComponent->GetBodyType());
			writer.Key("Mass");
			writer.Double(physicsComponent->GetMass());
			writer.Key("Gravity Enabled: ");
			writer.Bool(physicsComponent->IsGravityEnabled());
			writer.EndObject();
		}

		writer.EndObject();
	}
	writer.EndObject();

	if (document.Parse(s.GetString()).HasParseError())
	{
		std::cout << "Parse error!" << std::endl;
	}

	FILE* file = fopen(this->directory.append("\\scene.json").c_str(), "wb");
	char writeBuffer[65536];
	FileWriteStream os(file, writeBuffer, sizeof(writeBuffer));

	PrettyWriter<FileWriteStream> fileWriter(os);
	document.Accept(fileWriter);
	
	fclose(file);
}
