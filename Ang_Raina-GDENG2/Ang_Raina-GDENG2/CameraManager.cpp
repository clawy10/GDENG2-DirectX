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
	sharedInstance->sceneCamera = new Camera("Camera");
	GameObjectManager::getInstance()->AddObject(sharedInstance->sceneCamera, Vector3D(1, 1, 1));
}

void CameraManager::destroy()
{
}

Camera* CameraManager::GetSceneCamera()
{
	return sharedInstance->sceneCamera;
}

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}
