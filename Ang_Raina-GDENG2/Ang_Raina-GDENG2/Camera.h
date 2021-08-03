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
	
	Matrix4x4 GetCameraMatrix();
	void UpdateCameraMatrix();

	~Camera();

	
private:
	bool isForward = false;
	bool isBackward = false;
	bool isRight = false;
	bool isLeft = false;

	bool isRotate = false;
	
	Matrix4x4 cameraMatrix;

	float CAMERA_MOVE_SPEED = 0.5f;
	float CAMERA_ROTATE_SPEED = 0.001f;
};

