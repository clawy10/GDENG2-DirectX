#define STB_IMAGE_IMPLEMENTATION
#include "ImGuiTexture.h"
#include "ImGui/stb_image.h"
#include "GraphicsEngine.h"
#include "ImGui/imgui.h"

ImGuiTexture::ImGuiTexture(const char* full_path)
{
    bool ret = this->LoadTextureFromFile(full_path, &my_texture, &my_image_width, &my_image_height);
    IM_ASSERT(ret);
}

ImGuiTexture::~ImGuiTexture()
{
}

bool ImGuiTexture::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    ID3D11Device* g_pd3dDevice = GraphicsEngine::getInstance()->m_d3d_device;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

int ImGuiTexture::GetTextureWidth()
{
    return this->my_image_width;
}

int ImGuiTexture::GetTextureHeight()
{
    return this->my_image_height;
}

ID3D11ShaderResourceView* ImGuiTexture::GetTexture()
{
    return this->my_texture;
}
