#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Texture.h"

class CubeObject : public AGameObject
{
public:
	CubeObject(std::string name);

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(double deltaTime) override;
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;

	void SetAnimationSpeed(float speed); 

	~CubeObject();

private:
	float SPEED = 1.0; // animation speed

	VertexBuffer* vb;
	IndexBuffer* ib;
	ConstantBuffer* cb;

	Texture* texture;

	float delta = 0.0f;
};

