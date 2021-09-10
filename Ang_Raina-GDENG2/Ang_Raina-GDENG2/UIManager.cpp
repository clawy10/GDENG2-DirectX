#include "UIManager.h"
#include "GraphicsEngine.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include <iostream>
#include "MenuScreen.h"
#include "ObjectListScreen.h"
#include "TransformObjectScreen.h"
#include "EditorModeScreen.h"
#include "EditorActionScreen.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND hwnd)
{
	sharedInstance = new UIManager(hwnd);
}

void UIManager::destroy()
{
	if (sharedInstance != nullptr)
	{
		delete sharedInstance;
	}
}

void UIManager::AddUIScreen(AUIScreen* uiScreen)
{
	this->uiList.push_back(uiScreen);
	this->uiTable[uiScreen->GetName()] = uiScreen;
}

void UIManager::DrawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	for (int i = 0; i < this->uiList.size(); i++)
	{
		this->uiList[i]->DrawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->m_d3d_device, GraphicsEngine::getInstance()->m_imm_context);

	UINames uinames; 
	MenuScreen* menuScreen = new MenuScreen(uinames.MENU_SCREEN);
	this->uiList.push_back(menuScreen);

	ObjectListScreen* objectListScreen = new ObjectListScreen(uinames.OBJECTLIST_SCREEN);
	this->uiList.push_back(objectListScreen);

	TransformObjectScreen* transformObjectScreen = new TransformObjectScreen(uinames.TRANSFORMOBJECT_SCREEN);
	this->uiList.push_back(transformObjectScreen);

	EditorModeScreen* editorModeScreen = new EditorModeScreen(uinames.EDITORMODE_SCREEN);
	this->uiList.push_back(editorModeScreen);

	EditorActionScreen* editorActionScreen = new EditorActionScreen(uinames.EDITORACTION_SCREEN);
	this->uiList.push_back(editorActionScreen);
}

UIManager::~UIManager()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
