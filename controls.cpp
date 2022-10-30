#include "controls.h"

Controls::Controls()
{
    left = false;
    right = false;
    up = false;
    down = false;
    btn0 = false;
    btn1 = false;
    btn2 = false;
    btn3 = false;
}
Controls::~Controls(){}

const unsigned int Controls::getDirection()
{
    if (up && right)
        return 2;
    else if (right && down)
        return 4;
    else if (down && left)
        return 6;
    else if (left && up)
        return 8;
    else if (up && !down)
        return 1;
    else if (right && !left)
        return 3;
    else if (down && !up)
        return 5;
    else if (left && !right)
        return 7;
    else return 0;
}

void Controls::update(SDL_Event* const p_event)
{
    if (p_event->type == SDL_KEYDOWN)
    {

    }
}