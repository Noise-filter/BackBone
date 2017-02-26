#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "MeshGeometry.h"
#include "../Definitions/GraphicalDefinitions.h"

namespace BackBone
{
	class Model
	{
	public:
		Model();
		~Model();

		bool Init(std::vector<Definitions::Vertex>& vertices,
			std::vector<int>& indices, std::vector<Definitions::MeshGroupInfo>& subset,
			std::vector<Definitions::MaterialInfo>& materials);

		void Release();

		void Apply(ID3D11DeviceContext* deviceContext, unsigned int subset);

		unsigned int GetNumberOfSubsets();

	private:
		MeshGeometry mesh;

		std::vector<Definitions::Vertex> vertices;
		std::vector<int> indices;

	};
}

#endif