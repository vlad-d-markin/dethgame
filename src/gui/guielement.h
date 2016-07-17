#ifndef DETHGAME_GUIELEMENT_H
#define DETHGAME_GUIELEMENT_H

#include "oxygine-framework.h"

namespace Gui{

using namespace oxygine;

DECLARE_SMART(Element, spElement);
class Element : public Actor {
private:
    spColorRectSprite m_boundaries;

public:
    Element();
    virtual  ~Element();

    void showBoundaries(bool visible);

    virtual void updateStateOvered();
    virtual void updateStatePressed();
//

protected:
    virtual void onOvered();
    virtual void onLeft();
    virtual void onPressed();
    virtual void onReleased();
    virtual void onClicked(Event * e);
    virtual void onSizeChanged(const Vector2 &size);

    virtual void sizeChanged (const Vector2 &size);
};
}

#endif //DETHGAME_GUIELEMENT_H
