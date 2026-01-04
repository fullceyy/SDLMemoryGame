#include "SDLCell.h"

void SDLCell::SetComponentPosition(float x, float y) {
    m_Rect.x = x;
    m_Rect.y = y;
}

void SDLCell::SetComponentDimensions(float u, float u2) {
    m_Rect.w = u;
    m_Rect.h = u2;
}

SDL_FRect& SDLCell::GetRectData() {
    return m_Rect;
}

void SDLCell::Render() {
    SDL_Renderer* temp_rend = StaticSDLRenderer::getStaticInstance();

    if(m_CellStatus == SDLCellStatus::HIDDEN) {
        if(!hovered) {
            SDL_SetRenderDrawColor(temp_rend, 205, 0, 20, 255);
        } else {
            SDL_SetRenderDrawColor(temp_rend, 255, 0, 0, 255);
        }
    } else {
        SetRectColor(m_CellColor);
    }

    SDL_RenderRect(temp_rend, &m_Rect);
    SDL_RenderFillRect(temp_rend, &m_Rect);
}

void SDLCell::HandleInteraction(SDL_Event& buttonEvent) {
        if(buttonEvent.type == SDL_EVENT_MOUSE_MOTION) {
        float mx = buttonEvent.motion.x;
        float my = buttonEvent.motion.y;
        SDL_FPoint pt = {mx, my};
        hovered = SDL_PointInRectFloat(&pt, &m_Rect);
    }
    if(buttonEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN && hovered) {
        pressed = true;

    }
    if(buttonEvent.type == SDL_EVENT_MOUSE_BUTTON_UP && pressed && hovered) {
        pressed = false;
        onClick();
        // std::cout << "Button Pressed!" << std::endl;
    }
}

void SDLCell::SetRectColor(const SDLCellColor& color) {
    SDL_Renderer* temp_rend = StaticSDLRenderer::getStaticInstance();

    switch(color) {
        case SDLCellColor::YELLOW:
            SDL_SetRenderDrawColor(temp_rend, 255, 255, 0, 255);
            break;
        case SDLCellColor::BLUE:
            SDL_SetRenderDrawColor(temp_rend, 0, 0, 255, 255);
            break;
        case SDLCellColor::GREEN:
            SDL_SetRenderDrawColor(temp_rend, 0, 255, 0, 255);
            break;
        case SDLCellColor::WHITE:
            SDL_SetRenderDrawColor(temp_rend, 255, 255, 255, 255);
            break;
        case SDLCellColor::PINK:
            SDL_SetRenderDrawColor(temp_rend, 255, 192, 203, 255);
            break;
        case SDLCellColor::ORANGE:
            SDL_SetRenderDrawColor(temp_rend, 255, 165, 0, 255);
            break;
        default:
            SDL_Log("SDLCell::SetRectColor::Unrecognized color!");
    }
}

// void SDLCell::SetCallback(std::function<void()> callback) {
//     m_Callback = callback;
// }

void SDLCell::onClick() {
    if(m_CellStatus != SDLCellStatus::HIDDEN) {
        return;
    }

    m_CellStatus = SDLCellStatus::AWAITING;
    
    if(m_Callback)
        m_Callback(this);
}

SDLCellColor& SDLCell::getCellColor() {
    return m_CellColor;
}

    // SDL_SetRenderDrawColor(temp_rend, 255, 255, 244, 255);
    // SDL_RenderRect(temp_rend, &m_Rect);
    // if(!hovered)
    //     SDL_SetRenderDrawColor(temp_rend, 205, 0, 20, 255);
    // else
    //     SDL_SetRenderDrawColor(temp_rend, 255, 0, 0, 255);