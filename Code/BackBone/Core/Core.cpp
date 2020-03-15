#include "Core.h"

using namespace BackBone;

//Initiate all static variables
ID3D11Device* Core::device = nullptr;
ID3D11DeviceContext* Core::deviceContext = nullptr;
IDXGISwapChain* Core::swapChain = nullptr;

ID3D11Texture2D* Core::depthStencilBuffer = nullptr;
ID3D11DepthStencilView* Core::depthStencil = nullptr;

ID3D11RenderTargetView* Core::backBufferRTV = nullptr;

ID3D11RasterizerState* Core::wireFrame;

D3D11_VIEWPORT Core::viewPort;

ID3D11VertexShader* Core::vertexShader = nullptr;
ID3D11PixelShader* Core::pixelShader = nullptr;

ID3D11InputLayout* Core::inputLayout = nullptr;

ID3D11Buffer* Core::cbPerObjectBuffer = nullptr;
Definitions::cbPerObject Core::perObjectConstantBuffer;

Camera Core::camera(0.4f * 3.14f, 1.0f, 1.0f, 1000.0f);

HWND Core::window = nullptr;
DirectX::XMUINT2 Core::resolution;
bool Core::fullscreen = false;

ResourceMgr Core::resourceMgr;

void Core::Flush()
{
	resourceMgr.Flush();

	swapChain->SetFullscreenState(FALSE, nullptr);

	SAFE_RELEASE(cbPerObjectBuffer);

	SAFE_RELEASE(inputLayout);

	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(pixelShader);

	SAFE_RELEASE(depthStencilBuffer);
	SAFE_RELEASE(depthStencil);

	SAFE_RELEASE(wireFrame);

	SAFE_RELEASE(backBufferRTV);

	SAFE_RELEASE(swapChain);
	
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}