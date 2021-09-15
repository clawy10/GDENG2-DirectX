#pragma once
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
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

