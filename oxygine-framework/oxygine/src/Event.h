#pragma once
#include "oxygine_include.h"
#include "closure/closure.h"
#include "Input.h"
#include "EventDispatcher.h"
#undef OUT

struct SDL_KeyboardEvent;

namespace oxygine
{
    typedef int eventType;
    DECLARE_SMART(EventDispatcher, spEventDispatcher);

    class Event
    {
    public:
        enum { COMPLETE = sysEventID('C', 'M', 'P') };

        enum Phase
        {
            phase_capturing = 1,
            phase_target,
            phase_bubbling
        };

        eventType type;
        Phase phase;
        bool bubbles;
        bool stopsImmediatePropagation;
        bool stopsPropagation;

        void* userData;
        spObject userDataObject;
        int listenerID;

        spEventDispatcher target; //The event target
        spEventDispatcher currentTarget;// The object that is actively processing the Event object with an event listener.

        Event(eventType Type, bool Bubbles = false) : listenerID(0), userData(0), type(Type), phase(phase_target), bubbles(Bubbles), stopsImmediatePropagation(false), stopsPropagation(false) {}
        virtual ~Event() {}

        void stopPropagation() { stopsPropagation = true; }
        void stopImmediatePropagation() { stopsPropagation = stopsImmediatePropagation = true; }

        /**
        removes self from EventDispatcher, usage example
        actor->addEventListener(...buttonClicked...);
        void buttonClicked(Event* ev)
        {
            ev->removeListener();
        }
        */
        void removeListener() { currentTarget->removeEventListener(listenerID); }
    };
}
