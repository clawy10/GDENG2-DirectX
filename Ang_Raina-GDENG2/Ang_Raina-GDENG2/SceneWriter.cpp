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

	writer.Key("ObjectList");
	writer.StartArray();
	for (int i = 0; i < objectList.size(); i++)
	{
		writer.StartObject();
		
		writer.Key("ObjectType");
		writer.Int(objectList[i]->GetType());
		
		writer.Key("ObjectName");
		writer.String(objectList[i]->GetName().c_str());
		
		writer.Key("Position");
		writer.StartObject();
		writer.Key("X");
		writer.Double(objectList[i]->GetPosition().x);
		writer.Key("Y");
		writer.Double(objectList[i]->GetPosition().y);
		writer.Key("Z");
		writer.Double(objectList[i]->GetPosition().z);
		writer.EndObject();

		Vector3D rotation = MathTools::QuaternionToEuler(objectList[i]->GetOrientation()); 
		
		writer.Key("Rotation");
		writer.StartObject();
		writer.Key("X");
		writer.Double(rotation.x);
		writer.Key("Y");
		writer.Double(rotation.y);
		writer.Key("Z");
		writer.Double(rotation.z);
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
			writer.Key("RigidBodyComponent");
			writer.StartObject();
			writer.Key("Type");
			writer.Int((int) physicsComponent->GetBodyType());
			writer.Key("Mass");
			writer.Double(physicsComponent->GetMass());
			writer.Key("GravityEnabled");
			writer.Bool(physicsComponent->IsGravityEnabled());
			writer.EndObject();
		}

		writer.EndObject();
	}
	
	writer.EndArray();
	
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
