#include "SDLMenuLayer.h"

// SDLMenuLayer::SDLMenuLayer(StateRequestFn CallbackFn) : m_CallbackFn(CallbackFn) {
//     rendererInstance = StaticSDLRenderer::getStaticInstance();
//     m_MainButtons.resize(3);

//     float x, y;
//     x = 250;
//     y = 50;
//     float w, h;
//     w = 250;
//     h = 50;

//     for(auto& each : m_MainButtons) {
//         each.SetComponentPosition(x, y);
//         each.SetComponentDimensions(w, h);
//         y += h + 20;
//     }

//     m_MainButtons.at(0).ClickCallback = [this](){
//         // SDLGameStateManager::changeGameState_PlayState();
//         m_CallbackFn(SDLGameState::PlayState);
//     };
// }

SDLMenuLayer::~SDLMenuLayer() {
    rendererInstance = nullptr;
    std::cout << "Menu Layer Destructed!\n";
}

SDLMenuLayer::SDLMenuLayer(AppEventDispatcher& dispatcher) : m_Dispatcher(dispatcher) {
    rendererInstance = StaticSDLRenderer::getStaticInstance();
    m_MainButtons.resize(3);

    float x, y;
    x = 250;
    y = 50;
    float w, h;
    w = 250;
    h = 50;

    for(auto& each : m_MainButtons) {
        each.SetComponentPosition(x, y);
        each.SetComponentDimensions(w, h);
        y += h + 20;
    }

    m_MainButtons.at(0).ClickCallback = [this](){
        m_Dispatcher.Queue({ AppEvents::RequestPlay });
    };
    // below buttons will crash the program because for now nothing is being handled on request
    m_MainButtons.at(1).ClickCallback = [this](){
        m_Dispatcher.Queue({ AppEvents::RequestSettings });
    };
    m_MainButtons.at(2).ClickCallback = [this](){
        m_Dispatcher.Queue({ AppEvents::RequestExit });
    };
}

void SDLMenuLayer::Render() {
    SDL_SetRenderDrawColor(rendererInstance, 255, 0, 0, 255);
    SDL_Color textColor = {255, 255, 255, 255};
    int idx = 0;
    for(auto& each : m_MainButtons) {
        each.Render();
        SDL_Surface* tempSurface = 
            TTF_RenderText_Blended(SDLLabel::m_SDLFont, m_TextArray[idx].c_str(), 0, textColor);

        SDL_Texture* tempTexture =
            SDL_CreateTextureFromSurface(StaticSDLRenderer::getStaticInstance(), tempSurface);

        SDL_DestroySurface(tempSurface);
        
        float textW, textH;
        SDL_GetTextureSize(tempTexture, &textW, &textH);
        
        SDL_FRect ButtonFRectData = each.getRect();
        SDL_FRect textFRect {
            .x = ButtonFRectData.x + (ButtonFRectData.w - textW) / 2.f,
            .y = ButtonFRectData.y + (ButtonFRectData.h - textH) / 2.f,
            .w = textW,
            .h = textH,
        };
        // std::cout << "\nidx: " << idx << "\nw: " << tempFRect.w << "\nh: " << tempFRect.h;
        // tempFRect.x += ctrX - textW;
        // tempFRect.y += ctrY - textH;
        // tempFRect.w = textW;
        // tempFRect.h = textH;
        // std::cout << "\nx: " << tempFRect.x << "\ny: " << tempFRect.y;
        SDL_RenderTexture(StaticSDLRenderer::getStaticInstance(), tempTexture, nullptr, &textFRect);
        SDL_DestroyTexture(tempTexture);
        idx++;
    }
}

void SDLMenuLayer::HandleEvents(SDL_Event& ev) {
    for(auto& each : m_MainButtons) {
        each.HandleInteraction(ev);
    }
}

// void SDLMenuLayer::LoadRenderer(SDL_Renderer* renderer) {
//     if(!renderer)
//         throw SDLException("SDLMenuLayer::LoadRenderer::renderer is nullptr!");
    
//     rendererPointer = renderer;
// }