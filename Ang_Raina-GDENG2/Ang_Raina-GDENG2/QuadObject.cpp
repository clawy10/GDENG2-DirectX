#include "QuadObject.h"

QuadObject::QuadObject(std::string name): AGameObject(name)
{
	
}

void QuadObject::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	AGameObject::Initialize(shaderByteCode, sizeShader, color);
	
	vertex list[] =
	{
		//X - Y - Z
		{Vector3D(-0.5f,-0.5f,0.0f),		color }, // POS1
		{Vector3D(-0.5f,0.5f,0.0f),       color}, // POS2
		{ Vector3D(0.5f,0.5f,0.0f),		color},// POS3
		{ Vector3D(0.5f,-0.5f,0.0f),		color} // POS 4

	};
	UINT size_list = ARRAYSIZE(list);
	this->vb = GraphicsEngine::getInstance()->CreateVertexBuffer();
	this->vb->load(list, sizeof(vertex), size_list, shaderByteCode, sizeShader);


	unsigned int indexList[] =
	{
		0,1,2,  //FIRST TRIANGLE
		2,3,0  //SECOND TRIANGLE
	};
	this->ib = GraphicsEngine::getInstance()->CreateIndexBuffer();
	this->ib->load(indexList, ARRAYSIZE(indexList));


	constant cc;
	cc.m_time = 0;
	this->cb = GraphicsEngine::getInstance()->CreateConstantBuffer();
	this->cb->load(&cc, sizeof(constant));
}

void QuadObject::Update(float deltaTime)
{
	AGameObject::Update(deltaTime);
}

QuadObject::~QuadObject()
{
	
}
