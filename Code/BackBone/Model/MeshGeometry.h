#ifndef MESH_GEOMETRY_H
#define MESH_GEOMETRY_H

#include <vector>
#include <map>
#include <string>
#include "../Definitions/GraphicalDefinitions.h"
#include "../Definitions/BoundingVolumes.h"
#include "Material.h"

namespace BackBone
{
	class MeshGeometry
	{
	public:
		struct Subset
		{
			unsigned int startIndex;
			unsigned int numIndex;
			Material* material;
			BoundingVolumes::AxisAlignedBox boundingBox;
		};

	public:
		MeshGeometry();
		~MeshGeometry();

		bool Init(std::vector<Definitions::Vertex>& vertices,
			std::vector<int>& indices, std::vector<Definitions::MeshGroupInfo>& subset,
			std::vector<Definitions::MaterialInfo>& materials);

		void Release();

		void Apply(ID3D11DeviceContext* deviceContext, unsigned int subset);

	private:
		void CreateBoundingVolume(BoundingVolumes::AxisAlignedBox& box, std::vector<Definitions::Vertex>& vertices, 
			std::vector<int>& indices, Definitions::MeshGroupInfo& subset);


	private:
		//Vertex buffer
		//Index buffer

		std::vector<Subset> subsets;
		std::map<std::string, Material*> materials;
	};
}
#endif