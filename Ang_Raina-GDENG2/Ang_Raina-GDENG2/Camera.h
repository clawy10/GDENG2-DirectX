#pragma once
#include "Matrix4x4.h"
#include "InputListener.h"
#include "AGameObject.h"

class Camera : public AGameObject, InputListener
{
public:
	Camera(std::string name);

	void Update(double deltaTime) override;

	void OnKeyDown(int key) override;
	void OnKeyUp(int key) override;
	void OnMouseMove(const Point& mousePos) override;

	void OnLeftMouseDown(const Point& deltaMousePos) override;
	void OnLeftMouseUp(const Point& deltaMousePos) override;
	void OnRightMouseDown(const Point& deltaMousePos) override;
	void OnRightMouseUp(const Point& deltaMousePos) override;
	
	Matrix4x4 GetCameraViewMatrix();
	void UpdateCameraMatrix();

	Matrix4x4 GetCameraProjectionMatrix();

	~Camera();

	
private:
	void ChangeCameraMode(); // change camera mode to perspective or othographic
	
	bool isForward = false;
	bool isBackward = false;
	bool isRight = false;
	bool isLeft = false;

	bool isRotate = false;

	bool isOrtho = false; // if the camera is set to orthographic mode
	
	Matrix4x4 cameraViewMatrix;
	Matrix4x4 cameraProjectionMatrix;

	float CAMERA_MOVE_SPEED = 10.0f;
	float CAMERA_ROTATE_SPEED = 0.001f;
};

