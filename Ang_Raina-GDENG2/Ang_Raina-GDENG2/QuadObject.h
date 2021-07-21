#pragma once
#include "AGameObject.h"

class QuadObject : public AGameObject
{
public:
	QuadObject(std::string name);

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(float deltaTime) override;
	
	~QuadObject();
};

