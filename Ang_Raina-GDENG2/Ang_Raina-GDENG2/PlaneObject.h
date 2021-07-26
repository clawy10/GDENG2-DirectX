#pragma once
#include "AGameObject.h"
class PlaneObject : public AGameObject
{
public:
	PlaneObject(std::string name);

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(double deltaTime) override;

	~PlaneObject();
};

