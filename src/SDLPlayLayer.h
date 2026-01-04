#pragma once
#include <array>
#include "SDL3/SDL_events.h"
#include "SDLLayer.h"
#include "SDLRenderer.h"
#include "SDLAppEventDispatcher.h"
#include "SDLBoard.h"

class SDLPlayLayer : public SDLLayer {
public:
    explicit SDLPlayLayer(AppEventDispatcher&);
    ~SDLPlayLayer();
    void Render() override;
    void HandleEvents(SDL_Event&) override;
private:
    SDL_Renderer* rendererInstance;
    AppEventDispatcher& m_Dispatcher;

    SDLBoard m_Board;
};