//
// Created by lonelyowl on 10.07.16.
//

#ifndef DETHGAME_PANEL_H
#define DETHGAME_PANEL_H

#include "guielement.h"

namespace Gui {

    DECLARE_SMART(Panel, spPanel);
    class Panel : public Element {
    public:
        Panel();
        virtual ~Panel();

        void addElement(spElement element);
        void removeElement(spElement element);
    };
}


#endif //DETHGAME_PANEL_H
