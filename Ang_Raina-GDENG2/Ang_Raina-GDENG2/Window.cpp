#include "Window.h"
#include "EngineTime.h"
#include "ImGUI/imgui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
Window* window = nullptr; 

Window::Window()
{
	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;
	
	switch(msg)
	{
	case WM_CREATE: // window creation event
		{
			Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			//SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG_PTR)window);
			window->SetHWND(hwnd);
			window->OnCreate();
			break;
		}

	case WM_SETFOCUS: // window focus event 
	{
		//Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
		window->OnFocus();
		break;
	}

	case WM_KILLFOCUS: // window lost focus event 
	{
		//Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
		window->OnKillFocus();
		break;
	}

	case WM_DESTROY: // window destruction event 
		{
			//Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);
			window->OnDestroy();
			::PostQuitMessage(0);
			break;
		}

	default:
		{
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if(!::RegisterClassEx(&wc)) // if registration of the class fails, return false
	{
		return false;
	}

	if (!window)
	{
		window = this;
	}
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		throw std::runtime_error("COM Library is already initialized on this thread.");
	}
	
	// creation of the window 
	this->m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Window Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this);

	// if creation fails, return false
	if (!this->m_hwnd)
	{
		return false;
	}

	// show the window
	::ShowWindow(this->m_hwnd, SW_SHOW);
	::UpdateWindow(this->m_hwnd);

	// set flag to true to indicate window is initialized and running
	this->m_is_run = true;
	EngineTime::initialize();

	
	
	return true;
}

bool Window::broadcast()
{
	EngineTime::LogFrameStart();
	this->OnUpdate();
	MSG msg;
	
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);
	EngineTime::LogFrameEnd();
	
	return true;
}

bool Window::release()
{
	// destroy the window
	if (!::DestroyWindow(this->m_hwnd))
	{
		return false;
	}
	
	return true;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
	this->m_is_run = false;
}

void Window::OnFocus()
{
}

void Window::OnKillFocus()
{
}

bool Window::isRun()
{
	return this->m_is_run;
}

RECT Window::GetClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::SetHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

Window::~Window()
{
	
}
