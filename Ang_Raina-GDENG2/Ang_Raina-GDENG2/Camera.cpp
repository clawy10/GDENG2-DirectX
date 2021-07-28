#include "Camera.h"
#include "InputSystem.h"
#include "AppWindow.h"
#include "EngineTime.h"

Camera::Camera()
{
	InputSystem::getInstance()->AddListener(this);
	this->cameraMatrix.SetTranslation(Vector3D(0, 0, -2));
}

void Camera::OnKeyDown(int key)
{
	if (key == 'W')
	{
		this->forward = 1.0f;
	}
	else if (key == 'S')
	{
		this->forward = -1.0f;
	}

	if (key == 'A')
	{
		this->rightward = -1.0f;
	}
	else if (key == 'D')
	{
		this->rightward = 1.0f;
	}
}

void Camera::OnKeyUp(int key)
{
	this->forward = 0.0f;
	this->rightward = 0.0f;
}

void Camera::OnMouseMove(const Point& mousePos)
{
	int width = AppWindow::getInstance()->GetClientWindowRect().right - AppWindow::getInstance()->GetClientWindowRect().left;
	int height = AppWindow::getInstance()->GetClientWindowRect().bottom - AppWindow::getInstance()->GetClientWindowRect().top;
	

	this->rotX += (mousePos.y - (height / 2.0f)) * EngineTime::GetDeltaTime() * 0.1f;
	this->rotY += (mousePos.x - (width / 2.0f)) * EngineTime::GetDeltaTime() * 0.1f;
}

void Camera::OnLeftMouseDown(const Point& deltaMousePos)
{
}

void Camera::OnLeftMouseUp(const Point& deltaMousePos)
{
}

void Camera::OnRightMouseDown(const Point& deltaMousePos)
{
}

void Camera::OnRightMouseUp(const Point& deltaMousePos)
{
}

Matrix4x4 Camera::GetCameraMatrix()
{
	Matrix4x4 temp;
	temp.SetIdentity();
	
	Matrix4x4 worldCam;
	worldCam.SetIdentity();
	
	temp.SetRotationX(this->rotX);
	worldCam *= temp;

	temp.SetRotationY(this->rotY);
	worldCam *= temp;

	Vector3D newPos = this->cameraMatrix.GetTranslation() + worldCam.GetZDirection() * (this->forward * 0.1f);
	newPos = newPos + worldCam.GetXDirection() * (this->rightward * 0.1f);

	worldCam.SetTranslation(newPos);
	this->cameraMatrix = worldCam;
	worldCam.inverse();

	
	return worldCam;
}

Camera::~Camera()
{
}
