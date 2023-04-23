#include "NeutralContext.h"
#include "Landscape/ILandscape.h"


NeutralContext::NeutralSnapshot::NeutralSnapshot(NeutralContext& neutral) : point(Point(0, 0)) {
    correct = true;
    point = neutral.point;
}

NeutralContext::NeutralSnapshot::NeutralSnapshot(std::ifstream& stream) : point(Point(0, 0)) {
    correct = false;

    uint16_t x, y;
    if (!(stream >> x >> y)) {
        return;
    }
    point = Point(x, y);

    correct = true;
}

std::ofstream& operator<<(std::ofstream& stream, const NeutralContext::NeutralSnapshot& snapshot) {
    stream << snapshot.point.getX() << " " << snapshot.point.getY() << std::endl;
    return stream;
}
