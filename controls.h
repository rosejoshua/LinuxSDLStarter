
#include <SDL2/SDL.h>

class Controls
{
private:
    bool left;
    bool right;
    bool up;
    bool down;
public:
    Controls();
    ~Controls();

    bool btn0;
    bool btn1;
    bool btn2;
    bool btn3;

    // get 0-8 corresponding to 8-way joystick. This will ensure the same experience whether
    // using keyboard, d-pad, analog joystick, etc. 0 is null, 1 is north and increments clockwise
    const unsigned int getDirection();
    void update(SDL_Event* const p_event);
};
