#include "SDLPlayLayer.h"

SDLPlayLayer::~SDLPlayLayer() {
    rendererInstance = nullptr;
    std::cout << "Play layer destructor called!\n";
}

SDLPlayLayer::SDLPlayLayer(AppEventDispatcher& dispatcher) : m_Dispatcher(dispatcher), m_Board(12) {
    rendererInstance = StaticSDLRenderer::getStaticInstance();

}

void SDLPlayLayer::Render() {
    float x = 50.f;
    float y = 50.f;
    float wh = 100.f;
    // int idx = 0;
    float startX = 50.f;
    float startY = 50.f;
    int rowCount = 3;

    for(int q = 0; q < m_Board.m_Cells.size(); q++) {
        int row = q / rowCount;
        int col = q % rowCount;

        float x = startX + col * wh;
        float y = startY + row * wh;

        m_Board.m_Cells[q].SetComponentPosition(x, y);
        m_Board.m_Cells[q].SetComponentDimensions(wh, wh);
    }

    for(auto& cells : m_Board.m_Cells) {
        cells.Render();
    }
    // m_Board.Update();
}

void SDLPlayLayer::HandleEvents(SDL_Event& ev) {
    // Inputs are broken, fix the holding down request.
    if(ev.type == SDL_EVENT_KEY_DOWN) {
        if(ev.key.key == SDLK_SPACE) {
            m_Dispatcher.Queue({ AppEvents::RequestMenu });
        }
    }
    
    for(auto& cell : m_Board.m_Cells) {
        cell.HandleInteraction(ev);
    }
}