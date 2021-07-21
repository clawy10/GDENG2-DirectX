#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	bool load(void* listVertices, UINT sizeVertex, UINT sizeList, void* shaderByteCode, UINT sizeByteShader);
	UINT GetSizeVertexList();
	bool release();
	~VertexBuffer();

private:
	UINT m_size_vertex;
	UINT m_size_list;

	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;

private:
	friend class DeviceContext;
};

