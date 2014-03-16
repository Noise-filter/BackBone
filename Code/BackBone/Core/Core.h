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

		static HWND window;
		static DirectX::XMUINT2 resolution;
		static bool fullscreen;

		class Init
		{
		public:
			static bool CreateDeviceAndSwapChain(HWND window, DirectX::XMUINT2 resolution, bool fullscreen);

		};
	};
}

#endif