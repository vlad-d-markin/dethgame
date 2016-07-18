//
// Created by lonelyowl on 10.07.16.
//
#ifndef DETHGAME_BAR_H
#define DETHGAME_BAR_H

#include "oxygine-framework.h"
#include "../gui/guielement.h"

namespace Gui {
    DECLARE_SMART(Bar, spBar);
    class Bar : public Element {
    private:
        double m_value;
        double m_maxvalue;

        spTextField m_title;
		spSprite m_background;
        spColorRectSprite m_bar;
		Resources * m_resources;
    public:
        Bar(double maxvalue = 100);
        virtual ~Bar();
        void setValue(double value);
        double getValue();
        void setMaxValue(double maxvalue);
        double getMaxValue();
		void setTextStyle(TextStyle style);
		TextStyle getTextStyle();
		void setTextPosition(Vector2 pos);
		Vector2 getTextPosition();
		void removeBackground();
    protected:
        virtual void onSizeChanged(const Vector2 &size);
        virtual void updateText();
        void updateSizes(const Vector2 &basesize);
    };
}

#endif //DETHGAME_BAR_H
