#include "basescreen.h"
#include "../dethgame.h"


using namespace oxygine;


BaseScreen::BaseScreen()
{
    setName("Base screen");
    setSize(DethGame::instance()->getMainStage()->getSize());
}


void BaseScreen::show()
{

}
