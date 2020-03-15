#ifndef GRAPHICAL_DEFINITIONS_H
#define GRAPHICAL_DEFINITIONS_H

#include <string>
#include <memory>
#include "../Core/Directx11Includes.h"

namespace BackBone
{
	namespace Definitions
	{
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 tex;
		};

		struct VertexColored
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT4 color;
		};

		struct MeshGroupInfo
		{
			unsigned int startIndex;
			unsigned int numIndex;
			std::string materialName;
		};

		struct MaterialInfo
		{
			std::string materialName;
			DirectX::XMFLOAT3 ambientColor;
			DirectX::XMFLOAT3 diffuseColor;
			DirectX::XMFLOAT3 specularColor;
			DirectX::XMFLOAT3 transmissionFilter;
			float specularExponent;
			float opticalDensity;
			int reflectionSharpness;

			std::string ambientTexture;
			std::string diffuseTexture;
			std::string specularTexture;
			std::string specularHighlightTexture;
			std::string alphaTexture;
			std::string bumpTexture;
			std::string displacementTexture;
			std::string stencilTexture;
		};

		struct cbPerObject
		{
			DirectX::XMMATRIX WVP;
		};
	}
}

#endif