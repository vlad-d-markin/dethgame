#pragma once
#include "oxygine_include.h"
#include "Sprite.h"

namespace oxygine
{
    class ResAnim;

    DECLARE_SMART(Polygon, spPolygon);
    class Polygon : public _Sprite
    {
    public:
        DECLARE_COPYCLONE_NEW(Polygon);

        Polygon();
        ~Polygon();

        /**
        if *own* is true Polygon will delete[] data array;
        */
        void setVertices(const void* data, int size, int bformat, bool own);

        void serialize(serializedata* data);
        void deserialize(const deserializedata* data);

        std::string dump(const dumpOptions&) const;

    protected:
        void doRender(const RenderState& rs);

        const VertexDeclaration* _vdecl;
        bool _own;
        const unsigned char* _verticesData;
        int _verticesSize;
    };
}

#ifdef OX_EDITOR
#include "EditorPolygon.h"
#else
namespace oxygine
{
    typedef Polygon _Polygon;
}
#endif
