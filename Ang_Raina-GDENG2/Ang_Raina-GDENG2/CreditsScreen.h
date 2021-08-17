#pragma once
#include "AUIScreen.h"
#include "ImGuiTexture.h";

class CreditsScreen : public AUIScreen
{
private:
	CreditsScreen(std::string name);
	~CreditsScreen();
	void DrawUI() override;

	friend class MenuScreen;
	friend class UIManager;

	ImGuiTexture* logo;
};

