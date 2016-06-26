#pragma once

#include <d3d11.h>
//#include <d3dx11.h>
#include <D3DCompiler.h>
//#include <D3DX10Math.h>
#include <dinput.h>
//#include <XAudio2.h> //Windows7à»ëO
#include <xaudio2.h>//Windows8.1à»ç~
#include <XAudio2fx.h>

#include "Application.h"
#include "Singleton.h"

namespace engine
{
	class D3D11Wrapper : public Singleton<D3D11Wrapper>
	{
	public:
		HRESULT InitDevice(const Application& app);

		HRESULT Render();
	private:
		const TCHAR* CLASS_NAME = TEXT("D3D11Wrapper");
		D3D_DRIVER_TYPE						driverType = D3D_DRIVER_TYPE_NULL;
		D3D_FEATURE_LEVEL                   featureLevel = D3D_FEATURE_LEVEL_11_0;
		ID3D11Device*                       d3dDevice = nullptr;
		ID3D11DeviceContext*                deviceContext = nullptr;
		IDXGISwapChain*                     swapChain = nullptr;
		ID3D11RenderTargetView*             renderTargetView = nullptr;
		ID3D11Texture2D*                    depthStencil = nullptr;
		ID3D11DepthStencilView*             depthStencilView = nullptr;
		ID3D11ShaderResourceView*           textureRV1 = nullptr;
		ID3D11ShaderResourceView*           textureRV2 = nullptr;
		ID3D11InputLayout*                  batchInputLayout = nullptr;
	};
}