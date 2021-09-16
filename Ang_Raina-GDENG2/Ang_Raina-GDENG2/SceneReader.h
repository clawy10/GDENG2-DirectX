#pragma once
#include <string>
#include <rapidjson/document.h>

using namespace  rapidjson;

class SceneReader
{
public:
	SceneReader(std::string directory);
	~SceneReader();
	void ReadFile();

	void CreateMesh(const Value& obj);

private:
	std::string directory;
};

