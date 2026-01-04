#pragma once
#include "SDL3/SDL.h"
#include <functional>
#include "SDLComponent.h"
#include "SDLRenderer.h"

enum SDLCellColor {
    YELLOW  = 0,
    BLUE    = 1,
    GREEN   = 2,
    WHITE   = 3,
    PINK    = 4,
    ORANGE  = 5,
};

enum SDLCellStatus {
    HIDDEN      = 0,
    AWAITING    = 1,
    MATCHED     = 2,
};

struct SDLCell : public SDLComponent {
private:
    SDL_FRect m_Rect;
    bool pressed = false;
    bool hovered = false;
public:
    std::function<void(SDLCell*)> m_Callback;

    // void SetCallback(std::function<void()>);
    void HandleInteraction(SDL_Event&) override;
    void Render() override;
    void SetComponentPosition(float x, float y) override;
    void SetComponentDimensions(float w, float h) override;

    void onClick();
    void SetRectColor(const SDLCellColor&);
    SDLCellColor& getCellColor();
    
    SDL_FRect& GetRectData(); // lol, 
    // why are you breaking the call in PlayLayer huh? Am I getting incorrect reference or what.
    SDLCellColor m_CellColor;
    SDLCellStatus m_CellStatus = SDLCellStatus::HIDDEN;
};