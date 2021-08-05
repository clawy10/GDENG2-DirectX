#include "QuadObject.h"
#include "CameraManager.h"
#include "TextureManager.h"

QuadObject::QuadObject(std::string name): AGameObject(name)
{
	
}

void QuadObject::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	AGameObject::Initialize(shaderByteCode, sizeShader, color);
	
	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.5f,0)},
		{ Vector3D(-0.5f,0.5f,0) },
		{ Vector3D(0.5f,0.5f,0) },
		{ Vector3D(0.5f,-0.5f,0)},
	};

	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	vertex vertex_list[] =
	{
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] }
	};
	
	UINT size_list = ARRAYSIZE(vertex_list);
	this->vb = GraphicsEngine::getInstance()->CreateVertexBuffer();
	this->vb->load(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);


	unsigned int indexList[] =
	{
		0,1,2,  //FIRST TRIANGLE
		2,3,0  //SECOND TRIANGLE
	};
	this->ib = GraphicsEngine::getInstance()->CreateIndexBuffer();
	this->ib->load(indexList, ARRAYSIZE(indexList));


	constant cc;
	this->cb = GraphicsEngine::getInstance()->CreateConstantBuffer();
	this->cb->load(&cc, sizeof(constant));

	this->texture = GraphicsEngine::getInstance()->GetTextureManager()->createTextureFromFile(L"..\\Assets\\Textures\\white-texture.jpg");
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
}

void QuadObject::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
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

	cc.m_view = CameraManager::getInstance()->GetSceneCamera()->GetCameraMatrix();
	cc.m_projection.SetPerspectiveFOVLH(1.57f, (float)width / (float)height, 0.1f, 100.0f);

	this->cb->update(GraphicsEngine::getInstance()->GetImmediateDeviceContext(), &cc);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(vertexShader, this->cb);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(pixelShader, this->cb);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetVertexBuffer(this->vb);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetIndexBuffer(this->ib);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetTexture(pixelShader, this->texture);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->DrawIndexedTriangleList(this->ib->GetSizeIndexList(), 0, 0);
}

QuadObject::~QuadObject()
{
	
}
