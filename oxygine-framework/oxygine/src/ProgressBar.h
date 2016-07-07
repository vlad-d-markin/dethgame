#pragma once
#include "oxygine_include.h"
#include "Sprite.h"

namespace oxygine
{
    DECLARE_SMART(ProgressBar, spProgressBar);

    class ProgressBar: public _Sprite
    {
    public:
        enum { PROGRESS_CHANGED = sysEventID('P', 'C', 'h') };

        enum direction
        {
            dir_0,//moveable right edge
            dir_90,//moveable top edge
            dir_180,//moveable left edge
            dir_270,//moveable bottom edge
            dir_radial_cw,
            __dir_radial_ccw//not implemented!!
        };

        DECLARE_COPYCLONE_NEW(ProgressBar);

        ProgressBar();
        ~ProgressBar();

        float       getProgress() const;
        direction   getDirection() const;

        /** setProgress
        @param value range [0.0f, 1.0f]
        */
        void setProgress(float value);
        void setDirection(direction dir);

        std::string dump(const dumpOptions&) const;

        void serialize(serializedata* data);
        void deserialize(const deserializedata* data);

        typedef Property<float, float, ProgressBar, &ProgressBar::getProgress, &ProgressBar::setProgress> TweenProgress;

    private:
        void doRender(const RenderState& rs);

        RectF getDestRect() const OVERRIDE;
        virtual void _update();

        void animFrameChanged(const AnimationFrame& f);

        float _progress;
        direction _direction;
        AnimationFrame _originalFrame;
    };
}

#ifdef OX_EDITOR
#include "EditorProgressBar.h"
#else
typedef oxygine::ProgressBar BaseProgressBar;
#endif
