#include "Camera.h"
#include "InputSystem.h"
#include "AppWindow.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	InputSystem::getInstance()->AddListener(this);
	this->position = Vector3D(0, 0, -5);

	int width = AppWindow::getInstance()->GetClientWindowRect().right - AppWindow::getInstance()->GetClientWindowRect().left;
	int height = AppWindow::getInstance()->GetClientWindowRect().bottom - AppWindow::getInstance()->GetClientWindowRect().top;
	this->cameraProjectionMatrix.SetPerspectiveFOVLH(1.57f, (float)width / (float)height, 0.1f, 100.0f);
	
	this->UpdateCameraMatrix();
}

Vector3D GetForwardDirection(Matrix4x4 matrix)
{
	Matrix4x4 viewMatrix = matrix;
	viewMatrix.inverse();

	Vector3D zDirection = viewMatrix.GetZDirection();

	return Vector3D::normalize(zDirection);
}

Vector3D GetSidewardDirection(Matrix4x4 matrix)
{
	Matrix4x4 viewMatrix = matrix;
	viewMatrix.inverse();

	Vector3D xDirection = viewMatrix.GetXDirection();

	return Vector3D::normalize(xDirection);
}

void Camera::Update(double deltaTime)
{
	if (this->isForward)
	{
		this->position = this->position + GetForwardDirection(this->cameraViewMatrix) * deltaTime * this->CAMERA_MOVE_SPEED;
		this->UpdateCameraMatrix();
	}
	if (this->isBackward)
	{
		this->position = this->position - GetForwardDirection(this->cameraViewMatrix) * deltaTime * this->CAMERA_MOVE_SPEED;
		this->UpdateCameraMatrix();
	}
	if (this->isRight)
	{
		this->position = this->position + GetSidewardDirection(this->cameraViewMatrix) * deltaTime * this->CAMERA_MOVE_SPEED;
		this->UpdateCameraMatrix();
	}
	if (this->isLeft)
	{
		this->position = this->position - GetSidewardDirection(this->cameraViewMatrix) * deltaTime * this->CAMERA_MOVE_SPEED;
		this->UpdateCameraMatrix();
	}
}

void Camera::OnKeyDown(int key)
{
	if (key == 'W')
	{
		this->isForward = true;
	}
	else if (key == 'S')
	{
		this->isBackward = true;
	}

	if (key == 'A')
	{
		this->isLeft = true;
	}
	else if (key == 'D')
	{
		this->isRight = true;
	}
}

void Camera::OnKeyUp(int key)
{
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
	else if (key == 'Q')
	{
		this->ChangeCameraMode();
	}
}

void Camera::OnMouseMove(const Point& mousePos)
{
	if (this->isRotate)
	{
		float x = this->orientation.x;
		float y = this->orientation.y;
		float z = this->orientation.z;

		//int width = AppWindow::getInstance()->GetClientWindowRect().right - AppWindow::getInstance()->GetClientWindowRect().left;
		//int height = AppWindow::getInstance()->GetClientWindowRect().bottom - AppWindow::getInstance()->GetClientWindowRect().top;

		//x += (mousePos.y - (height / 2.0f)) * this->CAMERA_ROTATE_SPEED;
		//y += (mousePos.x - (width / 2.0f)) * this->CAMERA_ROTATE_SPEED;

		x += mousePos.y * this->CAMERA_ROTATE_SPEED;
		y += mousePos.x * this->CAMERA_ROTATE_SPEED;
		
		this->SetRotation(x, y, z, 1);
		this->UpdateCameraMatrix();
	}
}

void Camera::OnLeftMouseDown(const Point& deltaMousePos)
{
}

void Camera::OnLeftMouseUp(const Point& deltaMousePos)
{
}

void Camera::OnRightMouseDown(const Point& deltaMousePos)
{
	this->isRotate = true;
}

void Camera::OnRightMouseUp(const Point& deltaMousePos)
{
	this->isRotate = false;
}

Matrix4x4 Camera::GetCameraViewMatrix()
{
	return this->cameraViewMatrix;
}

void Camera::UpdateCameraMatrix()
{
	Matrix4x4 temp;
	temp.SetIdentity();

	Matrix4x4 world_cam;
	world_cam.SetIdentity();

	temp.SetIdentity();
	temp.SetRotationX(this->orientation.x);
	world_cam *= temp;

	temp.SetIdentity();
	temp.SetRotationY(this->orientation.y);
	world_cam *= temp;

	temp.SetTranslation(this->position);
	world_cam *= temp;
	
	world_cam.inverse();

	this->cameraViewMatrix = world_cam;
}

Matrix4x4 Camera::GetCameraProjectionMatrix()
{
	return this->cameraProjectionMatrix;
}

void Camera::ChangeCameraMode()
{
	this->isOrtho = !this->isOrtho;

	int width = AppWindow::getInstance()->GetClientWindowRect().right - AppWindow::getInstance()->GetClientWindowRect().left;
	int height = AppWindow::getInstance()->GetClientWindowRect().bottom - AppWindow::getInstance()->GetClientWindowRect().top;
	this->cameraProjectionMatrix.SetIdentity();
	
	if (this->isOrtho)
	{
		this->cameraProjectionMatrix.SetOrthoLH((float)width / 300.0f, (float)height / 300.0f, -69.0f, 420.0f);
	}
	else
	{
		this->cameraProjectionMatrix.SetPerspectiveFOVLH(1.57f, (float)width / (float)height, 0.1f, 100.0f);
	}
}

Camera::~Camera()
{
}
