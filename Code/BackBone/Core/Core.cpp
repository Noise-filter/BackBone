#include "Core.h"

using namespace BackBone;

//Initiate all static variables
ID3D11Device *Core::device = NULL;
ID3D11DeviceContext *Core::deviceContext = NULL;
IDXGISwapChain* Core::swapChain = NULL;

HWND Core::window = NULL;
DirectX::XMUINT2 Core::resolution;
bool Core::fullscreen = false;