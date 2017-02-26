#include "Model.h"

#include "../Definitions/BoundingVolumes.h"

using namespace BackBone;

Model::Model()
{
}

Model::~Model()
{
}

bool Model::Init(std::vector<Definitions::Vertex>& vertices,
	std::vector<int>& indices, std::vector<Definitions::MeshGroupInfo>& subset,
	std::vector<Definitions::MaterialInfo>& materials)
{
	this->vertices = vertices;
	this->indices = indices;

	mesh.Init(vertices, indices, subset, materials);

	//Create bounding volume
	BoundingVolumes::Sphere sphere;
	BoundingVolumes::ComputeBoundingSphere(sphere, vertices.size(), &vertices[0].pos, sizeof(Definitions::Vertex));

	return true;
}

void Model::Release()
{
	mesh.Release();
}

void Model::Apply(ID3D11DeviceContext* deviceContext, unsigned int subset)
{

}

unsigned int Model::GetNumberOfSubsets()
{
	return 0;
}