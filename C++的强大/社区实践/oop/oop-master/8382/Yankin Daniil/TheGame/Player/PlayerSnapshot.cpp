#include "Player.h"
#include "Landscape/ILandscape.h"


Player::PlayerSnapshot::PlayerSnapshot(Player& player) {
    correct = true;
    color = player.color;
}

Player::PlayerSnapshot::PlayerSnapshot(std::ifstream& stream) {
    correct = false;

    uint16_t colorValue;
    if (!(stream >> colorValue)) {
        return;
    }
    if (colorValue == PLAYER_BLUE || colorValue == PLAYER_RED || colorValue == PLAYER_GREEN || colorValue == PLAYER_ORANGE) {
        color = static_cast<uint16_t>(colorValue);
        correct = true;
    }
}

uint16_t Player::PlayerSnapshot::getColor() const {
    return color;
}

std::ofstream& operator<<(std::ofstream& stream, const Player::PlayerSnapshot& snapshot) {
    stream << snapshot.color << std::endl;
    return stream;
}

bool operator==(Player::PlayerSnapshot& snapshot1, Player::PlayerSnapshot& snapshot2) {
    if (snapshot1.color == snapshot2.color)
        return true;
    return false;
}

bool operator!=(Player::PlayerSnapshot& snapshot1, Player::PlayerSnapshot& snapshot2) {
    return !(snapshot1 == snapshot2);
}
