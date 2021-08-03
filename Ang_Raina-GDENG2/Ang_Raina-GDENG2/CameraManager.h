#pragma once
#include "Camera.h"
class CameraManager
{
public:
	static CameraManager* getInstance();
	static void initialize();
	static void destroy();

	Camera* GetSceneCamera();

private:
	CameraManager();
	~CameraManager();
	CameraManager(CameraManager const&) {};
	CameraManager& operator=(CameraManager const&) {};
	static CameraManager* sharedInstance;
	
	Camera* sceneCamera;
};

