#include "BackBone.h"
#include "Core\Core.h"

using namespace BackBone;

bool API::Init(HWND hwnd, unsigned int width, unsigned int height, bool fullscreen)
{
	if (!Core::Init::CreateDeviceAndSwapChain(hwnd, DirectX::XMUINT2(width, height), fullscreen))
	{
		return false;
	}

	return true;
}

void API::Flush()
{

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