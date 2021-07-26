#include "PlaneObject.h"

PlaneObject::PlaneObject(std::string name) : AGameObject(name)
{
	
}

void PlaneObject::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	AGameObject::Initialize(shaderByteCode, sizeShader, color);

	vertex list[] =
	{
		//X - Y - Z
		{Vector3D(-0.8f,-0.8f,-0.025f),    Vector3D(1,1,1),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.8f,0.8f,-0.025f),    Vector3D(1,1,1), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.8f,0.8f,-0.025f),   Vector3D(1,1,1),  Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.8f,-0.8f,-0.025f),     Vector3D(1,1,1), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(0.8f,-0.8f,0.025f),    Vector3D(1,1,1), Vector3D(0,0.2f,0) },
		{Vector3D(0.8f,0.8f,0.025f),    Vector3D(1,1,1), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.8f,0.8f,0.025f),   Vector3D(1,1,1),  Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.8f,-0.8f,0.025f),     Vector3D(1,1,1), Vector3D(0,0.2f,0) },
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
	//cc.m_time = 0;
	cc.m_angle = 0;
	this->cb = GraphicsEngine::getInstance()->CreateConstantBuffer();
	this->cb->load(&cc, sizeof(constant));

	this->SetRotation(190.0f, 0.0f, 0.0f);
}

void PlaneObject::Update(double deltaTime)
{
	
}

PlaneObject::~PlaneObject()
{
}
