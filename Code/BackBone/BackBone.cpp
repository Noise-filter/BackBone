#include "BackBone.h"
#include "Core\Core.h"

using namespace BackBone;

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

void API::RenderModel()
{

}

void API::RenderScene()
{

}

void API::CreateModel(std::string filename)
{

}

void API::CreateTexture(std::string filename)
{

}

void API::DeleteModel()
{

}

void API::DeleteTexture()
{

}

void API::SetOptions()
{

}