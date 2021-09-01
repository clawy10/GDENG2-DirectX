#pragma once
#include "CubeObject.h"
class PhysicsCube : public CubeObject
{
public:
	PhysicsCube(std::string name);
	~PhysicsCube();

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(double deltaTime) override;
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;

protected:
	float mass = 3.0f;
};

