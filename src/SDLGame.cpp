#include "SDLGame.h"

// Without Appstate header
// SDLGame::SDLGame(const s_WindowProps& wProps, const s_RendererProps& rProps) : 
//     m_SDLGameState(SDLGameState::MenuState), 
//     gameRunning(true), 
//     m_SDLMenuLayer([this](SDLGameState s) {RequestStateChange(s);}) {
    
//     m_SDLWindow = new SDLWindow(wProps);
//     if(!m_SDLWindow)
//         throw SDLException("SDLGame::SDLGame::m_SDLWindow is nullptr!");


//     StaticSDLRenderer::GenerateStaticRenderer(m_SDLWindow->getWindow());
//     m_SDLStaticRenderer = StaticSDLRenderer::getStaticInstance();

//     if(!TTF_Init())
//         throw SDLException("SDLGame::SDLGame::TTF_Init() error!");    

//     SDLLabel::m_SDLFont = TTF_OpenFont("include/font/Roboto.ttf", 24);
//     if(SDLLabel::m_SDLFont == nullptr) {
//         throw SDLException("Font not opened!");
//     }
// }

SDLGame::SDLGame(const s_WindowProps& wProps, const s_RendererProps& rProps) : 
    m_SDLGameState(SDLGameState::MenuState), 
    gameRunning(true), 
    m_SDLMenuLayer(m_AppEventDispatcher),
    m_SDLPlayLayer(m_AppEventDispatcher) {
    
    m_SDLWindow = new SDLWindow(wProps);
    if(!m_SDLWindow)
        throw SDLException("SDLGame::SDLGame::m_SDLWindow is nullptr!");


    StaticSDLRenderer::GenerateStaticRenderer(m_SDLWindow->getWindow());
    m_SDLStaticRenderer = StaticSDLRenderer::getStaticInstance();

    if(!TTF_Init())
        throw SDLException("SDLGame::SDLGame::TTF_Init() error!");    

    SDLLabel::m_SDLFont = TTF_OpenFont("include/font/Roboto.ttf", 24);
    if(SDLLabel::m_SDLFont == nullptr) {
        throw SDLException("Font not opened!");
    }
}

// With Appstate header
// SDLGame::SDLGame(const s_WindowProps& wProps, const s_RendererProps& rProps) : 
//     gameRunning(true) {
//     m_SDLWindow = new SDLWindow(wProps);
//     if(!m_SDLWindow)
//         throw SDLException("SDLGame::SDLGame::m_SDLWindow is nullptr!");
    
//     StaticSDLRenderer::GenerateStaticRenderer(m_SDLWindow->getWindow());
//     m_SDLStaticRenderer = StaticSDLRenderer::getStaticInstance();

//     *SDLGameStateManager::gs = SDLGameStates::MenuState;

//     if(!TTF_Init())
//         throw SDLException("SDLGame::SDLGame::TTF_Init() error!");    

//     SDLLabel::m_SDLFont = TTF_OpenFont("include/font/Roboto.ttf", 24);
//     if(SDLLabel::m_SDLFont == nullptr) {
//         throw SDLException("Font not opened!");
//     }
// }

SDLGame::~SDLGame() {
    if(m_SDLWindow)
        delete m_SDLWindow;
}

void SDLGame::Loop() {
    while(gameRunning) {
        HandleEvents();
        HandleApplicationEvent();
        MainRender();
        UpdateState();
    }
}

void SDLGame::HandleEvents() {
    SDL_Event ev;
    while(SDL_PollEvent(&ev)) {
        if(ev.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
            gameRunning = false;
        if(ev.type >= SDL_EVENT_WINDOW_FIRST && ev.type <= SDL_EVENT_WINDOW_LAST) {
            m_SDLWindow->HandleEvents(ev);
        }
        switch(m_SDLGameState) {
            case SDLGameState::MenuState:
                // std::cout << "Menu State\n";
                m_SDLMenuLayer.HandleEvents(ev);
                break;
            case SDLGameState::PlayState:
                // std::cout << "Play State\n";
                m_SDLPlayLayer.HandleEvents(ev);
                break;
            default:
                std::cout << "Couldn't recognize the game state!\n";
                break;
        }
        // if(m_SDLGameState == SDLGameState::MenuState) {
        //     std::cout << "MenuState game State was entered!\n";
        //     m_SDLMenuLayer.HandleEvents(ev);
        // }

        // if(m_SDLGameState == SDLGameState::PlayState) {
        //     std::cout << "PlayState game State was entered!\n";
        //     m_SDLPlayLayer.HandleEvents(ev);
        // }
    }
}

void SDLGame::HandleApplicationEvent() {
    AppEvent event;
    while (m_AppEventDispatcher.Poll(event)) {
        switch (event.event) {
            case AppEvents::RequestPlay:
                std::cout << "PlayState Request made!\n";
                RequestStateChange(SDLGameState::PlayState);
                break;

            case AppEvents::RequestMenu:
                std::cout << "MenuState Request made!\n";
                RequestStateChange(SDLGameState::MenuState);
                break;

            default:
                break;
        }
    }
}

    // while(m_AppEventDispatcher.Poll(ev)) {
    //     switch(ev.event) {
    //         case AppEvents::RequestMenu:
    //             RequestStateChange(SDLGameState::MenuState);
    //             break;
    //         case AppEvents::RequestPlay:
    //             RequestStateChange(SDLGameState::PlayState);
    //             break;
    //         default:
    //             std::cout << "Unregistered event!\n";
    //             break; 
    //     }
    // }

void SDLGame::MainRender() {
    SDL_SetRenderDrawColor(m_SDLStaticRenderer, 20, 20, 20, 255);
    SDL_RenderClear(m_SDLStaticRenderer);
    switch (m_SDLGameState) {
    case SDLGameState::MenuState:
        // std::cout << "Rendering Menu State!\n";
        m_SDLMenuLayer.Render();    
        break;
    case SDLGameState::PlayState:
        // std::cout << "Rendering Play State!\n";
        m_SDLPlayLayer.Render();
        break;
    default:
        break;
    }
    // if(m_SDLGameState == SDLGameState::MenuState) {
    //     m_SDLMenuLayer.Render();
    // }
    
    // if(m_SDLGameState == SDLGameState::PlayState) {
    //     m_SDLPlayLayer.Render();
    // }
    SDL_RenderPresent(m_SDLStaticRenderer);
}


void SDLGame::RequestStateChange(SDLGameState newState) {
    if(m_SDLGameState == newState)
        return;
    
    m_SDLGameState = newState;
}

void SDLGame::UpdateState() {
    // do nothing for now
}


