#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "button.h"
#include "oxygine-framework.h"

using namespace oxygine;

namespace Gui {

    DECLARE_SMART(TextButton, spTextButton);
    class TextButton : public BaseButton {
    private:
        spTextField m_title;
        spColorRectSprite m_background;

    public:
        TextButton(const std::string &text = "Click me");
        virtual ~TextButton();

        void setText(const std::string& text);


    protected:
        virtual void onOvered();
        virtual void onLeft();
        virtual void onPressed();
        virtual void onReleased();

        virtual void onSizeChanged(const Vector2 &size);

    };
}
#endif
