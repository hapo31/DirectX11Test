#pragma once
#include "Com_ptr.h"
#include "engine.h"

#include <string>
#include <memory>

#include <SpriteFont.h>

namespace engine
{
    class DXTFont
    {
    private:
        std::unique_ptr<DirectX::SpriteFont> ptr = nullptr;
        std::shared_ptr<DirectX::SpriteBatch> sprite;
    public:
        DXTFont();
        DXTFont(const std::wstring& fontname);
        DXTFont(DXTFont&& rhs);

        HRESULT createFont(const std::wstring& fontname);

        auto operator->() const { return ptr.get(); }
    };
}