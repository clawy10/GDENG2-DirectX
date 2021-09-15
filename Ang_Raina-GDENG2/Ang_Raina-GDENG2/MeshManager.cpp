#include "MeshManager.h"
#include "PhysicsComponent.h"

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

Mesh* MeshManager::createPrimitiveMesh(PrimitiveType type)
{
	Mesh* mesh = nullptr; 
	switch (type)
	{
	case PrimitiveType::Cube:
		mesh = new Mesh(L"..\\Assets\\Meshes\\cube.obj", "cube", PrimitiveType::Cube);
		break;

	case PrimitiveType::Cylinder:
		mesh = new Mesh(L"..\\Assets\\Meshes\\cylinder.obj", "cylinder", PrimitiveType::Cylinder);
		break;

	case PrimitiveType::Plane:
		mesh = new Mesh(L"..\\Assets\\Meshes\\cube.obj", "plane", PrimitiveType::Plane);
		mesh->SetScale(5, 0.5, 5);
		break;
	}

	return mesh;
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path, std::string name)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(file_path, name, PrimitiveType::Other);
	}
	catch (...) {}

	return mesh;
}
