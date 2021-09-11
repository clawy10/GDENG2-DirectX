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

Mesh* MeshManager::createPrimitiveMesh(Mesh::PrimitiveType type)
{
	Mesh* mesh = nullptr; 
	switch (type)
	{
	case Mesh::Cube:
		mesh = new Mesh(L"..\\Assets\\Meshes\\cube.obj", "cube");
		break;

	case Mesh::Cylinder:
		mesh = new Mesh(L"..\\Assets\\Meshes\\cylinder.obj", "cylinder");
		break;

	case Mesh::Plane:
		mesh = new Mesh(L"..\\Assets\\Meshes\\cube.obj", "plane");
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
		mesh = new Mesh(file_path, name);
	}
	catch (...) {}

	return mesh;
}
