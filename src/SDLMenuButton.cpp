#include "SDLMenuButton.h"

void SDLMenuButton::HandleInteraction(SDL_Event& buttonEvent) {
    if(buttonEvent.type == SDL_EVENT_MOUSE_MOTION) {
        float mx = buttonEvent.motion.x;
        float my = buttonEvent.motion.y;
        SDL_FPoint pt = {mx, my};
        hovered = SDL_PointInRectFloat(&pt, &m_ButtonRect);
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

void SDLMenuButton::Render() {
    SDL_Renderer* tempRend = StaticSDLRenderer::getStaticInstance();

    if(!hovered)
        SDL_SetRenderDrawColor(tempRend, 255, 0, 0, 255);
    else
        SDL_SetRenderDrawColor(tempRend, 205, 0, 0, 255);

    SDL_RenderFillRect(tempRend, &m_ButtonRect);
}

void SDLMenuButton::SetComponentPosition(float x, float y) {
    // int *w, *h;
    // SDL_GetRenderOutputSize(StaticSDLRenderer::getStaticInstance(), w, h);
    // std::cout << *w << " : " << *h << std::endl;
    m_ButtonRect = {x, y, 0, 0};
}

void SDLMenuButton::SetComponentDimensions(float w, float h) {
    m_ButtonRect.w = w;
    m_ButtonRect.h = h;
}

void SDLMenuButton::onClick() {
    if(ClickCallback)
        ClickCallback();
}