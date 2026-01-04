#pragma once
#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "SDLMenuLayer.h"
#include "SDLMenuButton.h"
#include "SDLPlayLayer.h"
#include "SDLFont.h"
#include "SDLGameState.h"
#include "SDLAppEventDispatcher.h"
#include "SDLException.hpp"

class SDLGame {
private:
    // SDLGame should only be capable of raising Events to Event Dispatcher.
    // Meaning the requirement of EventDispatch Callback

    // heap allocated elements _
    SDLWindow *m_SDLWindow;
    // SDLRenderer *m_SDLRenderer;

    // heap allocated lib elements _
    SDL_Renderer *m_SDLStaticRenderer;

    // stack allocated elements _
    SDLGameState m_SDLGameState;
    SDLMenuLayer m_SDLMenuLayer;
    SDLPlayLayer m_SDLPlayLayer;
    AppEventDispatcher m_AppEventDispatcher;
    bool gameRunning;
public:
    SDLGame(const s_WindowProps&, const s_RendererProps&);
    ~SDLGame();

    void Loop();
    void HandleEvents();
    void MainRender();
    void UpdateState();
    void HandleApplicationEvent();

    void RequestStateChange(SDLGameState newState);
};