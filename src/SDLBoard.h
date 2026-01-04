#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "SDLCell.h"
#include "SDLException.hpp"

struct SDLBoard {
    std::vector<SDLCell> m_Cells;
    // bool m_Lock = false;
    // Uint32 m_MismatchTime = 0;

    SDLCell* firstSelection = nullptr;
    SDLCell* secondSelection = nullptr;

    SDLBoard(int);
    void RandomizeCells();
    void OnClick(SDLCell*);
    // void Update();
};