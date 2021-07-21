#include "PixelShader.h"
#include "GraphicsEngine.h"

PixelShader::PixelShader()
{
}

void PixelShader::release()
{
	this->m_pixel_shader->Release();
	delete this;
}

PixelShader::~PixelShader()
{
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::getInstance()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &this->m_pixel_shader)))
	{
		return false;
	}

	return true;
}
