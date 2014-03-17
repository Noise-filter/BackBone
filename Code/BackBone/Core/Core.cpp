#include "Core.h"

using namespace BackBone;

//Initiate all static variables
ID3D11Device *Core::device = NULL;
ID3D11DeviceContext *Core::deviceContext = NULL;
IDXGISwapChain* Core::swapChain = NULL;

ID3D11DepthStencilView* Core::depthStencil = NULL;

D3D11_VIEWPORT Core::viewPort;

HWND Core::window = NULL;
DirectX::XMUINT2 Core::resolution;
bool Core::fullscreen = false;

void Core::Flush()
{
	swapChain->SetFullscreenState(FALSE, NULL);

	SAFE_RELEASE(depthStencil);

	SAFE_RELEASE(swapChain);
	
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}