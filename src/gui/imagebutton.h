#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <string>
#include "oxygine-framework.h"

using namespace oxygine;

class ImageButton : public Button
{
private:
    Resources * m_resources;
public:
    ImageButton(ResAnim * buttonBg);
    virtual ~ImageButton();
private:
    void onClick(Event * event);
};

typedef ::oxygine::intrusive_ptr<ImageButton> spImageButton;

#endif // IMAGEBUTTON_H
