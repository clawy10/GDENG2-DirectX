#pragma once
#include <vector>

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DepthBuffer.h"
#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
public:
	static AppWindow* getInstance();
	static void initialize();
	static void destroy();

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnUpdate() override;
	void OnFocus() override;
	void OnKillFocus() override;

	void CreateGraphicsWindow();

	void OnKeyDown(int key) override;
	void OnKeyUp(int key) override;
	
	void OnMouseMove(const Point& mousePos) override;
	void OnLeftMouseDown(const Point& deltaMousePos) override;
	void OnLeftMouseUp(const Point& deltaMousePos) override;
	void OnRightMouseDown(const Point& deltaMousePos) override;
	void OnRightMouseUp(const Point& deltaMousePos) override;

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {}
	
private:;
	static AppWindow* sharedInstance;

private:
	SwapChain* m_swap_chain;
	VertexShader* m_vertex_shader;
	PixelShader* m_pixel_shader;
	DepthBuffer* m_depth_buffer;
};

