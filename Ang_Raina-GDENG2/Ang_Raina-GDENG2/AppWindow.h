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

class AppWindow : public Window
{
public:
	static AppWindow* getInstance();
	static void initialize();
	static void destroy();

	virtual void OnCreate() override;
	virtual void OnDestroy() override;
	virtual void OnUpdate() override;

	void CreateGraphicsWindow();

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;

private:
	SwapChain* m_swap_chain;
	VertexShader* m_vertex_shader;
	PixelShader* m_pixel_shader;
	DepthBuffer* m_depth_buffer;

	long m_old_delta;
	long m_new_delta;
	float m_delta_time;
};

