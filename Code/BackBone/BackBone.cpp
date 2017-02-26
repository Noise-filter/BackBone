#include "BackBone.h"
#include "Core\Core.h"
#include "Definitions\GraphicalDefinitions.h"

using namespace BackBone;
using namespace Definitions;

bool API::Init(HWND hwnd, unsigned int width, unsigned int height, bool fullscreen)
{
	DirectX::XMUINT2 resolution(width, height);
	if (!Core::Init::CreateDeviceAndSwapChain(hwnd, resolution, fullscreen))
	{
		return false;
	}

	if (!Core::Init::CreateDepthStencil(resolution))
	{
		return false;
	}

	if (!Core::Init::CreateBackBuffer())
	{
		return false;
	}

	Core::Init::CreateViewPort(DirectX::XMUINT2(0, 0), resolution);

	Core::resourceMgr.SetModelDefaultPath("../Content/Models/");

	return true;
}

void API::Flush()
{
	Core::Flush();
}

void API::SetView(float matrix[16])
{

}

void API::SetProjection(float matrix[16])
{

}

void API::BeginFrame()
{

}

void API::EndFrame()
{

}

void API::RenderModel(ModelInstance* modelInstance)
{

}

void API::RenderScene()
{

}

ModelInstance* API::CreateModel(std::string filename)
{
	ModelInstance* model = new ModelInstance();
	
	model->model = (BackBone::Definitions::ModelInstance::Model*)Core::resourceMgr.CreateModel(filename);

	return model;
}

void API::CreateTexture(std::string filename)
{

}

void API::DeleteModel(Definitions::ModelInstance* modelInstance)
{
	SAFE_DELETE(modelInstance);
}

void API::DeleteTexture()
{

}

void API::SetOptions()
{

}