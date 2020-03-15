#ifndef BACKBONE_H
#define BACKBONE_H

#include <string>
#include <Windows.h>
#include <vector>

#include "BackBoneAPI_Preprocessor.h"

#include "Definitions\GraphicalDefinitions.h"
#include "Model/Model.h"
#include "Model/ModelInstance.h"

namespace BackBone
{
	class BACKBONEAPI_USAGE API
	{
	public:
		static bool Init(HWND hwnd, unsigned int width, unsigned int height, bool fullscreen);
		static void Flush();

		static void BeginFrame();
		static void EndFrame();

		static void RenderModel(std::unique_ptr<ModelInstance>& model);
		static void RenderScene();

		static std::unique_ptr<ModelInstance> CreateModel(std::string filename);
		static std::unique_ptr<ModelInstance> CreateModel(std::vector<Definitions::VertexColored> vertices);
		static std::unique_ptr<ModelInstance> CreateModel(std::vector<Definitions::VertexColored> vertices, std::vector<unsigned int> indices);
		static void CreateTexture(std::string filename);

		static void DeleteTexture();

		static void SetOptions(bool wireFrame);

	};
}

#endif