#include "Camera.h"
#include "InputSystem.h"
#include "AppWindow.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	InputSystem::getInstance()->AddListener(this);
	this->position = Vector3D(0, 0, -4);
	this->UpdateCameraMatrix();
}

void Camera::Update(double deltaTime)
{
	float x = this->position.x;
	float y = this->position.y;
	float z = this->position.z;

	if (this->isForward)
	{
		z += (float) deltaTime * this->CAMERA_MOVE_SPEED;
		this->SetPosition(x, y, z);
		this->UpdateCameraMatrix();
	}
	else if (this->isBackward)
	{
		z -= (float) deltaTime * this->CAMERA_MOVE_SPEED;
		this->SetPosition(x, y, z);
		this->UpdateCameraMatrix();
	}
	else if (this->isRight)
	{
		x += (float)deltaTime * this->CAMERA_MOVE_SPEED;
		this->SetPosition(x, y, z);
		this->UpdateCameraMatrix();
	}
	else if (this->isLeft)
	{
		x -= (float)deltaTime * this->CAMERA_MOVE_SPEED;
		this->SetPosition(x, y, z);
		this->UpdateCameraMatrix();
	}
}

void Camera::OnKeyDown(int key)
{
	if (key == 'W')
	{
		this->forward = 1.0f;
		this->isForward = true;
	}
	else if (key == 'S')
	{
		this->forward = -1.0f;
		this->isBackward = true;
	}

	if (key == 'A')
	{
		this->rightward = -1.0f;
		this->isLeft = true;
	}
	else if (key == 'D')
	{
		this->rightward = 1.0f;
		this->isRight = true;
	}
}

void Camera::OnKeyUp(int key)
{
	this->forward = 0.0f;
	this->rightward = 0.0f;

	if (key == 'W')
	{
		this->isForward = false;
	}
	else if (key == 'S')
	{
		this->isBackward = false;
	}

	if (key == 'A')
	{
		this->isLeft = false;
	}
	else if (key == 'D')
	{
		this->isRight = false;
	}
}

void Camera::OnMouseMove(const Point& mousePos)
{
	float x = this->rotation.x;
	float y = this->rotation.y;
	float z = this->rotation.z;

	int width = AppWindow::getInstance()->GetClientWindowRect().right - AppWindow::getInstance()->GetClientWindowRect().left;
	int height = AppWindow::getInstance()->GetClientWindowRect().bottom - AppWindow::getInstance()->GetClientWindowRect().top;
	
	x += (mousePos.y - (height / 2.0f)) * this->CAMERA_ROTATE_SPEED;
	y += (mousePos.x - (width / 2.0f)) * this->CAMERA_ROTATE_SPEED;

	this->SetRotation(x, y, z);
	this->UpdateCameraMatrix();
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
	return this->cameraMatrix;
}

void Camera::UpdateCameraMatrix()
{
	Matrix4x4 temp;
	temp.SetIdentity();

	Matrix4x4 world_cam;
	world_cam.SetIdentity();

	//temp.SetIdentity();
	temp.SetRotationX(this->rotation.x);
	world_cam *= temp;

	//temp.SetIdentity();
	temp.SetRotationY(this->rotation.y);
	world_cam *= temp;

	//Vector3D new_pos = m_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);
	//new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);
	temp.SetTranslation(this->position);
	world_cam *= temp;
	
	world_cam.inverse();

	this->cameraMatrix = world_cam;
}

Camera::~Camera()
{
}
