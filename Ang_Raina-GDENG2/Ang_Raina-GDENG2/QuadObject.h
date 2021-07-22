#pragma once
#include "AGameObject.h"

class QuadObject : public AGameObject
{
public:
	QuadObject(std::string name);

	void Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color) override;
	void Update(double deltaTime) override;
	
	~QuadObject();

private:
	float speed = 5.0f;
	bool isSpeedUp = true; // is speeding up
	float MAX_SPEED = 10.0f;
	float MIN_SPEED = 2.0f;

	float ticks = 0.0f;
};

