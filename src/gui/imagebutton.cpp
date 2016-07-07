#include "imagebutton.h"
//#include <string>

ImageButton::ImageButton(ResAnim *buttonBg)
{
    setSize(buttonBg->getSize());
    setResAnim(buttonBg);
    addEventListener(TouchEvent::CLICK,CLOSURE(this, &ImageButton::onClick));
}

ImageButton::~ImageButton()
{

}

void ImageButton::onClick(Event* event)
{
    oxygine::log::messageln("clicked %d",this->getObjectID());
//    oxygine::log::messageln(std::to_string(this->getObjectID()).c_str());
}
