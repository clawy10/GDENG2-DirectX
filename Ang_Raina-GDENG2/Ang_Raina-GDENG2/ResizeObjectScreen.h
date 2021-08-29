#pragma once
#include "AUIScreen.h"
#include "AGameObject.h"

class ResizeObjectScreen : public AUIScreen
{
public:
	ResizeObjectScreen(std::string name);
	~ResizeObjectScreen();
	void DrawUI() override;

	void SelectObject(AGameObject* gameObject);

	friend class MenuScreen;
	friend class UIManager;

	float size[3];

private:
	AGameObject* selectedObject; 
};

