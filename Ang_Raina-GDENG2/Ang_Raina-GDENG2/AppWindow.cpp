#include "AppWindow.h"
#include <iostream>
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "GameObjectManager.h"
#include "QuadObject.h"
#include "CubeObject.h"
#include "EngineTime.h"

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::destroy()
{
}

void AppWindow::OnCreate()
{
	Window::OnCreate();
	this->CreateGraphicsWindow();
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	this->m_swap_chain->release();
	this->m_vertex_shader->release();
	this->m_pixel_shader->release();
	GraphicsEngine::getInstance()->release();
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetVertexShader(this->m_vertex_shader);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetPixelShader(this->m_pixel_shader);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, this->m_depth_buffer, 0, 0.3f, 0.4f, 1);

	RECT rc = this->GetClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetViewportSize(width, height);

	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;

	GameObjectManager::getInstance()->UpdateObjects(EngineTime::GetDeltaTime());
	GameObjectManager::getInstance()->DrawObjects(width, height, this->m_vertex_shader, this->m_pixel_shader);
	
	this->m_swap_chain->present(true);
}

void AppWindow::CreateGraphicsWindow()
{
	GraphicsEngine::initialize();
	this->m_swap_chain = GraphicsEngine::getInstance()->CreateSwapChain();

	RECT rc = this->GetClientWindowRect();
	this->m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// create depth buffer
	this->m_depth_buffer = GraphicsEngine::getInstance()->CreateDepthBuffer();
	this->m_depth_buffer->init(rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t sizeShader = 0;

	GraphicsEngine::getInstance()->CompileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &sizeShader);
	this->m_vertex_shader = GraphicsEngine::getInstance()->CreateVertexShader(shader_byte_code, sizeShader);

	GameObjectManager::initialize(shader_byte_code, sizeShader);
	
	// insert objects to draw here

	QuadObject* quad_object = new QuadObject("Quad1"); // orange
	GameObjectManager::getInstance()->AddObject(quad_object, Vector3D(1, 0.38, 0.38));

	QuadObject* quad_object2 = new QuadObject("Quad2"); // yellow
	//quad_object2->SetPosition(0.5, 0, 1.0);
	//GameObjectManager::getInstance()->AddObject(quad_object2, Vector3D(1, 1, 0.38));

	//CubeObject* cube_object = new CubeObject("Cube1");
	//GameObjectManager::getInstance()->AddObject(cube_object, Vector3D(1, 0.38, 0.38));

	//CubeObject* cube_object2 = new CubeObject("Cube2");
	//cube_object2->SetPosition(0.5, 0, 1.0);
	//GameObjectManager::getInstance()->AddObject(cube_object2, Vector3D(1, 1, 0.38));
	
	
	// end of objects to draw
	
	GraphicsEngine::getInstance()->ReleaseCompiledShader();

	GraphicsEngine::getInstance()->CompilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &sizeShader);
	this->m_pixel_shader = GraphicsEngine::getInstance()->CreatePixelShader(shader_byte_code, sizeShader);
	GraphicsEngine::getInstance()->ReleaseCompiledShader();

	std::cout << "App Window initialized" << std::endl;
}
