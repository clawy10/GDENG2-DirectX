#pragma once
#include "ResourceManager.h"
#include "Mesh.h"

class MeshManager
{
public:
	MeshManager();
	~MeshManager();
	Mesh* createMeshFromFile(const wchar_t* file_path, std::string name);
	Mesh* createPrimitiveMesh(Mesh::PrimitiveType type);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path, std::string name); 
};

