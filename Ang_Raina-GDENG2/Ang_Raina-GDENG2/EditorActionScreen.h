#pragma once
#include "AUIScreen.h"
class EditorActionScreen : public AUIScreen
{
public:
	EditorActionScreen(std::string name);
	~EditorActionScreen();
	void DrawUI() override;
	
};