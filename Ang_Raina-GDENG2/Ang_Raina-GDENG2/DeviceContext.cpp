#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DepthBuffer.h"
#include "Texture.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) : m_device_context(deviceContext)
{
	
}

void DeviceContext::ClearRenderTargetColor(SwapChain* swapChain, DepthBuffer* depthBuffer, float red, float green, float blue, float alpha)
{
	FLOAT clearColor[] = { red, green, blue, alpha };
	this->m_device_context->ClearRenderTargetView(swapChain->m_render_target_view, clearColor);
	this->m_device_context->ClearDepthStencilView(depthBuffer->dsView, D3D11_CLEAR_DEPTH, 1.0f, 0u);
	this->m_device_context->OMSetRenderTargets(1, &swapChain->m_render_target_view, depthBuffer->dsView);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertexBuffer)
{
	UINT stride = vertexBuffer->m_size_vertex;
	UINT offset = 0;
	this->m_device_context->IASetVertexBuffers(0, 1, &vertexBuffer->m_buffer, &stride, &offset);
	this->m_device_context->IASetInputLayout(vertexBuffer->m_layout);
}

void DeviceContext::SetIndexBuffer(IndexBuffer* indexBuffer)
{
	this->m_device_context->IASetIndexBuffer(indexBuffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::DrawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	this->m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_device_context->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::DrawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexLocation)
{
	this->m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_device_context->DrawIndexed(indexCount, startIndexLocation, startVertexIndex);
}

void DeviceContext::DrawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	this->m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->m_device_context->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::SetViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	
	this->m_device_context->RSSetViewports(1, &vp);
}

void DeviceContext::SetVertexShader(VertexShader* vertex_shader)
{
	this->m_device_context->VSSetShader(vertex_shader->m_vertex_shader, nullptr, 0);
}

void DeviceContext::SetPixelShader(PixelShader* pixel_shader)
{
	this->m_device_context->PSSetShader(pixel_shader->m_pixel_shader, nullptr, 0);
}

void DeviceContext::PSSetSamplers(Texture* texture)
{
	this->m_device_context->PSSetSamplers(0u, 1u, &texture->m_ss);
}

void DeviceContext::SetTexture(VertexShader* vertex_shader, Texture* texture)
{
	m_device_context->VSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

void DeviceContext::SetTexture(PixelShader* pixel_shader, Texture* texture)
{
	m_device_context->PSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

void DeviceContext::SetConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* constant_buffer)
{
	this->m_device_context->VSSetConstantBuffers(0, 1, &constant_buffer->m_buffer);
}

void DeviceContext::SetConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* constant_buffer)
{
	this->m_device_context->PSSetConstantBuffers(0, 1, &constant_buffer->m_buffer);
}

bool DeviceContext::release()
{
	this->m_device_context->Release();
	delete this;
	return true;
}

DeviceContext::~DeviceContext()
{
	
}
