#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer(): m_buffer(0), m_layout(0)
{
}

bool VertexBuffer::load(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, UINT sizeByteShader)
{
	if (this->m_buffer)
	{
		this->m_buffer->Release();
	}
	if (this->m_layout)
	{
		this->m_layout->Release();
	}
	
	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = sizeVertex * sizeList;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = listVertices;

	this->m_size_vertex = sizeVertex;
	this->m_size_list = sizeList;
	
	if (FAILED(GraphicsEngine::getInstance()->m_d3d_device->CreateBuffer(&buffer_desc, &init_data, &this->m_buffer)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// SEMANTIC NAME, SEMANTIC INDEX, FORMAT, INPUT SLOT, ALIGNED BYTE OFFSET, INPUT SLOT CLASS, INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};

	UINT size_layout = ARRAYSIZE(layout);
	
	if (FAILED(GraphicsEngine::getInstance()->m_d3d_device->CreateInputLayout(layout, size_layout, shaderByteCode, sizeByteShader, &this->m_layout)))
	{
		return false;
	}

	return true;
}

UINT VertexBuffer::GetSizeVertexList()
{
	return this->m_size_list;
}

bool VertexBuffer::release()
{
	this->m_buffer->Release();
	this->m_layout->Release();
	delete this;
	
	return true;
}

VertexBuffer::~VertexBuffer()
{
}
