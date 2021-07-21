#include "IndexBuffer.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer() : m_buffer(0)
{
}

bool IndexBuffer::load(void* listIndices, UINT sizeList)
{
	if (this->m_buffer)
	{
		this->m_buffer->Release();
	}

	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = 4 * sizeList;
	buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = listIndices;

	this->m_size_list = sizeList;

	if (FAILED(GraphicsEngine::getInstance()->m_d3d_device->CreateBuffer(&buffer_desc, &init_data, &this->m_buffer)))
	{
		return false;
	}

	return true;
}

UINT IndexBuffer::GetSizeIndexList()
{
	return this->m_size_list;
}

bool IndexBuffer::release()
{
	this->m_buffer->Release();
	delete this;

	return true;
}

IndexBuffer::~IndexBuffer()
{
}
