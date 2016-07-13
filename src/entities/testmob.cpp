#include "testmob.h"

TestMob::TestMob()
{
    spColorRectSprite kaban = new ColorRectSprite();
    kaban->attachTo(this);
    kaban->setSize(40, 40);
    kaban->setColor(Color::Brown);
    setSize(40, 40);
    setName("KABAN");
}
