#pragma once
#include "SDL3/SDL_events.h"
#include "SDL3_ttf/SDL_ttf.h"
#include "SDLFont.h"
#include "SDLRenderer.h"

class SDLComponent {
public:
    virtual void HandleInteraction(SDL_Event&) = 0;
    virtual void Render() = 0;
    virtual void SetComponentPosition(float x, float y) = 0;
    virtual void SetComponentDimensions(float w, float h) = 0;
};