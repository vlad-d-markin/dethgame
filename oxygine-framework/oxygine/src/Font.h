#pragma once
#include "oxygine_include.h"
#include "core/Object.h"
#include "math/Rect.h"
#ifdef __S3E__
#include <set>
#else
#include <unordered_set>
#endif
namespace oxygine
{
    DECLARE_SMART(NativeTexture, spNativeTexture);

    struct glyph
    {
        RectF src;

        int ch;

        short sw;
        short sh;

        short offset_x;
        short offset_y;

        short advance_x;
        short advance_y;

        spNativeTexture texture;

        bool operator == (const glyph& r) const {return ch == r.ch;}
        bool operator < (const glyph& r) const { return ch < r.ch; }
    };

    struct GlyphHasher
    {
        std::size_t operator()(const glyph& k) const
        {
            return std::hash<int>()(k.ch);
        }
    };

    class Font: public ObjectBase
    {
    public:
        Font();
        ~Font();

        void init(const char* name, int size, int baselineDistance, int lineHeight, bool sdf = false);

        void addGlyph(const glyph& g);
        void sortGlyphs() {}

        void setScale(float scale) { _scale = scale; }

        const glyph*    getGlyph(int code) const;
        int             getBaselineDistance() const;
        int             getSize() const;
        float           getScale() const;
        int             getLineHeight() const;
        bool            isSDF() const;

    protected:
        const glyph* findGlyph(int code) const;

        virtual bool loadGlyph(int code, glyph&) { return false; }

#ifdef __S3E__
        typedef std::set<glyph> glyphs;
#else
        typedef std::unordered_set<glyph, GlyphHasher> glyphs;
#endif
        glyphs _glyphs;

        float _scale;
        bool _sdf;

        int _size;
        int _baselineDistance;
        int _lineHeight;
    };
}