#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "../Definitions/GraphicalDefinitions.h"

namespace BackBone
{
	class ModelColored
	{
	public:
		ModelColored(std::vector<Definitions::VertexColored>& vertices);
		ModelColored(std::vector<Definitions::VertexColored>& vertices, std::vector<unsigned int>& indices);
		virtual ~ModelColored();

		void Render(ID3D11DeviceContext* const deviceContext);

	private:
		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;

		unsigned int numberOfVertices = 0;
		unsigned int numberOfIndices = 0;

	};
}

#endif