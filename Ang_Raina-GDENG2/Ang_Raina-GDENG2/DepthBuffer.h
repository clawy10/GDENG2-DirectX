#pragma once
#include <d3d11.h>

class DeviceContext; 

class DepthBuffer
{
public:
	DepthBuffer();
	bool init(UINT width, UINT height);
	bool release();
	~DepthBuffer();

private:
	ID3D11DepthStencilState* dsState;
	ID3D11DepthStencilView* dsView;

private:
	friend class DeviceContext;
};

