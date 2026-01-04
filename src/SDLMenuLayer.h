#pragma once
#include "SDL3/SDL_events.h"
#include "SDLLayer.h"
#include "SDLMenuButton.h"
#include "SDLRenderer.h"
#include "SDLGameState.h"
#include "SDLAppEventDispatcher.h"
#include <array>
#include <vector>

class SDLMenuLayer : public SDLLayer {
public:
    // Unreadable;
    // The issue that I've been running is that the Layers have no way of requesting stateChange 
    // from non static non global SDLGame class. Meaning that I have to perform these obscure std::function callbacks
    // I think the better way of handling this will be an event dispatcher. That will perform direct requests of state
    // changes to SDLGame without Layers ever doing any callbacks.
    // using StateRequestFn = std::function<void(SDLGameState)>;

    // explicit SDLMenuLayer(StateRequestFn);
    explicit SDLMenuLayer(AppEventDispatcher& dispatcher);
    ~SDLMenuLayer();
    void Render() override;
    void HandleEvents(SDL_Event&) override;
private:
    // StateRequestFn m_CallbackFn;
    SDL_Renderer* rendererInstance;
    AppEventDispatcher& m_Dispatcher;

    std::vector<SDLMenuButton> m_MainButtons;
    std::vector<SDLMenuButton> m_SubButtons;

    std::array<std::string, 6> m_TextArray {
        "Play",
        "Settings",
        "Exit",
        "Video",
        "Input",
        "Audio"
    };
};