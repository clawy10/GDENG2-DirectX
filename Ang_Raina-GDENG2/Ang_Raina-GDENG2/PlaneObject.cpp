#include "PlaneObject.h"
#include "CameraManager.h"
#include "TextureManager.h"

PlaneObject::PlaneObject(std::string name) : AGameObject(name)
{
	
}

void PlaneObject::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	AGameObject::Initialize(shaderByteCode, sizeShader, color);

	Vector3D position_list[] =
	{
		{ Vector3D(-0.5f,-0.2f,-0.5f)},
		{ Vector3D(-0.5f,0.2f,-0.5f) },
		{ Vector3D(0.5f,0.2f,-0.5f) },
		{ Vector3D(0.5f,-0.2f,-0.5f)},

		//BACK FACE
		{ Vector3D(0.5f,-0.2f,0.5f) },
		{ Vector3D(0.5f,0.2f,0.5f) },
		{ Vector3D(-0.5f,0.2f,0.5f)},
		{ Vector3D(-0.5f,-0.2f,0.5f) }
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
		{ position_list[3],texcoord_list[3] },

		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },

		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }
	};

	UINT size_list = ARRAYSIZE(vertex_list);
	this->vb = GraphicsEngine::getInstance()->CreateVertexBuffer();
	this->vb->load(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

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

	this->texture = GraphicsEngine::getInstance()->GetTextureManager()->createTextureFromFile(L"..\\Assets\\Textures\\white-texture.jpg");

	
}

void PlaneObject::Update(double deltaTime)
{
	AGameObject::Update(deltaTime);
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
	temp = Matrix4x4::QuaternionToMatrix(this->orientation.x, this->orientation.y, this->orientation.z, this->orientation.w);
	cc.m_world *= temp;

	// translate
	temp.SetIdentity();
	temp.SetTranslation(this->position);
	cc.m_world *= temp;

	cc.m_view = CameraManager::getInstance()->GetSceneCamera()->GetCameraViewMatrix();
	cc.m_projection = CameraManager::getInstance()->GetSceneCamera()->GetCameraProjectionMatrix();

	this->cb->update(GraphicsEngine::getInstance()->GetImmediateDeviceContext(), &cc);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(vertexShader, this->cb);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(pixelShader, this->cb);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetVertexBuffer(this->vb);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetIndexBuffer(this->ib);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetTexture(pixelShader, this->texture);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->DrawIndexedTriangleList(this->ib->GetSizeIndexList(), 0, 0);
}

PlaneObject::~PlaneObject()
{
}
