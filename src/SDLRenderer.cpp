#include "SDLRenderer.h"
#include "SDLException.hpp"

SDLRenderer::~SDLRenderer() {

}

SDLRenderer::SDLRenderer(const s_RendererProps& props) : m_Props(props) 
{    
}

void SDLRenderer::CreateRenderer(SDL_Window* windowPointer) {
    if(!windowPointer)
        throw SDLException("SDLRenderer::CreateRenderer invalid windowPointer!");

    if(!m_Props.renderer)
        m_Props.renderer = SDL_CreateRenderer(windowPointer, NULL);
}

SDL_Renderer* SDLRenderer::CreateStaticRenderer(SDL_Window* windowPointer) {
    return SDL_CreateRenderer(windowPointer, NULL);
}

SDL_Renderer* SDLRenderer::getRenderer() {
    if(m_Props.renderer)
        return m_Props.renderer;
    else
        throw SDLException("SDLRenderer::getRenderer invalid renderer!");
}

SDL_Renderer* StaticSDLRenderer::renderer = nullptr;

void StaticSDLRenderer::GenerateStaticRenderer(SDL_Window* window) {
    StaticSDLRenderer::renderer = SDL_CreateRenderer(window, NULL);
    
    SDL_SetRenderVSync(StaticSDLRenderer::renderer, 1);

    if(!StaticSDLRenderer::renderer) 
        throw SDLException("StaticSDLRenderer::GenerateStaticRenderer::unable to generate renderer!"); 
}

SDL_Renderer* StaticSDLRenderer::getStaticInstance() {    
    return StaticSDLRenderer::renderer;
}