#pragma once

#include <memory>
#include <vector>

#include <d3d11.h>
//#include <d3dx11.h>
#include <D3DCompiler.h>
#include <DirectXMath.h>
#include <dinput.h>
//#include <XAudio2.h> //Windows7à»ëO
#include <xaudio2.h>//Windows8.1à»ç~
#include <XAudio2fx.h>

#include <CommonStates.h>
#include <SpriteBatch.h>
#include <DirectXMath.h>
#include <Effects.h>
#include <VertexTypes.h>

#include "Application.h"
#include "Singleton.h"
#include "Com_ptr.h"

namespace engine
{
	class D3D11Wrapper : public Singleton<D3D11Wrapper>
	{
	public:
		HRESULT InitDevice(const Application& app);

		HRESULT Release();

		HRESULT Render();
	private:
		const TCHAR* CLASS_NAME = TEXT("D3D11Wrapper");
		D3D_DRIVER_TYPE						driverType = D3D_DRIVER_TYPE_NULL;
		D3D_FEATURE_LEVEL                   featureLevel = D3D_FEATURE_LEVEL_11_0;
		com_ptr<ID3D11Device>				d3dDevice;
		com_ptr<ID3D11DeviceContext>        deviceContext;
		com_ptr<IDXGISwapChain>             swapChain;
		com_ptr<ID3D11RenderTargetView>		renderTargetView;
		com_ptr<ID3D11Texture2D>            depthStencil;
		com_ptr<ID3D11DepthStencilView>     depthStencilView;
		std::shared_ptr<D3D11_VIEWPORT>		viewPort = nullptr;

		ID3D11InputLayout*                  batchInputLayout = nullptr;

		std::unique_ptr<DirectX::CommonStates>	commonStates;
		std::unique_ptr<DirectX::SpriteBatch>	sprites;
		std::unique_ptr<DirectX::BasicEffect>	batchEffect;
		DirectX::XMMATRIX						view;
		DirectX::XMMATRIX						world;
		DirectX::XMMATRIX						projection;

		std::vector<ID3D11ShaderResourceView*>	textures;

	};
}