#pragma once
#include "AUIScreen.h"
class TransformObjectScreen : public AUIScreen
{
public:
	TransformObjectScreen(std::string name);
	~TransformObjectScreen();

	void DrawUI() override;

	void GetObjectTransform();
	
	void UpdatePosition();
	void UpdateRotation();
	void UpdateScale();
	void RecordAction();
	
private:
	float position[3];
	float rotation[3];
	float scale[3];
};

