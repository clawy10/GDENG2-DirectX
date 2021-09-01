#pragma once
#include "AUIScreen.h"
class ObjectListScreen : public AUIScreen
{
public:
	ObjectListScreen(std::string name);
	~ObjectListScreen();
	
	void DrawUI() override;
	
	friend class UIManager;
};

