#pragma once
#include "AGameObject.h"
class CubeObject : public AGameObject
{
public:
	CubeObject(std::string name);

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(double deltaTime) override;

	void SetAnimationSpeed(float speed); 

	~CubeObject();

private:
	float SPEED = 1.0; // animation speed
};

