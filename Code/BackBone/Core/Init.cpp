#include "Core.h"

using namespace DirectX;
using namespace BackBone;

bool Core::Init::CreateDeviceAndSwapChain(HWND window, XMUINT2 resolution, bool fullscreen)
{
	UINT createDeviceFlags = 0;

	//Might give a slight improvment in speed but cannot be used when multithreading.
	createDeviceFlags = ::D3D11_CREATE_DEVICE_SINGLETHREADED;

	#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	const D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_STRETCHED;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.Width = resolution.x;
	swapChainDesc.BufferDesc.Height = resolution.y;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = !fullscreen;

	D3D_FEATURE_LEVEL initiatedFeatureLevel;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, 1, 
						D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &initiatedFeatureLevel, &deviceContext)))
	{
		if (deviceContext)
		{
			deviceContext->Release();
			deviceContext = NULL;
		}

		if (device)
		{
			device->Release();
			device = NULL;
		}

		if (swapChain)
		{
			swapChain->Release();
			swapChain = NULL;
		}
		return false;
	}

	return true;
}