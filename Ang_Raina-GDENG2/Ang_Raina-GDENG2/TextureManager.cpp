#include "TextureManager.h"
#include "Texture.h"


TextureManager::TextureManager() : ResourceManager()
{
}


TextureManager::~TextureManager()
{
}

Texture* TextureManager::createTextureFromFile(const wchar_t* file_path)
{
	return (Texture*) this->createResourceFromFileConcrete(file_path); 
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(file_path);
	}
	catch (...) {}

	return tex;
}