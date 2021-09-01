#pragma once
#include "PlaneObject.h"

class PhysicsPlane : public PlaneObject
{
public:
	PhysicsPlane(std::string name);
	~PhysicsPlane();
	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(double deltaTime) override;
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;

private:
	float mass = 100.0f;
};

