#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	bool init();
	bool broadcast();
	bool release();
	bool isRun();

	RECT GetClientWindowRect();
	void SetHWND(HWND hwnd);
	
	// events
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();
	virtual void OnFocus();
	virtual void OnKillFocus();
	
	
	~Window();

protected:
	HWND m_hwnd;
	bool m_is_run;
};

