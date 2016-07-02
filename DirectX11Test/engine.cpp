#pragma once

#include<DDSTextureLoader.h>

#include "engine.h"
#include "Application.h"
#include "DXTSprite.h"

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "dxgi.lib") 
#pragma comment(lib, "d3d11.lib") 
#pragma comment(lib, "DirectXTK.lib")
//#pragma comment(lib, "d3dx11.lib") 
#pragma comment(lib, "d3dCompiler.lib")
//#pragma comment(lib, "d3dx10.lib")

using namespace std;
using namespace DirectX;

HRESULT engine::D3D11Wrapper::InitDevice(const Application& app)
{
	HRESULT hr = S_OK;

	RECT rc = app.get_client_size();
	UINT height = rc.bottom - rc.top;
	UINT width = rc.right - rc.left;

	//�h���C�o�^�C�v�̗�
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	//�t���[�`���[���x���̗񋓁@���Ԃ�ǂ�DirectX�g�����I�Ȃ��
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
	};

	//�X���b�v�`�F�C���̏�����
	DXGI_SWAP_CHAIN_DESC desc = { 0 };

	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = app.get_hwnd();
	desc.SampleDesc.Count = 1;
	desc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	desc.Windowed = false;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		featureLevels, 3, D3D11_SDK_VERSION, &desc, &swapChain, &d3dDevice, &featureLevel, &deviceContext)))
	{
		MessageBox(app.get_hwnd(), TEXT("D3D11Device�̍쐬�܂���SwapChain�̍쐬�Ɏ��s���܂���"), CLASS_NAME, MB_OK);
		return E_FAIL;
	}

	//�����_�����O�^�[�Q�b�g�r���[
	ID3D11Texture2D* backBuffer = nullptr;
	swapChain->GetBuffer(NULL, IID_PPV_ARGS(&backBuffer));

	if (FAILED(hr = d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView))) {
		MessageBox(NULL, TEXT("�f�t�H���g�����_�[�^�[�Q�b�g�r���[�̐����Ɏ��s���܂����B"), TEXT("Error"), MB_ICONWARNING);
		backBuffer->Release();
		return hr;
	}
	// 
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
		MessageBox(NULL, TEXT("�[�x�X�e���V���e�N�X�`���̐����Ɏ��s���܂����B"), TEXT("Error"), MB_ICONWARNING);
        backBuffer->Release();
		return hr;
	}

	if (FAILED(hr = d3dDevice->CreateDepthStencilView(depthStencil, nullptr, &depthStencilView))) {
		MessageBox(NULL, TEXT("�[�x�X�e���V���r���[�̐����Ɏ��s���܂����B"), TEXT("Error"), MB_ICONWARNING);
        backBuffer->Release();
        depthStencil->Release();
		return hr;
	}

	backBuffer->Release();
	depthStencil->Release();

	/*
		�f�o�C�X�̏��������Ԃ񂱂��܂�
	*/


	/*
		�r���[�|�[�g�̐ݒ�
	*/
	deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	viewPort = make_shared<D3D11_VIEWPORT>();
	viewPort->TopLeftX = 0.0f;
	viewPort->TopLeftY = 0.0f;
	viewPort->Width = (float)width;
	viewPort->Height = (float)height;
	viewPort->MinDepth = 0.0f;
	viewPort->MaxDepth = 1.0f;

	deviceContext->RSSetViewports(1, viewPort.get());

	/*
		���̃R�[�h�Ŏg���Ă��Ȃ��������R�����g�A�E�g
	*/

	//commonStates = make_unique<CommonStates>(d3dDevice);
	sprites = make_shared<SpriteBatch>(deviceContext);


	//batchEffect = make_unique<BasicEffect>(d3dDevice);

	//batchEffect->SetVertexColorEnabled(true);

	//{
	//	void const* shaderByteCode;
	//	size_t byteCodeLength;

	//	batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//	hr = d3dDevice->CreateInputLayout(VertexPositionColor::InputElements,
	//		VertexPositionColor::InputElementCount,
	//		shaderByteCode, byteCodeLength,
	//		&batchInputLayout);
	//	if (FAILED(hr))
	//		return hr;
	//}

	//���Ԃ�J�����Ƃ��̐ݒ�
	//XMVECTOR Eye = XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
	//XMVECTOR At = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//view = XMMatrixLookAtLH(Eye, At, Up);
	//world = XMMatrixIdentity();
	//projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, width / (float)height, 0.01f, 100.0f);

	//batchEffect->SetProjection(projection);

    /*
        ���\�[�X�ǂݍ���
    */

	//ID3D11ShaderResourceView* tex;
	//ID3D11Resource* res;

	//hr = CreateDDSTextureFromFile(d3dDevice, TEXT("Resources/damedesu.dds"), &res, &tex );

    texture.createTexture(TEXT("Resources/damedesu.dds"));

	return hr;
}

HRESULT engine::D3D11Wrapper::Render()
{
	//��ʂ���������
	deviceContext->ClearRenderTargetView(renderTargetView, Colors::Aquamarine);
	deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	static float x = 10;

	x = x > 1280 ? -1280 : x + 1;

    sprites->Begin(SpriteSortMode_Deferred);
	//�Ȃ�ƂȂ�ƍ�����W�n�ŕ`��ʒu�����߂���
	sprites->Draw(texture.getTextureResource(), XMFLOAT2(x, 75), nullptr, Colors::White);

    sprites->End();
	return this->swapChain->Present(0, 0);;
}

HRESULT engine::D3D11Wrapper::Release()
{
	d3dDevice->Release();
	deviceContext->Release();

	return S_OK;
}