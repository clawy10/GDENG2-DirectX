#pragma once
#include "AUIScreen.h"
class ColorPickerScreen : public AUIScreen
{
private:
	ColorPickerScreen(std::string name);
	~ColorPickerScreen();
	void DrawUI() override;

	friend class MenuScreen;
	friend class UIManager;

	float color[4];
};

