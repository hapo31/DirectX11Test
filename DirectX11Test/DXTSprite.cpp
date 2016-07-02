#pragma once
#include "DXTSprite.h"

#include "engine.h"
#include <DDSTextureLoader.h>

engine::DXTSprite::DXTSprite(const defs::tstring& filename)
{
    createTexture(filename);
}

HRESULT engine::DXTSprite::createTexture(const defs::tstring& filename)
{
    auto& device = engine::D3D11Wrapper::get_instance().getDevice();
    return last_error = DirectX::CreateDDSTextureFromFile(device, filename.c_str(), &res, &tex);
}

ULONG engine::DXTSprite::Release()
{
    ULONG r;
    if (tex != nullptr)
        r = tex->Release();
    if (res != nullptr)
        r = res->Release();
    return r;
}