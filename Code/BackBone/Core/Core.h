#ifndef CORE_H
#define CORE_H

#include "Directx11Includes.h"
#include "../FileLoaders/ResourceMgr.h"

namespace BackBone
{
	class Core
	{
	public:
		static ID3D11Device* device;
		static ID3D11DeviceContext* deviceContext;
		static IDXGISwapChain* swapChain;
		
		static ID3D11DepthStencilView* depthStencil;
		static ID3D11RenderTargetView* backBufferRTV;

		static D3D11_VIEWPORT viewPort;

		static HWND window;
		static DirectX::XMUINT2 resolution;
		static bool fullscreen;

		static ResourceMgr resourceMgr;

		static void Flush();

		class Init
		{
		public:
			static bool CreateDeviceAndSwapChain(HWND window, DirectX::XMUINT2 resolution, bool fullscreen);
			static bool CreateDepthStencil(DirectX::XMUINT2 resolution);
			static bool CreateBackBuffer();
			static void CreateViewPort(DirectX::XMUINT2 origin, DirectX::XMUINT2 resolution);
		};
	};
}

#endif