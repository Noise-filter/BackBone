#include "Core.h"

using namespace DirectX;
using namespace BackBone;

bool Core::Init::CreateDeviceAndSwapChain(HWND window, XMUINT2 resolution, bool fullscreen)
{
	Core::resolution = resolution;
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

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevels, 1, 
						D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &initiatedFeatureLevel, &deviceContext)))
	{
		if (deviceContext)
		{
			SAFE_RELEASE(deviceContext);
		}

		if (device)
		{
			SAFE_RELEASE(device);
		}

		if (swapChain)
		{
			SAFE_RELEASE(swapChain);
		}
		return false;
	}

	return true;
}

bool Core::Init::CreateDepthStencil(XMUINT2 resolution)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.ArraySize = 1;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.MipLevels = 1;
	textureDesc.MiscFlags = 0;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.Width = resolution.x;
	textureDesc.Height = resolution.y;

	if (FAILED(device->CreateTexture2D(&textureDesc, nullptr, &depthStencilBuffer)))
	{
		return false;
	}

	if (FAILED(device->CreateDepthStencilView(depthStencilBuffer, nullptr, &depthStencil)))
	{
		SAFE_RELEASE(depthStencil);
		return false;
	}

	return true;
}

bool Core::Init::CreateBackBuffer()
{
	ID3D11Texture2D *pBackBuffer = nullptr;
	if (FAILED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
	{
		SAFE_RELEASE(pBackBuffer);
		return false;
	}

	if (FAILED(device->CreateRenderTargetView(pBackBuffer, nullptr, &Core::backBufferRTV)))
	{
		SAFE_RELEASE(pBackBuffer);
		SAFE_RELEASE(backBufferRTV);
		return false;
	}

	SAFE_RELEASE(pBackBuffer);

	return true;
}

void Core::Init::CreateViewPort(DirectX::XMUINT2 origin, DirectX::XMUINT2 resolution)
{
	viewPort.TopLeftX = (FLOAT)origin.x;
	viewPort.TopLeftY = (FLOAT)origin.x;
	viewPort.Width = (FLOAT)resolution.x;
	viewPort.Height = (FLOAT)resolution.y;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
}

void Core::Init::CreateWireFrameRasterizer()
{
	D3D11_RASTERIZER_DESC wireFrameDesc;
	ZeroMemory(&wireFrameDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireFrameDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireFrameDesc.CullMode = D3D11_CULL_NONE;
	auto hr = device->CreateRasterizerState(&wireFrameDesc, &wireFrame);
}

void Core::Init::InitPipeline()
{
	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	flags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* VS = nullptr, * PS = nullptr;
	ID3DBlob* errorBlob = nullptr;
	auto result = D3DCompileFromFile(L"../Content/Shaders/coloredShader.shader", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VShader", "vs_4_0", flags, 0, &VS, &errorBlob);
	result = D3DCompileFromFile(L"../Content/Shaders/coloredShader.shader", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PShader", "ps_4_0", flags, 0, &PS, &errorBlob);

	device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), nullptr, &vertexShader);
	device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), nullptr, &pixelShader);

	deviceContext->VSSetShader(vertexShader, 0, 0);
	deviceContext->PSSetShader(pixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &inputLayout);
	deviceContext->IASetInputLayout(inputLayout);

	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(Definitions::cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	auto hr = device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);
	perObjectConstantBuffer.WVP = XMMatrixIdentity();

	camera = Camera(0.4f * 3.14f, (float)resolution.x / resolution.y, 1.0f, 1000.0f);
}