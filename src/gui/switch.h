//
// Created by lonelyowl on 10.07.16.
//

#ifndef DETHGAME_SWITCH_H
#define DETHGAME_SWITCH_H

#include "gui.h"
#include "oxygine-framework.h"

namespace Gui {

    class SwitchStateChangedEvent : public ::oxygine::Event {
    public:
        enum { EVENT = eventID('s', 'S', 'c', 'D') };
        bool state;
        SwitchStateChangedEvent(bool s) : Event(EVENT), state(s) {}
    };


    DECLARE_SMART(Switch, spSwitch);
    class Switch : public BaseButton {
    protected:
        bool m_state;
        ::oxygine::spColorRectSprite m_background;
        ::oxygine::spColorRectSprite m_indicator;

    public:
        Switch(bool state = false);

        void toggle();

    protected:
        void updateIndicator();

        virtual void onClicked(Event * event);
        virtual void onOvered();
        virtual void onLeft();

    };
}


#endif //DETHGAME_SWITCH_H
