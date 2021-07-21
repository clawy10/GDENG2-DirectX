#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer()
{
}

bool ConstantBuffer::load(void* buffer, UINT sizeBuffer)
{
	if (this->m_buffer)
	{
		this->m_buffer->Release();
	}

	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeBuffer;
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(GraphicsEngine::getInstance()->m_d3d_device->CreateBuffer(&buffer_desc, &init_data, &this->m_buffer)))
	{
		return false;
	}

	return true;
}

void ConstantBuffer::update(DeviceContext* deviceContext, void* buffer)
{
	deviceContext->m_device_context->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstantBuffer::release()
{
	if (this->m_buffer)
	{
		this->m_buffer->Release();
	}
	delete this;
	return true;
}

ConstantBuffer::~ConstantBuffer()
{
}
