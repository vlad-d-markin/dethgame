#include "testmob.h"

TestMob::TestMob()
{
    m_kaban = new ColorRectSprite();
    m_kaban->attachTo(this);
    m_kaban->setSize(40, 40);
    m_kaban->setColor(Color::Brown);
    setSize(40, 40);
    setName("KABAN");

    m_health = 100;
}


void TestMob::doUpdate(const UpdateState &us) {
    Mob::doUpdate(us);

    if(m_state == DEAD)
    {
        m_kaban->setColor(Color::RosyBrown);
    }
}