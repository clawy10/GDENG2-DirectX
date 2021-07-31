#include "CameraManager.h"
#include "GameObjectManager.h"

CameraManager* CameraManager::sharedInstance = nullptr;

CameraManager* CameraManager::getInstance()
{
	return sharedInstance;
}

void CameraManager::initialize()
{
	sharedInstance = new CameraManager();
	sharedInstance->mainCamera = new Camera("Camera");
	GameObjectManager::getInstance()->AddObject(sharedInstance->mainCamera, Vector3D(1, 1, 1));
}

void CameraManager::destroy()
{
}

Camera* CameraManager::GetMainCamera()
{
	return sharedInstance->mainCamera;
}

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}
