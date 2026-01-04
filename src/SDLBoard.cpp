#include "SDLBoard.h"

SDLBoard::SDLBoard(int size) {
    if(size < 12)
        throw SDLException("SDLBoard::SDLBoard passed size is less than allowed(12)!");

    m_Cells.resize(size);

    for(auto& it : m_Cells) {
        it.m_Callback = [this](SDLCell* cell) {
            OnClick(cell);
        };
    }

    RandomizeCells();
}

void SDLBoard::RandomizeCells() {
    int pairs = m_Cells.size() / 2;
    
    std::vector<SDLCellColor> colors;
    colors.reserve(m_Cells.size());
    
    for(unsigned int q = 0; q < pairs; q++) {
        colors.push_back(static_cast<SDLCellColor>(q));
        colors.push_back(static_cast<SDLCellColor>(q));
    }

    std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    std::shuffle(colors.begin(), colors.end(), rng);

    for(size_t q = 0; q < m_Cells.size(); q++) {
        m_Cells[q].m_CellColor = colors[q];
    }
}

// void SDLBoard::OnClick(SDLCell* clickedCell) {
//     if (m_Lock || clickedCell->m_CellStatus != SDLCellStatus::AWAITING)
//         return;

//     if (!firstSelection) {
//         firstSelection = clickedCell;
//         return;
//     }

//     if (!secondSelection && clickedCell != firstSelection) {
//         secondSelection = clickedCell;

//         if (firstSelection->m_CellColor == secondSelection->m_CellColor) {
//             firstSelection->m_CellStatus = SDLCellStatus::MATCHED;
//             secondSelection->m_CellStatus = SDLCellStatus::MATCHED;
//             firstSelection = nullptr;
//             secondSelection = nullptr;
//         } else {
//             // keep cells visible for a short time
//             firstSelection->m_CellStatus = clickedCell->m_CellStatus; // still shows color
//             secondSelection->m_CellStatus = clickedCell->m_CellStatus;
//             m_MismatchTime = SDL_GetTicks();
//             m_Lock = true;
//         }
//     }
// }

// void SDLBoard::Update() {
//     if (m_Lock && firstSelection && secondSelection) {
//         if (SDL_GetTicks() - m_MismatchTime > 1000) { // 1 second
//             firstSelection->m_CellStatus = SDLCellStatus::HIDDEN;
//             secondSelection->m_CellStatus = SDLCellStatus::HIDDEN;
//             firstSelection = nullptr;
//             secondSelection = nullptr;
//             m_Lock = false;
//         }
//     }
// }

void SDLBoard::OnClick(SDLCell* clickedCell) {
    if (clickedCell->m_CellStatus != SDLCellStatus::AWAITING)
            return;

        if (firstSelection == nullptr) {
            firstSelection = clickedCell;
            return;
        }

        if (secondSelection == nullptr && clickedCell != firstSelection) {
            secondSelection = clickedCell;
            
            if (!firstSelection || !secondSelection)
                return;

            if (firstSelection->m_CellColor == secondSelection->m_CellColor) {
                firstSelection->m_CellStatus = SDLCellStatus::MATCHED;
                secondSelection->m_CellStatus = SDLCellStatus::MATCHED;
            } else {
                firstSelection->m_CellStatus = SDLCellStatus::HIDDEN;
                secondSelection->m_CellStatus = SDLCellStatus::HIDDEN;
            }
        firstSelection = nullptr;
        secondSelection = nullptr;
    }
}