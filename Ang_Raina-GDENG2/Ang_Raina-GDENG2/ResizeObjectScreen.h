#pragma once
#include "AUIScreen.h"
#include "AGameObject.h"

class ResizeObjectScreen : public AUIScreen
{
public:
	ResizeObjectScreen(std::string name);
	~ResizeObjectScreen();
	void DrawUI() override;

	friend class MenuScreen;
	friend class UIManager;

private:
	float size[3];
};

