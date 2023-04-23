#include "Field.h"
#include "Landscape/ILandscape.h"


Field::FieldSnapshot::FieldSnapshot(Field& field) : width(0), height(0){
    width = field.width;
    height = field.height;

    landscapes.resize(height);
    for (auto i = 0; i < height; i++) {
        landscapes[i].resize(width);
        for (auto j = 0; j < width; j++) {
            landscapes[i][j] = field.getLandscape(Point(j, i))->getObjectType();
        }
    }

    correct = true;
}

Field::FieldSnapshot::FieldSnapshot(std::ifstream& stream) : width(0), height(0) {
    correct = false;

    if (!(stream >> width >> height)) {
        return;
    }

    landscapes.resize(height);
    for (auto i = 0; i < height; i++) {
        landscapes[i].resize(width);
    }

    for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < height; j++) {
            if (!(stream >> landscapes[i][j])) {
                return;
            }
        }
    }
    correct = true;
}

std::ofstream& operator<<(std::ofstream& stream, const Field::FieldSnapshot& snapshot) {
    stream << snapshot.width << " " << snapshot.height << std::endl;
    for (auto i = 0; i < snapshot.height; i++) {
        for (auto j = 0; j < snapshot.width; j++) {
            stream << snapshot.landscapes[i][j];
            if (j + 1 < snapshot.width)
                stream << " ";
        }
        stream << std::endl;
    }
    return stream;
}
