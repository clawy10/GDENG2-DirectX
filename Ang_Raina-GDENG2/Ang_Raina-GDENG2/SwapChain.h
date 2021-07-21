#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	bool init(HWND hwnd, UINT width, UINT height); // initialize swap chain
	bool present(bool vsync);
	bool release(); // release swap chain
	~SwapChain();

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target_view;

private:
	friend class DeviceContext;
};

