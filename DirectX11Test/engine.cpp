#pragma once
#include <typeinfo>

#include "engine.h"
#include "Application.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "dxgi.lib") 
#pragma comment(lib, "d3d11.lib") 
//#pragma comment(lib, "d3dx11.lib") 
#pragma comment(lib, "d3dCompiler.lib")
//#pragma comment(lib, "d3dx10.lib")

void safe_release(IUnknown* obj);

HRESULT engine::D3D11Wrapper::InitDevice(const Application& app)
{
	HRESULT hr = S_OK;

	RECT rc = app.get_client_size();
	UINT height = rc.bottom - rc.top;
	UINT width = rc.right - rc.left;
	
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
	};

	DXGI_SWAP_CHAIN_DESC sd = {0};

	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = app.get_hwnd();
	sd.SampleDesc.Count = 1;
	sd.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	sd.Windowed = false;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		featureLevels, 3, D3D11_SDK_VERSION, &sd, &swapChain, &d3dDevice, &featureLevel, &deviceContext)))
	{
		MessageBox(app.get_hwnd(), TEXT("D3D11Deviceの作成またはSwapChainの作成に失敗しました"), CLASS_NAME, MB_OK);
		return E_FAIL;
	}

	//レンダリングターゲットビュー
	ID3D11Texture2D* backBuffer = nullptr;
	swapChain->GetBuffer(NULL, IID_PPV_ARGS(&backBuffer));
	
	if (FAILED(hr = d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView))) {
		MessageBox(NULL, TEXT("デフォルトレンダーターゲットビューの生成に失敗しました。"), TEXT("Error"), MB_ICONWARNING);
		safe_release(backBuffer);
		return hr;
	}
	D3D11_TEXTURE2D_DESC desc_depth;
	ZeroMemory(&desc_depth, sizeof(desc_depth));

	desc_depth.Width = width;
	desc_depth.Height = height;
	desc_depth.MipLevels = 1;
	desc_depth.ArraySize = 1;
	desc_depth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc_depth.SampleDesc.Count = 1;
	desc_depth.SampleDesc.Quality = 0;
	desc_depth.Usage = D3D11_USAGE_DEFAULT;
	desc_depth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc_depth.CPUAccessFlags = 0;
	desc_depth.MiscFlags = 0;
	ID3D11Texture2D* depthStencil = nullptr;

	if (FAILED(hr = d3dDevice->CreateTexture2D(&desc_depth, nullptr, &depthStencil))) {
		MessageBox(NULL, TEXT("深度ステンシルテクスチャの生成に失敗しました。"), TEXT("Error"), MB_ICONWARNING);
		safe_release(backBuffer);
		return hr;
	}

	if (FAILED(hr = d3dDevice->CreateDepthStencilView(depthStencil, nullptr, &depthStencilView))) {
		MessageBox(NULL, TEXT("深度ステンシルビューの生成に失敗しました。"), TEXT("Error"), MB_ICONWARNING);
		safe_release(backBuffer);
		safe_release(depthStencil);
		return hr;
	}

	safe_release(backBuffer);
	safe_release(depthStencil);

	return hr;
}

HRESULT engine::D3D11Wrapper::Render()
{
	return this->swapChain->Present(0, 0);;
}


inline void safe_release(IUnknown* obj)
{
	if (obj != nullptr) {
		obj->Release();
		obj = nullptr;
	}
}