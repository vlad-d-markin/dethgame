#pragma once
#include "core/Object.h"
#include <functional>
#include "Scene.h"

namespace oxygine
{
    class Event;

    namespace flow
    {
        DECLARE_SMART(Scene, spScene);
        DECLARE_SMART(Transition, spTransition);
        class Flow;

        class SceneEvent;
        inline void doNothingEventCallback(SceneEvent*) {}
        typedef std::function< void(SceneEvent*) > resultCallback;

        /**initializing oxygine-flow subsystem*/
        void init();

        /**releasing oxygine-flow subsystem*/
        void free();

        /**update oxygine-flow. Call it each frame*/
        void update();

        /**shows next scene and call callback when it was finished*/
        void show(spScene, const resultCallback& cb = doNothingEventCallback, Flow* = 0);




        class Flow
        {
        public:
            static Flow instance;

            Flow();

            void init();
            void free();

            void show(spScene scene, const resultCallback& cb);
            void update();

            void phaseBegin(spScene current, spScene next, bool back);
            void phaseEnd();

            void checkDone();
            void checkShow();

            void blockedTouch(Event*);

            std::vector<spScene> scenes;
            std::vector<spScene> scenes2show;

            bool _transition;
            bool _back;

            spTransition _trans;
            spScene _current;
            spScene _next;
        };
    }
}