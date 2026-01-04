#include "SDLWindow.h"
#include "SDLException.hpp"

SDLWindow::~SDLWindow() {
    SDL_DestroyWindow(m_Props.window);
}

SDLWindow::SDLWindow(const s_WindowProps& props) : m_Props(props) {
    m_Props.window = SDL_CreateWindow(
        m_Props.title,
        m_Props.width,
        m_Props.height,
        0
    );

    if(!m_Props.window)
        throw SDLException("SDLWindow::Window not initialized!");    
}

SDL_Window* SDLWindow::getWindow() const { 
    if(m_Props.window)
        return m_Props.window;
    else
        throw SDLException("SDLWindow::getWindow invalid getter!");
}

void SDLWindow::HandleEvents(SDL_Event& ev) {
    switch(ev.type) {
        case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
            m_Props.fullscreen = true;
            SDL_SetWindowFullscreen(m_Props.window, m_Props.fullscreen);
            break;
        case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
            m_Props.fullscreen = false;
            SDL_SetWindowFullscreen(m_Props.window, m_Props.fullscreen);
            break;
        case SDL_EVENT_WINDOW_MOUSE_ENTER:
            SDL_SetWindowTitle(m_Props.window, m_Props.title);
            break;
        case SDL_EVENT_WINDOW_MOUSE_LEAVE:
            SDL_SetWindowTitle(m_Props.window, "Mousey<3");
            break;

        default:
            break; 
    }
}