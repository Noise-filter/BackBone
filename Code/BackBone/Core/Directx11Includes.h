#ifndef DIRECTX_11_INCLUDES_H
#define DIRECTX_11_INCLUDES_H

#define NOMINMAX
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")

#ifdef _DEBUG
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#endif

#endif