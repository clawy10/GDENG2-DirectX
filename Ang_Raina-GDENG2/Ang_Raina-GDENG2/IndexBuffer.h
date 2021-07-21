#pragma once
#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();
	bool load(void* listIndices, UINT sizeList);
	UINT GetSizeIndexList();
	bool release();
	~IndexBuffer();

private:
	UINT m_size_list;

	ID3D11Buffer* m_buffer;

private:
	friend class DeviceContext;
};

