#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "oxygine-framework.h"


using namespace oxygine;

class TextButton : public Button
{
private:
    Resources * m_resources;

public:
    TextButton(Resources * resManager, const std::string& text = "Click me");
    virtual ~TextButton();

private:
    void onCkick();
    void onHover();

};

typedef ::oxygine::intrusive_ptr<TextButton> spTextButton;

#endif
