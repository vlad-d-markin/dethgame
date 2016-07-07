#pragma once
#include <string>
#include "core/ImageData.h"

namespace oxygine
{
    namespace file
    {
        std::string getSupportFolder();
    }

    class MemoryTexture;

    bool nsImageLoad(MemoryTexture& mt, void* pData, int nDatalen, bool premultiplied, TextureFormat format);

    void iosGetMemoryUsage(size_t& a);
}