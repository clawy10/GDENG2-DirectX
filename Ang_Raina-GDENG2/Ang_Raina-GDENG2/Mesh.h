#pragma once
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "AGameObject.h"
#include "ConstantBuffer.h"

class Mesh : public Resource, public AGameObject
{
public:
	Mesh(const wchar_t* full_path, std::string name, PrimitiveType type);
	Mesh(PrimitiveType type, std::string name);
	~Mesh();

	//void Draw(VertexShader* vertexShader, PixelShader* pixelShader);

	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();

	void Update(double deltaTime) override;
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;

	void SetTexture(Texture* texture);

	float mass = 3.0f;
	
private:
	VertexBuffer* m_vertex_buffer;
	IndexBuffer* m_index_buffer;
	ConstantBuffer* m_constant_buffer;
	Texture* texture;

	

private:
	friend class DeviceContext;
};

