#pragma once

#include <vector>
#include <optional>
#include <raylib.h>

#include "../Units/UnitFactory.hpp"
#include "GuiTools.hpp"

// TODO remake specially for bases
class NewUnitSelectionScreen {
public:
    NewUnitSelectionScreen();

    void draw() const;

    // TODO: Returns true if the state was modified.
    void handleEvents();

    bool needToClose() const;

    // Returns nullptr if no unit should be created.
    std::shared_ptr<UnitFactory> getUnitToCreate() const;

private:
    // TODO: bool m_stateWasModified = false;
    bool m_needToClose = false;
    bool m_needToCreateUnit = false;
    int m_selectedCandidate = 0;
    std::vector<std::shared_ptr<Unit>> m_candidates;

    GuiTools::AreaSize m_screenSize;
    GuiTools::AreaSize m_candidatesListSize;
    GuiTools::Offset m_candidatesListOffset;

    void updateCandidatesListSizeAndOffset();

    std::optional<int> getCandidateUnderMouse() const;
    Rectangle getCandidateSquare(int candidate) const;
};
