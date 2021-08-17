#pragma once
#include <d3d11.h>

class ImGuiTexture
{
public:
	ImGuiTexture(const char* full_path);
	~ImGuiTexture();
	
	int GetTextureWidth();
	int GetTextureHeight();
	ID3D11ShaderResourceView* GetTexture();
	
private:
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	
	int my_image_width = 0;
	int my_image_height = 0;
	ID3D11ShaderResourceView* my_texture = NULL;
};

