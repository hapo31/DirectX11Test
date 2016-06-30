#pragma once
#include <d3d11.h>
#include <string>


#include "Com_ptr.h"
#include "Defs.h"

namespace engine
{
    class DXTSprite
    {
    private:
        com_ptr<ID3D11ShaderResourceView> tex;
        com_ptr<ID3D11Resource> res;
        HRESULT last_error;
    public:
        DXTSprite(const defs::tstring& filename);

        ID3D11ShaderResourceView* getTextureResource() const { return tex; }
        ID3D11Resource* getResource() const { return res; }

        ULONG Release();

    };
}