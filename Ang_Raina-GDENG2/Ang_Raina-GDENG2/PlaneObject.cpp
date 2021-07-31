#include "PlaneObject.h"
#include "CameraManager.h"

PlaneObject::PlaneObject(std::string name) : AGameObject(name)
{
	
}

void PlaneObject::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	AGameObject::Initialize(shaderByteCode, sizeShader, color);

	vertex list[] =
	{
		//X - Y - Z
		{Vector3D(-0.8f,-0.8f,-0.025f),	color},
		{Vector3D(-0.8f,0.8f,-0.025f),	color},
		{Vector3D(0.8f,0.8f,-0.025f),		color},
		{Vector3D(0.8f,-0.8f,-0.025f),	color},

		//BACK FACE
		{Vector3D(0.8f,-0.8f,0.025f),		color},
		{Vector3D(0.8f,0.8f,0.025f),		color},
		{Vector3D(-0.8f,0.8f,0.025f),		color},
		{Vector3D(-0.8f,-0.8f,0.025f),	color},
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
	this->cb = GraphicsEngine::getInstance()->CreateConstantBuffer();
	this->cb->load(&cc, sizeof(constant));

	this->SetRotation(190.0f, 0.0f, 0.0f);
}

void PlaneObject::Update(double deltaTime)
{
	
}

void PlaneObject::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	//std::cout << "Drawing " << this->name << std::endl;
	constant cc;

	Matrix4x4 temp;

	//scale
	cc.m_world.SetIdentity();
	cc.m_world.SetScale(this->scale);

	// rotate
	temp.SetIdentity();
	temp.SetRotationZ(this->rotation.z);
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.SetRotationY(this->rotation.y);
	cc.m_world *= temp;

	temp.SetIdentity();
	temp.SetRotationX(this->rotation.x);
	cc.m_world *= temp;

	// translate
	temp.SetIdentity();
	temp.SetTranslation(this->position);
	cc.m_world *= temp;

	cc.m_view = CameraManager::getInstance()->GetMainCamera()->GetCameraMatrix();
	cc.m_projection.SetPerspectiveFOVLH(1.57f, (float)width / (float)height, 0.1f, 100.0f);

	this->cb->update(GraphicsEngine::getInstance()->GetImmediateDeviceContext(), &cc);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(vertexShader, this->cb);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(pixelShader, this->cb);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetVertexBuffer(this->vb);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetIndexBuffer(this->ib);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->DrawIndexedTriangleList(this->ib->GetSizeIndexList(), 0, 0);
}

PlaneObject::~PlaneObject()
{
}
