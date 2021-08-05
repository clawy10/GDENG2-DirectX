#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Texture.h"

class PlaneObject : public AGameObject
{
public:
	PlaneObject(std::string name);

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(double deltaTime) override;
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;

	~PlaneObject();

private:
	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;

	Texture* texture;
};

