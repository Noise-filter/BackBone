#ifndef LOADERS_H
#define LOADERS_H

#include <string>
#include <vector>
#include "../Core/Directx11Includes.h"
#include "../Definitions/GraphicalDefinitions.h"

namespace BackBone
{
	namespace Loaders
	{
		class ModelLoader
		{
		public:
			static std::string modelPath;

			static bool LoadOBJ(std::string filename, std::vector<Definitions::Vertex>& vertices,
				std::vector<int>& indices, std::vector<Definitions::MeshGroupInfo>& subset,
				std::vector<Definitions::MaterialInfo>& materials);
		};
	}
}

#endif