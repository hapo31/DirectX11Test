#pragma once
#include <SpriteBatch.h>
#include <memory>

#include "Singleton.h"
#include "Com_ptr.h"

namespace engine
{
    class SpriteBatchScope
    {
        friend class SpriteBatchManager;
    private:
        SpriteBatchScope(std::shared_ptr<DirectX::SpriteBatch> batcher)
        {
            this->batcher = batcher;
            this->batcher->Begin();
        }
        std::shared_ptr<DirectX::SpriteBatch> batcher;
    public:
        ~SpriteBatchScope()
        {
            batcher->End();
        }
        auto operator->() const { return batcher; }
    };

    class SpriteBatchManager : public Singleton<SpriteBatchManager>
    {
    private:
        std::shared_ptr<DirectX::SpriteBatch> sprites;
    public:
        void createSpriteBatch(com_ptr<ID3D11DeviceContext> context)
        {
            sprites = std::make_shared<DirectX::SpriteBatch>(context);
        }

        auto scopedBatcher() { return SpriteBatchScope(sprites); }
    };

}