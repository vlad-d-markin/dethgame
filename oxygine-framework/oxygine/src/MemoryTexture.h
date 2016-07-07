#pragma once
#include "oxygine_include.h"
#include "core/Texture.h"
#include "core/file.h"

namespace oxygine
{
    enum ImageType
    {
        IT_UNKNOWN,
        IT_PNG,
        IT_PKM,
        IT_PVR2,
        IT_PVR,
        IT_TGA,
        IT_JPEG
    };

    bool getImageInfo(const void* data, size_t size, const char* name, ImageType& type, int& width, int& height);

    DECLARE_SMART(MemoryTexture, spMemoryTexture);

    class MemoryTexture : public Texture
    {
    public:
        MemoryTexture();
        ~MemoryTexture();

        bool init(file::buffer& bf, bool premultiplied = false, TextureFormat format = TF_UNDEFINED);
        void init(const ImageData& src);
        void init(int w, int h, TextureFormat Format);

        void cleanup();
        void convert(MemoryTexture& dest, TextureFormat format);
        //void convert2pot(MemoryTexture &dest);

        void fill_zero();

        unsigned int    getSizeVRAM() const {return (unsigned int)_buffer.size();}
        int             getWidth() const;
        int             getHeight() const;
        const Point&    getSize() const;
        TextureFormat   getFormat() const;

        ImageData   lock(lock_flags f = 0, const Rect* pRect = 0);
        ImageData   lock(const Rect* pRect);
        ImageData   lock(const Rect& pRect);
        void        unlock();

        void        updateRegion(int x, int y, const ImageData& data);
        void        apply(const Rect*);

        void        swap(MemoryTexture& r);

    private:
        ImageData _image;
        size_t _offset;//buffer offset
        std::vector<unsigned char> _buffer;
    };

    typedef bool (*cbLoadImageFromBuffer)(MemoryTexture& mt, void* data, int nSize, bool premultiplied, TextureFormat format);
    void setJpegLoader(cbLoadImageFromBuffer);
    void setPngLoader(cbLoadImageFromBuffer);
}