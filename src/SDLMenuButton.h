#pragma once
#include <iostream>
#include <functional>
#include "SDLComponent.h"

class SDLMenuButton : public SDLComponent {
private:
    SDL_FRect m_ButtonRect;
    bool hovered = false;
    bool pressed = false;
public:
    std::function<void()> ClickCallback;
    
    SDLMenuButton() = default;
    ~SDLMenuButton() = default;

    void HandleInteraction(SDL_Event&) override;
    void Render() override;
    void SetComponentPosition(float x, float y) override;
    void SetComponentDimensions(float w, float h) override;

    void onClick();
    SDL_FRect getRect() const { return m_ButtonRect; }
};