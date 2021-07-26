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
		{Vector3D(-0.5f,-0.5f,0.0f),   Vector3D(0,0,0),  Vector3D(0,1,0) }, // POS1
		{Vector3D(-0.5f,0.5f,0.0f),   Vector3D(1,1,0),  Vector3D(0,1,1) }, // POS2
		{ Vector3D(0.5f,0.5f,0.0f),	 Vector3D(0,0,1),  Vector3D(1,0,0) },// POS2
		{ Vector3D(0.5f,-0.5f,0.0f),   Vector3D(1,1,1),  Vector3D(0,0,1) }
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
	//cc.m_time = 0;
	cc.m_angle = 0;
	this->cb = GraphicsEngine::getInstance()->CreateConstantBuffer();
	this->cb->load(&cc, sizeof(constant));
}

void QuadObject::Update(double deltaTime)
{
	AGameObject::Update(deltaTime);
	//this->m_angle += 1.57f * deltaTime;
	this->ticks += 1.57f * deltaTime;
	
	if (this->speed > this->MAX_SPEED)
	{
		this->isSpeedUp = false;
	}
	else if (this->speed < this->MIN_SPEED)
	{
		this->isSpeedUp = true;
	}

	if (this->isSpeedUp)
	{
		this->speed += 0.05f;
	}
	else
	{
		this->speed -= 0.05f;
	}

	//std::cout << this->ticks << std::endl;

	this->m_angle = sin(this->ticks / this->speed) / 2.0f;
}

QuadObject::~QuadObject()
{
	
}
