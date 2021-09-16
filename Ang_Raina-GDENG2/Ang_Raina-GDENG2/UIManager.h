#pragma once
#include <vector>
#include <unordered_map>
#include "Window.h"
#include "AUIScreen.h"

class UINames
{
public:
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string CREDITS_SCREEN = "CREDITS_SCREEN";
	const std::string COLORPICKER_SCREEN = "COLORPICKER_SCREEN";
	const std::string OBJECTRESIZER_SCREEN = "OBJECTRESIZER_SCREEN";
	const std::string OBJECTLIST_SCREEN = "OBJECTLIST_SCREEN";
	const std::string TRANSFORMOBJECT_SCREEN = "TRANSFORMOBJECT_SCREEN";
	const std::string EDITORMODE_SCREEN = "EDITORMODE_SCREEN";
	const std::string EDITORACTION_SCREEN = "EDITORACTION_SCREEN";
	const std::string COMPONENTS_SCREEN = "COMPONENTS_SCREEN";
};

class UIManager
{
public:
	static UIManager* getInstance();
	static void initialize(HWND hwnd);
	static void destroy();

	void AddUIScreen(AUIScreen* uiScreen);
	
	void DrawAllUI();
	
private:
	UIManager(HWND hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	std::vector<AUIScreen*> uiList;
	std::unordered_map<std::string, AUIScreen*> uiTable;
};

