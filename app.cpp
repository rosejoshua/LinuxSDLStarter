#include <iostream>
#include <SDL2/SDL.h>
#include <cstdio>

#include "controls.h"

//#include "SDL_ttf.h"
//#include "SDL_mixer.h"

using std::clog;
using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    unsigned int fullscreenResW = 1920;
    unsigned int fullscreenResH = 1080;
    unsigned int systemCurrentRefreshRate = 60;

    unsigned int windowedResW = 1280;
    unsigned int windowedResH = 720;
    unsigned int windowedRefreshRate = 60;

    int inUseResW = 640;
    int inUseResH = 480;

    bool fullscreen = false;

    freopen( "logs.txt", "w", stdout );
    freopen( "logs.txt", "w", stderr );

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    Controls controls;
    bool appIsRunning = true;
    Uint64 lastDrawTime = SDL_GetTicks64();


    if (SDL_Init(SDL_INIT_VIDEO ) < 0) {
        cerr << "SDL could not be initialized: " <<
            SDL_GetError();
        return 1;
    }
    else 
    {
        clog << "SDL VIDEO successfuly initialized" << endl;
    }

    // Declare display mode structure to be filled in.
    SDL_DisplayMode tempDisplayMode;
    // Get current display mode of all displays.
    for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i){
        int should_be_zero = SDL_GetCurrentDisplayMode(i, &tempDisplayMode);

        if(should_be_zero != 0)
        // In case of error...
        SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

        else
        {
        // On success, print the current display mode.
        SDL_Log("Display #%d: display mode before creating SDL window is %dx%dpx @ %dhz.", i, tempDisplayMode.w, tempDisplayMode.h, tempDisplayMode.refresh_rate);
        fullscreenResW = tempDisplayMode.w;
        fullscreenResH = tempDisplayMode.h;
        }
    }

    if (fullscreen)
    {// Create an application window with the following settings:
    window = SDL_CreateWindow(
        // window title
        "PewPew",
        // initial x position
        SDL_WINDOWPOS_UNDEFINED,
        // initial y position
        SDL_WINDOWPOS_UNDEFINED,
        // width, in pixels
        fullscreenResW,
        // height, in pixels
        fullscreenResH,
        // flags - see below
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
    );}
    else
    {// Create an application window with the following settings:
    window = SDL_CreateWindow(
        // window title
        "PewPew",
        // initial x position
        SDL_WINDOWPOS_UNDEFINED,
        // initial y position
        SDL_WINDOWPOS_UNDEFINED,
        // width, in pixels
        windowedResW,
        // height, in pixels
        windowedResH,
        // flags - see below
        SDL_WINDOW_SHOWN
    );}

    // Check that the window was successfully created
    if (window == NULL)
    {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    else
    {
        SDL_GetWindowSize(window, &inUseResW, &inUseResH);
        // On success, print the current display mode.
        SDL_Log("Current window display mode after creating SDL window is %dx%dpx.", inUseResW, inUseResH);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        // In the case that the renderer could not be made...
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Rect sdlRect;
    sdlRect.w = inUseResW/30;
    sdlRect.h = inUseResH/10;
    sdlRect.x = inUseResW/2 - sdlRect.w/2;
    sdlRect.y = inUseResH/2 - sdlRect.h/2;
    
    int numPixelsToMovePerFrame = 1;

    //main game/app loop
    while (appIsRunning)
    {
        //slowing things down a little, you can delete this if you like
        // while (SDL_GetTicks64() - lastDrawTime < numMillisToThrottle){}

        SDL_Event event;
        SDL_Event* p_event = &event;
        while (SDL_PollEvent(p_event))
        {
            // Handle each specific event
            if (event.type == SDL_QUIT)
            {
                appIsRunning = false;
            }
            else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                controls.update(p_event);
            }
        }

        //bounds checking and correction
        if (sdlRect.x < 0)
        {
            sdlRect.x = 0;
        }
        else if (sdlRect.x + sdlRect.w - 1 >= inUseResW)
        {
            sdlRect.x = inUseResW - sdlRect.w;
        }
        if (sdlRect.y < 0)
        {
            sdlRect.y = 0;
        }
        else if (sdlRect.y + sdlRect.h - 1 >= inUseResH)
        {
            sdlRect.y = inUseResH - sdlRect.h;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 105, 180, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &sdlRect);
        SDL_RenderPresent(renderer);
        
        lastDrawTime = SDL_GetTicks64();
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    std::cout << "exiting..." << std::endl;
    SDL_Quit();
    
    std::cout << "program exiting..." << std::endl;
    return 0;
}
