#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <d3dcompiler.h>
#include "DepthBuffer.h"
#include "TextureManager.h"

GraphicsEngine* GraphicsEngine::sharedInstance = nullptr;

GraphicsEngine* GraphicsEngine::getInstance()
{
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();
	sharedInstance->init();
}

void GraphicsEngine::destroy()
{
	if (sharedInstance != NULL)
	{
		sharedInstance->release();
	}
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}

IndexBuffer* GraphicsEngine::CreateIndexBuffer()
{
	return new IndexBuffer();
}

ConstantBuffer* GraphicsEngine::CreateConstantBuffer()
{
	return new ConstantBuffer();
}

DepthBuffer* GraphicsEngine::CreateDepthBuffer()
{
	return new DepthBuffer();
}

VertexShader* GraphicsEngine::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = new VertexShader();
	if (!vs->init(shader_byte_code, byte_code_size))
	{
		vs->release();
		return nullptr;
	}

	return vs;
}

PixelShader* GraphicsEngine::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = new PixelShader();
	if (!ps->init(shader_byte_code, byte_code_size))
	{
		ps->release();
		return nullptr;
	}

	return ps;
}

TextureManager* GraphicsEngine::GetTextureManager()
{
	return this->m_texture_manager;
}

MeshManager* GraphicsEngine::GetMeshManager()
{
	return this->m_mesh_manager;
}

bool GraphicsEngine::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &this->m_blob, &error_blob)))
	{
		if (error_blob)
		{
			error_blob->Release();
		}
		return false;
	}

	*shader_byte_code = this->m_blob->GetBufferPointer();
	*byte_code_size = this->m_blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &this->m_blob, &error_blob)))
	{
		if (error_blob)
		{
			error_blob->Release();
		}
		return false;
	}

	*shader_byte_code = this->m_blob->GetBufferPointer();
	*byte_code_size = this->m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
	if (this->m_blob)
	{
		this->m_blob->Release();
	}
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &this->m_d3d_device, &this->m_feature_level, &this->m_imm_context);

		if (SUCCEEDED(res))
		{
			break;
		}

		driver_type_index++;
	}

	if (FAILED(res))
	{
		return false;
	}

	this->m_imm_device_context = new DeviceContext(this->m_imm_context);

	this->m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&this->m_dxgi_device);
	this->m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&this->m_dxgi_adapter);
	this->m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&this->m_dxgi_factory);

	this->m_texture_manager = new TextureManager();
	this->m_mesh_manager = new MeshManager();

	void* shader_byte_code = nullptr;
	size_t sizeShader = 0;

	this->CompileVertexShader(L"VertexMeshLayoutShader.hlsl", "main", &shader_byte_code, &sizeShader);
	::memcpy(m_mesh_layout_byte_code, shader_byte_code, sizeShader);
	m_mesh_layout_size = sizeShader;
	this->ReleaseCompiledShader();
	
	return true;
}

bool GraphicsEngine::release()
{
	this->m_imm_context->Release();
	this->m_d3d_device->Release();
	this->m_dxgi_device->Release();
	this->m_dxgi_adapter->Release();
	this->m_dxgi_factory->Release();
	this->m_imm_device_context->release();

	return true;
}

void GraphicsEngine::GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = this->m_mesh_layout_byte_code;
	*size = this->m_mesh_layout_size;
}

GraphicsEngine::GraphicsEngine()
{

}

GraphicsEngine::~GraphicsEngine()
{
}
