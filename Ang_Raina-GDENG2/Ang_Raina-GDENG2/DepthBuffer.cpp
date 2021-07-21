#include "DepthBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

DepthBuffer::DepthBuffer() : dsState(0)
{
	
}

bool DepthBuffer::init(UINT width, UINT height)
{
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	HRESULT hr = GraphicsEngine::getInstance()->m_d3d_device->CreateDepthStencilState(&dsDesc, &this->dsState);
	if (FAILED(hr))
	{
		return false;
	}
	
	GraphicsEngine::getInstance()->m_imm_context->OMSetDepthStencilState(this->dsState, 1u);
	
	ID3D11Texture2D* depthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	hr = GraphicsEngine::getInstance()->m_d3d_device->CreateTexture2D(&descDepth, nullptr, &depthStencil);

	if (FAILED(hr))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;

	hr = GraphicsEngine::getInstance()->m_d3d_device->CreateDepthStencilView(depthStencil, &descDSV, &this->dsView);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool DepthBuffer::release()
{
	this->dsView->Release();
	this->dsState->Release();
	delete this;

	return true;
}

DepthBuffer::~DepthBuffer()
{
	
}
