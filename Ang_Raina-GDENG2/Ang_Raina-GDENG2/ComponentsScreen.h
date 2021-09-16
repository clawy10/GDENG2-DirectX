#pragma once
#include "AUIScreen.h"
#include "AGameObject.h"

class ComponentsScreen : public AUIScreen
{
public:
	ComponentsScreen(std::string name);
	~ComponentsScreen();
	void DrawUI() override;

	friend class MenuScreen;
	friend class UIManager;
};

