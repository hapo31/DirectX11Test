#include "DXTFont.h"
#include "engine.h"

engine::DXTFont::DXTFont()
{
    createFont(L"italic.spritefont");
}

engine::DXTFont::DXTFont(const std::wstring& fontname)
{
    createFont(fontname);
}

HRESULT engine::DXTFont::createFont(const std::wstring& fontname)
{
    try
    {
        auto& d3d11 = D3D11Wrapper::get_instance();
        auto& device = d3d11.getDevice();
        batch = d3d11.getSpriteBatch();
        
        ptr = std::make_unique<DirectX::SpriteFont>(device, fontname.c_str());
    }
    catch (std::exception e)
    {
        throw;
    }
    if (ptr == nullptr) return E_FAIL;
    else return S_OK;
}

engine::DXTFont::DXTFont(DXTFont&& rhs)
{
    ptr = std::move(rhs.ptr);

}

