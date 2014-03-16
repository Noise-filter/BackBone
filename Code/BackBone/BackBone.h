#ifndef BACKBONE_H
#define BACKBONE_H

#include <vld.h>
#include <string>

#include "BackBoneAPI_Preprocessor.h"

namespace BackBone
{
	class BACKBONEAPI_USAGE API
	{
	public:
		static bool Init(HWND hwnd, unsigned int width, unsigned int height, bool fullscreen);
		static void Flush();

		static void SetView(float matrix[16]);
		static void SetProjection(float matrix[16]);

		static void BeginFrame();
		static void EndFrame();

		static void RenderModel();
		static void RenderScene();

		static void CreateModel(std::string filename);
		static void CreateTexture(std::string filename);

		static void DeleteModel();
		static void DeleteTexture();

		static void SetOptions();

	};
}

#endif