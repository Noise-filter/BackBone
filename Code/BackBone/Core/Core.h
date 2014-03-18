#ifndef CORE_H
#define CORE_H

#include "Directx11Includes.h"

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

		static HWND window;
		static DirectX::XMUINT2 resolution;
		static bool fullscreen;

		static void Flush();

		class Init
		{
		public:
			static bool CreateDeviceAndSwapChain(HWND window, DirectX::XMUINT2 resolution, bool fullscreen);
			static bool CreateDepthStencil(DirectX::XMUINT2 resolution);
			static bool CreateBackBuffer();
		};
	};
}

#endif