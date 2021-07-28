#include "AGameObject.h"
#include "CameraManager.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
}

void AGameObject::SetPosition(float x, float y, float z)
{
	this->position = Vector3D(x, y, z);
}

void AGameObject::SetRotation(float x, float y, float z)
{
	this->rotation = Vector3D(x, y, z);
}

void AGameObject::SetScale(float x, float y, float z)
{
	this->scale = Vector3D(x, y, z);
}

std::string AGameObject::GetName()
{
	return this->name;
}

void AGameObject::Initialize(void* shaderByteCode, size_t sizeShader, Vector3D color)
{
	
}

void AGameObject::Update(double deltaTime)
{
	
}

void AGameObject::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	//std::cout << "Drawing " << this->name << std::endl;
	constant cc;
	
	Matrix4x4 temp;
	
	//scale
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
	cc.m_angle = this->m_angle;

	this->cb->update(GraphicsEngine::getInstance()->GetImmediateDeviceContext(), &cc);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(vertexShader, this->cb);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(pixelShader, this->cb);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetVertexBuffer(this->vb);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetIndexBuffer(this->ib);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->DrawIndexedTriangleList(this->ib->GetSizeIndexList(), 0, 0);
}

void AGameObject::release()
{
	this->vb->release();
	this->ib->release();
	this->cb->release();
	delete this;
}

AGameObject::~AGameObject()
{
	
}
