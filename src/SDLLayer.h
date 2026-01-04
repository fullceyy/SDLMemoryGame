#pragma once
#include "SDL3/SDL.h"
#include "SDLException.hpp"

class SDLLayer {
public:
    SDLLayer() = default;
    ~SDLLayer() = default;

    virtual void Render() = 0;
    virtual void HandleEvents(SDL_Event&) = 0;
};

