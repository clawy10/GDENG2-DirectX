#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
#include "MeshManager.h"

class ImGuiTexture;

class GraphicsEngine
{
public:
	bool init(); // initialize the graphics engine and directX device 
	bool release(); // release all resources loaded

public:
	static GraphicsEngine* getInstance();
	static void initialize();
	static void destroy();

	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();
	VertexBuffer* CreateVertexBuffer();
	IndexBuffer* CreateIndexBuffer();
	ConstantBuffer* CreateConstantBuffer();
	DepthBuffer* CreateDepthBuffer();
	VertexShader* CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);

	TextureManager* GetTextureManager();
	MeshManager* GetMeshManager();
	
	bool CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void ReleaseCompiledShader();

	void GetShaderBufferAndSize(void** bytecode, UINT* size);

	void GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size); 

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator=(GraphicsEngine const&) {};
	static GraphicsEngine* sharedInstance;

private:
	DeviceContext* m_imm_device_context;

	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_context;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

	ID3DBlob* m_blob = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	TextureManager* m_texture_manager = nullptr;
	MeshManager* m_mesh_manager = nullptr;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0; 

private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class DepthBuffer;
	friend class Texture;
	friend class UIManager;
	friend class ImGuiTexture;
};

