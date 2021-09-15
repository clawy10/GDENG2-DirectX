#include "Mesh.h"
#include <locale>
#include <codecvt>
#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <tiny_obj_loader.h>
#include "CameraManager.h"
#include "GraphicsEngine.h"
#include "VertexMesh.h"
#include "TextureManager.h"
#include "DeviceContext.h"


Mesh::Mesh(const wchar_t* full_path, std::string name, PrimitiveType type) : Resource(full_path), AGameObject(name, type)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::string inputfile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(full_path); 
	
	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty())
	{
		throw std::exception("Mesh not created successfully");
	}
	if (!res)
	{
		throw std::exception("Mesh not created successfully");
	}

	if (shapes.size() > 1)
	{
		throw std::exception("Mesh not created successfully");
	}

	std::vector<VertexMesh> listVertices; 
	std::vector<unsigned int> listIndices; 

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t indexOffset = 0;
		listVertices.reserve(shapes[s].mesh.indices.size());
		listIndices.reserve(shapes[s].mesh.indices.size());
		
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char numFaceVertices = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < numFaceVertices; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[indexOffset + v];
				
				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0]; 
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1]; 
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = 0;
				tinyobj::real_t ty = 0;
				if (index.texcoord_index >= 0)
				{
					tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}
				 
				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				listVertices.push_back(vertex);

				listIndices.push_back(indexOffset + v);
			}
			indexOffset += numFaceVertices; 
		}
	}
	this->texture = GraphicsEngine::getInstance()->GetTextureManager()->createTextureFromFile(L"..\\Assets\\Textures\\white-texture.jpg");
	this->texture->CreateSamplerState(); 

	void* shader_byte_code = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine::getInstance()->GetVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &sizeShader);

	this->m_vertex_buffer = GraphicsEngine::getInstance()->CreateVertexBuffer();
	this->m_vertex_buffer->load(&listVertices[0], sizeof(VertexMesh), listVertices.size(), shader_byte_code, (UINT)sizeShader);

	this->m_index_buffer = GraphicsEngine::getInstance()->CreateIndexBuffer();
	this->m_index_buffer->load(&listIndices[0], (UINT)listIndices.size());

	constant cc;
	this->m_constant_buffer = GraphicsEngine::getInstance()->CreateConstantBuffer();
	this->m_constant_buffer->load(&cc, sizeof(constant));
}

Mesh::Mesh(PrimitiveType type, std::string name) : Resource(), AGameObject(name, type)
{
	
}

Mesh::~Mesh()
{
}

VertexBuffer* Mesh::GetVertexBuffer()
{
	return this->m_vertex_buffer;
}

IndexBuffer* Mesh::GetIndexBuffer()
{
	return this->m_index_buffer;
}

void Mesh::Update(double deltaTime)
{
}

void Mesh::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetVertexBuffer(this->m_vertex_buffer);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetIndexBuffer(this->m_index_buffer);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetTexture(pixelShader, this->texture);
	constant cc;
	Matrix4x4 temp;

	//scale
	cc.m_world.SetIdentity();
	cc.m_world.SetScale(this->scale);

	// rotate
	temp = MathTools::QuaternionToMatrix(this->orientation.x, this->orientation.y, this->orientation.z, this->orientation.w);
	cc.m_world *= temp;

	// translate
	temp.SetIdentity();
	temp.SetTranslation(this->position);
	cc.m_world *= temp;

	cc.m_view = CameraManager::getInstance()->GetSceneCamera()->GetCameraViewMatrix();
	cc.m_projection = CameraManager::getInstance()->GetSceneCamera()->GetCameraProjectionMatrix();

	this->m_constant_buffer->update(GraphicsEngine::getInstance()->GetImmediateDeviceContext(), &cc);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(vertexShader, this->m_constant_buffer);
	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->SetConstantBuffer(pixelShader, this->m_constant_buffer);

	GraphicsEngine::getInstance()->GetImmediateDeviceContext()->DrawIndexedTriangleList(this->m_index_buffer->GetSizeIndexList(), 0, 0);
}

void Mesh::SetTexture(Texture* texture)
{
	this->texture = texture;
	this->texture->CreateSamplerState();
}
