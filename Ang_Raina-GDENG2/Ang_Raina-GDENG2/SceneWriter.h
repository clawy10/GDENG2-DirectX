#pragma once
#include <rapidjson/writer.h>
#include <string>

using namespace rapidjson;

class SceneWriter
{
public:
	SceneWriter(std::string directory);
	~SceneWriter();
	void WriteToFile();

private:
	std::string directory;
};

