#ifndef CORE_H
#define CORE_H

#include <array>

#include "Directx11Includes.h"
#include "../Definitions/GraphicalDefinitions.h"
#include "../FileLoaders/ResourceMgr.h"
#include "Camera.h"

namespace BackBone
{
	class Core
	{
	public:
		static ID3D11Device* device;
		static ID3D11DeviceContext* deviceContext;
		static IDXGISwapChain* swapChain;

		static ID3D11Texture2D* depthStencilBuffer;
		static ID3D11DepthStencilView* depthStencil;

		static ID3D11RenderTargetView* backBufferRTV;

		static ID3D11RasterizerState* wireFrame;

		static D3D11_VIEWPORT viewPort;

		static ID3D11VertexShader* vertexShader;
		static ID3D11PixelShader* pixelShader;

		static ID3D11InputLayout* inputLayout;

		static ID3D11Buffer* cbPerObjectBuffer;
		static Definitions::cbPerObject perObjectConstantBuffer;

		static Camera camera;

		static HWND window;
		static DirectX::XMUINT2 resolution;
		static bool fullscreen;

		static ResourceMgr resourceMgr;

		static void Flush();

		static std::array<FLOAT, 4> getClearColor() {
			return std::array<FLOAT, 4> { 1.0f, 0.0f, 1.0f, 1.0f };
		}

		class Init
		{
		public:
			static bool CreateDeviceAndSwapChain(HWND window, DirectX::XMUINT2 resolution, bool fullscreen);
			static bool CreateDepthStencil(DirectX::XMUINT2 resolution);
			static bool CreateBackBuffer();
			static void CreateViewPort(DirectX::XMUINT2 origin, DirectX::XMUINT2 resolution);
			static void CreateWireFrameRasterizer();
			static void InitPipeline();
		};
	};
}

#endif