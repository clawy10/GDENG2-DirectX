#include "CameraManager.h"

CameraManager* CameraManager::sharedInstance = nullptr;

CameraManager* CameraManager::getInstance()
{
	return sharedInstance;
}

void CameraManager::initialize()
{
	sharedInstance = new CameraManager();
	sharedInstance->mainCamera = new Camera();
}

void CameraManager::destroy()
{
}

Camera* CameraManager::GetMainCamera()
{
	return this->mainCamera;
}

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}
