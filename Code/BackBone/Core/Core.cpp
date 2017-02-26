#include "Core.h"

using namespace BackBone;

//Initiate all static variables
ID3D11Device *Core::device = NULL;
ID3D11DeviceContext *Core::deviceContext = NULL;
IDXGISwapChain* Core::swapChain = NULL;

ID3D11DepthStencilView* Core::depthStencil = NULL;
ID3D11RenderTargetView* Core::backBufferRTV = NULL;

D3D11_VIEWPORT Core::viewPort;

HWND Core::window = NULL;
DirectX::XMUINT2 Core::resolution;
bool Core::fullscreen = false;

ResourceMgr Core::resourceMgr;

void Core::Flush()
{
	resourceMgr.Flush();

	swapChain->SetFullscreenState(FALSE, NULL);

	SAFE_RELEASE(depthStencil);
	SAFE_RELEASE(backBufferRTV);

	SAFE_RELEASE(swapChain);
	
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}