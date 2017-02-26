#include "MeshGeometry.h"

#include <DirectXMath.h>

using namespace BackBone;
using namespace Definitions;
using namespace DirectX;

MeshGeometry::MeshGeometry()
{
}

MeshGeometry::~MeshGeometry()
{
}

bool MeshGeometry::Init(std::vector<Definitions::Vertex>& vertices,
	std::vector<int>& indices, std::vector<Definitions::MeshGroupInfo>& subset,
	std::vector<Definitions::MaterialInfo>& materials)
{
	for (unsigned int i = 0; i < materials.size(); i++)
	{
		Material* material = this->materials[materials.at(i).materialName];
		if (material == NULL)
		{
			material = new Material;
			if (material->Init(materials.at(i)))
			{
				this->materials[materials.at(i).materialName] = material;
			}
			else
			{
				return false;
			}
		}
	}

	Subset set;
	for (unsigned int i = 0; i < subset.size(); ++i)
	{
		set.startIndex = subset.at(i).startIndex;
		set.numIndex = subset.at(i).numIndex;
		set.material = this->materials[subset.at(i).materialName];
		if (set.material == NULL)
		{
			return false;
		}

		//Create bounding volume
		CreateBoundingVolume(set.boundingBox, vertices, indices, subset.at(i));
	}

	//Create vertexbuffer

	//Create indexbuffer

	return true;
}

void MeshGeometry::Release()
{
	//Release vertexbuffer
	//Release indexbuffer
}

void MeshGeometry::Apply(ID3D11DeviceContext* deviceContext, unsigned int subset)
{
	//Apply vertexbuffer
	//Apply indexbuffer
	//Apply material
}

void MeshGeometry::CreateBoundingVolume(BoundingVolumes::AxisAlignedBox& box, std::vector<Definitions::Vertex>& vertices,
	std::vector<int>& indices, Definitions::MeshGroupInfo& subset)
{
	XMFLOAT3 minF3(INFINITY, INFINITY, INFINITY);
	XMFLOAT3 maxF3(-INFINITY, -INFINITY, -INFINITY);

	XMVECTOR min = XMLoadFloat3(&minF3);
	XMVECTOR max = XMLoadFloat3(&maxF3);

	for (unsigned int i = subset.startIndex; i < subset.numIndex; i++)
	{
		XMVECTOR p = XMLoadFloat3(&vertices.at(indices.at(i)).pos);
		min = XMVectorMin(min, p);
		max = XMVectorMax(max, p);
	}

	XMStoreFloat3(&box.center, 0.5f*(min + max));
	XMStoreFloat3(&box.extents, 0.5f*(max - min));
}