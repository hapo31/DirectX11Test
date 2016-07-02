#include "DXTFont.h"

engine::DXTFont::DXTFont()
{
    createFont(L"Meiryo UI");
}

engine::DXTFont::DXTFont(const std::wstring & fontname)
{
    createFont(fontname);
}

HRESULT engine::DXTFont::createFont(const std::wstring& fontname)
{
    try
    {
        auto device = D3D11Wrapper::get_instance().get_Device();
        ptr = std::make_unique<DirectX::SpriteFont>(device, fontname.c_str());
    }
    catch (...){}
    if (ptr == nullptr) return E_FAIL;
    else return S_OK;
}

engine::DXTFont::DXTFont(DXTFont&& rhs)
{
    ptr = std::move(rhs.ptr);

}