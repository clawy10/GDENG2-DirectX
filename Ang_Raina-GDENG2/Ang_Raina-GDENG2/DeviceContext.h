#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class DepthBuffer;
class Texture;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargetColor(SwapChain* swapChain, DepthBuffer* depthBuffer, float red, float green, float blue, float alpha);
	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void SetIndexBuffer(IndexBuffer* indexBuffer);
	void DrawTriangleList(UINT vertexCount, UINT startVertexIndex);
	void DrawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation);
	void DrawTriangleStrip(UINT vertexCount, UINT startVertexIndex);
	void SetViewportSize(UINT width, UINT height);
	
	void SetVertexShader(VertexShader* vertex_shader);
	void SetPixelShader(PixelShader* pixel_shader);
	void PSSetSamplers(Texture* texture);

	void SetTexture(VertexShader* vertex_shader, Texture* texture);
	void SetTexture(PixelShader* pixel_shader, Texture* texture);
	
	void SetConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* constant_buffer);
	void SetConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* constant_buffer);
	
	bool release();
	~DeviceContext();
	
private:
	ID3D11DeviceContext* m_device_context;

private:
	friend class ConstantBuffer;
};

