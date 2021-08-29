#include "MeshManager.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

Mesh* MeshManager::createMeshFromFile(const wchar_t* file_path, std::string name)
{
	return (Mesh*)this->createResourceFromFileConcrete(file_path, name);
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path, std::string name)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path, name);
	}
	catch (...) {}

	return mesh;
}
