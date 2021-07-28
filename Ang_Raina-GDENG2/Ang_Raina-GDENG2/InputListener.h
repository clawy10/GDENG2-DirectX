#pragma once
#include "Point.h"

class InputListener
{
public:
	InputListener()
	{

	}
	~InputListener()
	{

	}

	// keyboard events
	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;

	// mouse events 
	virtual void OnMouseMove(const Point& mousePos) = 0;
	
	virtual void OnLeftMouseDown(const Point& deltaMousePos) = 0;
	virtual void OnLeftMouseUp(const Point& deltaMousePos) = 0;
	
	virtual void OnRightMouseDown(const Point& deltaMousePos) = 0;
	virtual void OnRightMouseUp(const Point& deltaMousePos) = 0;
};