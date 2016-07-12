#include "button.h"

void Gui::BaseButton::onClicked(Event *event)
{
    ButtonClickedEvent btn_clicked_ev(m_action);
    dispatchEvent(&btn_clicked_ev);
}