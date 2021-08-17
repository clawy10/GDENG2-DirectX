#pragma once
#include <string>
#include "ImGui/imgui.h"

class UIManager;

class AUIScreen
{
protected:
	AUIScreen(std::string name);
	~AUIScreen();

	std::string GetName();
	virtual void DrawUI() = 0;

	std::string name;

	friend class UIManager; 
};

