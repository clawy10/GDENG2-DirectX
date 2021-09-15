#include "SceneWriter.h"
#include "GameObjectManager.h"
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>

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
	Writer<StringBuffer> writer(s);
	Document document;

	std::vector<AGameObject*> objectList = GameObjectManager::getInstance()->GetAllObjects();
	writer.StartObject();
	writer.Key("Objects");
	writer.StartArray();
	for (int i = 0; i < objectList.size(); i++)
	{
		writer.Key("Object Name");
		writer.String(objectList[i]->GetName().c_str());
		writer.Key("X Position");
		writer.Double(objectList[i]->GetPosition().x);
		writer.Key("Y Position");
		writer.Double(objectList[i]->GetPosition().y);
		writer.Key("Z Position");
		writer.Double(objectList[i]->GetPosition().z);
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

	Writer<FileWriteStream> fileWriter(os);
	document.Accept(fileWriter);
	
	fclose(file);
}
