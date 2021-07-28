#pragma once
#include "Matrix4x4.h"
#include "InputListener.h"

class Camera : public InputListener
{
public:
	Camera();

	void OnKeyDown(int key) override;
	void OnKeyUp(int key) override;
	void OnMouseMove(const Point& mousePos) override;

	void OnLeftMouseDown(const Point& deltaMousePos) override;
	void OnLeftMouseUp(const Point& deltaMousePos) override;
	void OnRightMouseDown(const Point& deltaMousePos) override;
	void OnRightMouseUp(const Point& deltaMousePos) override;
	
	Matrix4x4 GetCameraMatrix();

	~Camera();

	
private:
	float rotX = 0.0f;
	float rotY = 0.0f;
	float forward = 0.0f;
	float rightward = 0.0f;
	Matrix4x4 cameraMatrix;
	
};

