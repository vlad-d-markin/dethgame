#ifndef DETHGAME_BUTTON_H
#define DETHGAME_BUTTON_H

#include "oxygine-framework.h"
#include "guielement.h"
#include <string>

namespace Gui {

    using namespace oxygine;

    class ButtonClickedEvent : public Event {
    public:
        enum { EVENT = eventID('x', 'A','f', 'q') };
        std::string m_action;
        ButtonClickedEvent(const std::string& action) : Event(EVENT), m_action(action) {}
    };

    DECLARE_SMART(BaseButton, spBaseButton);
    class BaseButton : public Element {
    public:
        void setAction(const std::string &action) { m_action = action; }

    protected:
        std::string m_action;
        virtual void onClicked(Event * event);
    };

}


#endif //DETHGAME_BUTTON_H
