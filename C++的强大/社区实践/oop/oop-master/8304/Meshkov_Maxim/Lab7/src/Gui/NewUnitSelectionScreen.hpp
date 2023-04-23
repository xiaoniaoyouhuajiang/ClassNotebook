#pragma once

#include <vector>
#include <optional>
#include <raylib.h>

#include "../Units/UnitFactory.hpp"
#include "GuiTools.hpp"
#include "../Base.hpp"

class NewUnitSelectionScreen {
public:
    NewUnitSelectionScreen(std::weak_ptr<const Base> base);

    void draw();

    void handleEvents();

    bool needToClose() const;

    // Returns nullptr if no unit should be created.
    std::shared_ptr<UnitFactory> getUnitToCreate() const;

private:
    std::weak_ptr<const Base> m_base;

    bool m_needToClose = false;
    bool m_needToCreateUnit = false;
    int m_selectedCandidate = 0;
    std::vector<std::shared_ptr<Unit>> m_candidates;

    bool m_isDrawn = false;
    GuiTools::AreaSize m_screenSize;
    GuiTools::AreaSize m_candidatesListSize;
    GuiTools::Offset m_candidatesListOffset;

    void updateCandidatesListSizeAndOffset(int y);

    std::optional<int> getCandidateUnderMouse() const;
    Rectangle getCandidateSquare(int candidate) const;
};
