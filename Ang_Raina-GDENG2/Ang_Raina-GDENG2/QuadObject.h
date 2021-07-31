#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class QuadObject : public AGameObject
{
public:
	QuadObject(std::string name);

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(double deltaTime) override;
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	
	~QuadObject();

private:
	float speed = 5.0f;
	bool isSpeedUp = true; // is speeding up
	float MAX_SPEED = 10.0f;
	float MIN_SPEED = 2.0f;

	float ticks = 0.0f;

	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;
};

