#include "AppWindow.h"
#include <iostream>
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "GameObjectManager.h"
#include "QuadObject.h"
#include "CubeObject.h"
#include "PlaneObject.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

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
	srand((unsigned)time(NULL));
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	this->m_swap_chain->release();
	this->m_vertex_shader->release();
	this->m_pixel_shader->release();
	GraphicsEngine::getInstance()->release();
	InputSystem::destroy();
	CameraManager::destroy();
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	InputSystem::getInstance()->Update();
	
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetVertexShader(this->m_vertex_shader);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetPixelShader(this->m_pixel_shader);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, this->m_depth_buffer, 0, 0.3f, 0.4f, 1);

	RECT rc = this->GetClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetViewportSize(width, height);

	BaseComponentSystem::getInstance()->GetPhysicsSystem()->UpdateAllComponents();
	GameObjectManager::getInstance()->UpdateObjects(EngineTime::GetDeltaTime());
	//this->m_mesh->Draw(this->m_vertex_shader, this->m_pixel_shader);
	GameObjectManager::getInstance()->DrawObjects(width, height, this->m_vertex_shader, this->m_pixel_shader);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetVertexShader(this->m_vertex_shader);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetPixelShader(this->m_pixel_shader);
	

	UIManager::getInstance()->DrawAllUI();
	
	this->m_swap_chain->present(true);
}


float RandomNumber(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

void AppWindow::CreateGraphicsWindow()
{
	GraphicsEngine::initialize();
	InputSystem::initialize();
	UIManager::initialize(this->m_hwnd);

	InputSystem::getInstance()->AddListener(this);
	//InputSystem::getInstance()->ShowCursor(false);

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

	//GraphicsEngine::getInstance()->CompileVertexShader(L"VertexMeshLayoutShader.hlsl", "main", &shader_byte_code, &sizeShader);

	GameObjectManager::initialize(shader_byte_code, sizeShader);
	CameraManager::initialize();
	BaseComponentSystem::initialize();

	// insert objects to draw here

	//CubeObject* cube_object = new CubeObject("Cube1");
	//cube_object->SetPosition(0.0f, 0.0f, -0.5f);
	//GameObjectManager::getInstance()->AddObject(cube_object, Vector3D(1, 0.38, 0.38));

	for (int i = 0; i < 20; i++)
	{
		PhysicsCube* physics_cube = new PhysicsCube("PhysicsCube");
		physics_cube->SetPosition(0, 5, 0);
		GameObjectManager::getInstance()->AddObject(physics_cube, Vector3D(1, 0.38, 0.38));
	}

	PhysicsPlane* physics_plane = new PhysicsPlane("PhysicsPlane");
	GameObjectManager::getInstance()->AddObject(physics_plane, Vector3D(1, 0.38, 0.38));

	//PlaneObject* plane_object = new PlaneObject("Plane1");
	//plane_object->SetScale(5, 5, 1);
	//GameObjectManager::getInstance()->AddObject(plane_object, Vector3D(1, 1, 1));

	//Mesh* teapot = GraphicsEngine::getInstance()->GetMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\teapot.obj", "teapot");
	//teapot->SetPosition(3.0f, 0.0f, 0.0f);
	//GameObjectManager::getInstance()->AddObject(teapot, Vector3D(1, 0.38, 0.38));
	
	//Mesh* bunny = GraphicsEngine::getInstance()->GetMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\bunny.obj", "bunny");
	//bunny->SetPosition(-3.0f, 0.0f, 0.0f);
	//GameObjectManager::getInstance()->AddObject(bunny, Vector3D(1, 0.38, 0.38));
	
	//Mesh* armadillo = GraphicsEngine::getInstance()->GetMeshManager()->createMeshFromFile(L"..\\Assets\\Meshes\\armadillo.obj", "armadillo");
	//GameObjectManager::getInstance()->AddObject(armadillo, Vector3D(1, 0.38, 0.38));
	
	// end of objects to draw

	GraphicsEngine::getInstance()->ReleaseCompiledShader();

	GraphicsEngine::getInstance()->CompilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &sizeShader);
	this->m_pixel_shader = GraphicsEngine::getInstance()->CreatePixelShader(shader_byte_code, sizeShader);
	GraphicsEngine::getInstance()->ReleaseCompiledShader();
	
	std::cout << "App Window initialized" << std::endl;
}

void AppWindow::OnFocus()
{
	InputSystem::getInstance()->AddListener(this);
}

void AppWindow::OnKillFocus()
{
	InputSystem::getInstance()->RemoveListener(this);
}

void AppWindow::OnKeyDown(int key)
{
}

void AppWindow::OnKeyUp(int key)
{
}

void AppWindow::OnMouseMove(const Point& mousePos)
{
	//int width = this->GetClientWindowRect().right - this->GetClientWindowRect().left;
	//int height = this->GetClientWindowRect().bottom - this->GetClientWindowRect().top;
	
	// lock cursor
	//InputSystem::getInstance()->SetCursorPosition(Point(width / 2.0f, height / 2.0f));
}

void AppWindow::OnLeftMouseDown(const Point& deltaMousePos)
{
}

void AppWindow::OnLeftMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::OnRightMouseDown(const Point& deltaMousePos)
{
}

void AppWindow::OnRightMouseUp(const Point& deltaMousePos)
{
}

