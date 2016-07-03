#pragma once
#include "Com_ptr.h"

#include <string>
#include <memory>

#include <SpriteFont.h>

namespace engine
{
    class DXTFont
    {
    private:
        std::unique_ptr<DirectX::SpriteFont> ptr = nullptr;
        std::weak_ptr<DirectX::SpriteBatch> batch;
    public:
        DXTFont();
        DXTFont(const std::wstring& fontname);
        DXTFont(DXTFont&& rhs);

        HRESULT createFont(const std::wstring& fontname);
        void drawString(const std::wstring& text, float x, float y,  DirectX::FXMVECTOR color)
        {
            ptr->DrawString(batch.lock().get(), text.c_str(), DirectX::XMFLOAT2(x, y), color);
        }
        auto operator->() const { return ptr.get(); }
    };
}