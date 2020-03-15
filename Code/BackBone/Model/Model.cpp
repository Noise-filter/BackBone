#include "Model.h"

#include "../Core/Core.h"
#include "../Definitions/BoundingVolumes.h"

using namespace BackBone;

template <class T>
ID3D11Buffer* createBuffer(const std::vector<T>& data, D3D11_BIND_FLAG bindFlag)
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.ByteWidth = sizeof(T) * data.size();
	bd.BindFlags = bindFlag;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexInitData;
	vertexInitData.pSysMem = data.data();
	Core::device->CreateBuffer(&bd, &vertexInitData, &buffer);
	return buffer;
}

ModelColored::ModelColored(std::vector<Definitions::VertexColored>& vertices)
{
	numberOfVertices = vertices.size();

	//Create bounding volume
	BoundingVolumes::Sphere sphere;
	BoundingVolumes::ComputeBoundingSphere(sphere, vertices.size(), &vertices[0].pos, sizeof(Definitions::VertexColored));

	vertexBuffer = createBuffer(vertices, D3D11_BIND_VERTEX_BUFFER);
}

ModelColored::ModelColored(std::vector<Definitions::VertexColored>& vertices, std::vector<unsigned int>& indices)
{
	numberOfVertices = vertices.size();
	numberOfIndices = indices.size();

	//Create bounding volume
	BoundingVolumes::Sphere sphere;
	BoundingVolumes::ComputeBoundingSphere(sphere, vertices.size(), &vertices[0].pos, sizeof(Definitions::VertexColored));

	vertexBuffer = createBuffer(vertices, D3D11_BIND_VERTEX_BUFFER);
	indexBuffer = createBuffer(indices, D3D11_BIND_INDEX_BUFFER);
}

ModelColored::~ModelColored()
{
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
}

void ModelColored::Render(ID3D11DeviceContext* const deviceContext)
{
	deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Definitions::VertexColored);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	if (indexBuffer != nullptr) {
		deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		deviceContext->DrawIndexed(numberOfIndices, 0, 0);
	}
	else
	{
		deviceContext->Draw(numberOfVertices, 0);
	}
}