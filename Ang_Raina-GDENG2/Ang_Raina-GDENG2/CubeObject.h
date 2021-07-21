#pragma once
#include "AGameObject.h"
class CubeObject : public AGameObject
{
public:
	CubeObject(std::string name);

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(float deltaTime) override;

	~CubeObject();
};

