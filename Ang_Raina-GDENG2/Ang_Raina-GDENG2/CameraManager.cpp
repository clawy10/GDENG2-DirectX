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
	//GameObjectManager::getInstance()->AddObject(sharedInstance->sceneCamera);
}

void CameraManager::destroy()
{
}

void CameraManager::Update(float deltaTime)
{
	sharedInstance->GetSceneCamera()->Update(deltaTime);
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
