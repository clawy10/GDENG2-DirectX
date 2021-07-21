#include "CubeObject.h"

CubeObject::CubeObject(std::string name) : AGameObject(name)
{
	
}

void CubeObject::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	AGameObject::Initialize(shaderByteCode, sizeShader, color);

	vertex list[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),		color},
		{Vector3D(-0.5f,0.5f,-0.5f),		color},
		{ Vector3D(0.5f,0.5f,-0.5f),		color},
		{ Vector3D(0.5f,-0.5f,-0.5f),     color},

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),		color},
		{ Vector3D(0.5f,0.5f,0.5f),		color},
		{ Vector3D(-0.5f,0.5f,0.5f),		color},
		{ Vector3D(-0.5f,-0.5f,0.5f),     color}
	};
	
	UINT size_list = ARRAYSIZE(list);
	this->vb = GraphicsEngine::getInstance()->CreateVertexBuffer();
	this->vb->load(list, sizeof(vertex), size_list, shaderByteCode, sizeShader);


	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};
	
	this->ib = GraphicsEngine::getInstance()->CreateIndexBuffer();
	this->ib->load(indexList, ARRAYSIZE(indexList));


	constant cc;
	cc.m_time = 0;
	this->cb = GraphicsEngine::getInstance()->CreateConstantBuffer();
	this->cb->load(&cc, sizeof(constant));
}

void CubeObject::Update(float deltaTime)
{
	AGameObject::Update(deltaTime);
	
	//this->rotation.x += deltaTime / 0.55f;
	//this->rotation.y += deltaTime / 0.55f;
	this->rotation.z += deltaTime / 0.55f;
}

CubeObject::~CubeObject()
{
	
}
