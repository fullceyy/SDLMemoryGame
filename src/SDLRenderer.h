#pragma once
#include "SDL3/SDL.h"

typedef struct {
    SDL_Renderer* renderer;
    int vSync;
} s_RendererProps;

class StaticSDLRenderer {
public:
    static SDL_Renderer* getStaticInstance();
    static void GenerateStaticRenderer(SDL_Window*);  
private:  
    static SDL_Renderer* renderer;
};

class SDLRenderer {
public:
    SDLRenderer(const s_RendererProps&);
    ~SDLRenderer();

    void CreateRenderer(SDL_Window*);
    static SDL_Renderer* CreateStaticRenderer(SDL_Window*);
    
    SDL_Renderer* getRenderer();
private:
    s_RendererProps m_Props;
};