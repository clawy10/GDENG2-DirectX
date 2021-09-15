#pragma once
#include "AUIScreen.h"
#include "SceneWriter.h"
class MenuScreen : public AUIScreen
{
private:
	MenuScreen(std::string name);
	~MenuScreen();
	void DrawUI() override;

	friend class UIManager;
};

