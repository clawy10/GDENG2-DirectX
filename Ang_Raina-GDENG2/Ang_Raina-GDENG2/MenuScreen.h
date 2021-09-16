#pragma once
#include "AUIScreen.h"
#include "SceneWriter.h"
#include "MeshManager.h"
class MenuScreen : public AUIScreen
{
private:
	MenuScreen(std::string name);
	~MenuScreen();
	void CreateMesh(PrimitiveType type);
	void DrawUI() override;

	

	friend class UIManager;
};

