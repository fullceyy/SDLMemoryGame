// #include "SDLEngine.hpp"
#include "SDLGame.h"
#include <memory>

int main(int argc, char* argv[]) {
    s_WindowProps windowSettings = {
        .window = nullptr,
        .width = 800,
        .height = 600,
        .title = "Chronos",
        .fullscreen = false,
    };

    s_RendererProps rendererSettings = {
        .renderer = nullptr,
        .vSync = 1
    };

    std::unique_ptr<SDLGame> game = std::make_unique<SDLGame>(windowSettings, rendererSettings);

    game->Loop();
    
    SDL_Quit();
    return 0;
}


// int main(int argc, char* argv[]) {
//     SDLEngine* engine = new SDLEngine();
//     SDLFPS fps;
//     // SDLSprite* sprite = 
//     //     new SDLSprite("include/Image/Vikings_walkabout_074.bmp");
//     // sprite->LoadTexture(engine->getRenderer());

//     bool running = true;
//     SDL_Event event;
//     uint64_t lastTime = 0;
//     while (running) {
//         fps.currentTick = SDL_GetTicksNS();
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
//                 running = false;
//             }
//             switch (event.type) {
//                 case SDL_EVENT_KEY_DOWN: {
//                     SDL_Scancode sc = event.key.scancode;
//                     if (sc == SDL_SCANCODE_UP) {
//                         std::cout << "UP pressed\n";
//                         engine->getOLayer().Render();
//                         // engine->getLayer<OverlayLayer>()->Render(engine->getRenderer());
//                     }
//                     if (sc == SDL_SCANCODE_DOWN) {
//                         std::cout << "DOWN pressed\n";
//                         engine->getMLayer().Render();
//                         // engine->getLayer<MenuLayer>()->Render(engine->getRenderer());
//                     }
//                     if (sc == SDL_SCANCODE_SPACE) {
//                         std::cout << "SPACE pressed\n";
//                     }

//                     break;
//                 }
//             }
//         }
//                 // SDL_RenderClear(engine->getRenderer());
//                 // sprite->Render(engine->getRenderer());
//                 // SDL_RenderPresent(engine->getRenderer());
//                 // per second report                
//                 if(fps.currentTick > lastTime + 1000) {
//                     std::cout << "Reporting.\n";  
//                 }

//                 // std::cout << avg << std::endl;                
//     }
//     // Cleanups
//     SDL_DestroyWindow(engine->getWindow());
//     // delete sprite;
//     delete engine;
//     SDL_Quit();
//     return 0;
// }
