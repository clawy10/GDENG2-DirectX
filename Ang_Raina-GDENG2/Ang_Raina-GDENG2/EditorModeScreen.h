#pragma once
#include "AUIScreen.h"
class EditorModeScreen : public AUIScreen
{
public:
	EditorModeScreen(std::string name);
	~EditorModeScreen();

	void DrawUI() override;

	
};

