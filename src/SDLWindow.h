#pragma once
#include <functional>
#include "SDL3/SDL.h"
#include "SDLAppEventDispatcher.h"

typedef struct {
    SDL_Window* window;
    int width;
    int height;
    const char* title;
    bool fullscreen;
} s_WindowProps;

class SDLWindow {
public:
    SDLWindow(const s_WindowProps&);
    ~SDLWindow();

    void HandleEvents(SDL_Event&);
    SDL_Window* getWindow() const;
private:
    s_WindowProps m_Props;
};