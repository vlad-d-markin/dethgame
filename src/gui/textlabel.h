//
// Created by lonelyowl on 10.07.16.
//
#ifndef DETHGAME_TEXTLABEL_H
#define DETHGAME_TEXTLABEL_H

#include "guielement.h"
#include "oxygine-framework.h"

namespace Gui {
    using namespace oxygine;
    DECLARE_SMART(TextLabel, spTextLabel);
    class TextLabel : public Element {
    private:
        spTextField m_label;
    public:
        TextLabel();
        virtual ~TextLabel();
        TextStyle getTextStyle();
        void setTextStyle(TextStyle style);
        void setText(const std::string& text);
		const std::string getText();
    };
}


#endif //DETHGAME_TEXTLABEL_H
