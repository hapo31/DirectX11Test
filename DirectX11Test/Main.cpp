#include <Windows.h>
#include <string>

#include "Defs.h"
#include "engine.h"
#include "Application.h"

using namespace std;
using namespace engine;

HRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wpara, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	
	D3D11Wrapper& d3d11 = Singleton<D3D11Wrapper>::get_instance();

	wc.hInstance = hInstance;
	wc.lpfnWndProc = wndproc;
	wc.lpszClassName = defs::CLASSNAME.c_str();
	wc.style = CS_HREDRAW | CS_VREDRAW;
	
	if (FAILED(RegisterClass(&wc))) {
		MessageBox(nullptr, TEXT("Failed Register Window"), TEXT(""), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	DWORD style = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE;

	auto hwnd = CreateWindow(wc.lpszClassName, TEXT("DirectX11 Test"), style, 0, 0, 1280, 720, NULL, 0, hInstance, 0);
	
	LPVOID lpMessageBuffer;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // デフォルト ユーザー言語 
		(LPTSTR)&lpMessageBuffer,
		0,
		NULL);
	wstring str = (wchar_t*)lpMessageBuffer;
	LocalFree(lpMessageBuffer);

	if (hwnd == NULL) return 1;

	Application app(hwnd);
	app.set_hInstance(hInstance);

	MSG msg = {0};
	ShowWindow(hwnd, SW_SHOW);


	if (FAILED(d3d11.InitDevice(app))) return 1;

	while( WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//びょうが
			d3d11.Render();
		}
	}


	return 0;
}

HRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:

		return 0;
	case WM_ERASEBKGND: //背景の消去をもみ消して画面のちらつきを抑える

		return 0;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}