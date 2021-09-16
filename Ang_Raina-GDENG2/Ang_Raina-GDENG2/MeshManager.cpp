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
		mesh = new Mesh(L"..\\Assets\\Meshes\\cube.obj", "Cube", PrimitiveType::Cube);
		mesh->SetTexture(new Texture(L"..\\Assets\\Textures\\orange-texture.jpg"));
		break;

	case PrimitiveType::Cylinder:
		mesh = new Mesh(L"..\\Assets\\Meshes\\cylinder.obj", "Cylinder", PrimitiveType::Cylinder);
		
		break;

	case PrimitiveType::Plane:
		mesh = new Mesh(L"..\\Assets\\Meshes\\cube.obj", "Plane", PrimitiveType::Plane);
		mesh->SetScale(5, 0.5, 5);
		break;

	case PrimitiveType::Capsule:
		mesh = new Mesh(L"..\\Assets\\Meshes\\capsule.obj", "Capsule", PrimitiveType::Capsule);
		break;

	case PrimitiveType::Sphere:
		mesh = new Mesh(L"..\\Assets\\Meshes\\sphere.obj", "Sphere", PrimitiveType::Sphere);
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
