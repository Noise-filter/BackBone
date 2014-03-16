#include <iostream>
using namespace std;
#include <Windows.h>

#include <vld.h>
#include "../BackBone/BackBone.h"
using namespace BackBone;

LRESULT CALLBACK			WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int Update(float deltaTime);
int Render();
int Init(HWND hWnd);

const unsigned int SCREEN_WIDTH = 1024;
const unsigned int SCREEN_HEIGHT = 768;

int Update(float deltaTime)
{

	return 0;
}

int Render()
{
	return 0;
}

int Init(HWND hWnd)
{
	if (!API::Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT, false))
	{
		return -1;
	}

	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	if (SetDllDirectory("..\\DLL") == FALSE)
	{
		return -1;
	}

	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(NULL,
		"WindowClass",
		"BackBone",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	Init(hWnd);
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Update(1.0f);
		Render();
		

	}

	return 0;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		} break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}