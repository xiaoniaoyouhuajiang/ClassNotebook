#include "ProxyBoardfield.h"

bool ProxyBoardfield::is_base(int x, int y) const {
    board->log->write("Check for \"Is Base\"");
    return board->is_base(x, y);
}

bool ProxyBoardfield::is_unit(int x, int y) const {
    board->log->write("Check for \"Is Unit\"");
    return board->is_unit(x, y);
}

bool ProxyBoardfield::is_free_coordinates(int x, int y) const {
    board->log->write("Check for free coordinates");
    return board->is_free_coordinates(x, y);
}

bool ProxyBoardfield::is_valid_coordinates(int x, int y) const {
    board->log->write("Check for valid coordinates");
    return board->is_valid_coordinates(x, y);
}

bool ProxyBoardfield::landscape_action(int x, int y) {
    board->log->write(std::string("Landscape action at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    return board->landscape_action(x, y);
}

bool ProxyBoardfield::is_free_space() const {
    board->log->write("Check for free space");
    return board->is_free_space();
}

void ProxyBoardfield::check_for_die(int x, int y) {
    board->log->write(std::string("Check for die at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    board->check_for_die(x, y);
}

bool ProxyBoardfield::is_neutral_object(int x, int y) const {
    board->log->write("Check for \"Is Neutral Object\"");
    return board->is_neutral_object(x, y);
}

bool ProxyBoardfield::neutral_object_action(int x, int y) {
    board->log->write(std::string("Neutral object action at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    return board->neutral_object_action(x, y);
}

bool ProxyBoardfield::is_landscape(int x, int y) const {
    board->log->write("Check for \"Is Landscape\"");
    return board->is_landscape(x, y);
}

std::shared_ptr<Unit> ProxyBoardfield::get_unit(int key) const {
    board->log->write(std::string("Making Units ") + std::to_string(key) + " type");
    return board->get_unit(key);
}

bool ProxyBoardfield::add_base(Base& base, int x, int y) {
    bool tmp_result = board->add_base(base, x, y);
    if (tmp_result) {
        board->log->write(std::string("Adding base at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    } else {
        board->log->write(std::string("Can't add base at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    }
    return tmp_result;
}

bool ProxyBoardfield::add_unit(Base& base, int x, int y, int key) {
    bool tmp_result = board->add_unit(base, x, y, key);
    if (tmp_result) {
        board->log->write(std::string("Adding unit at (") + std::to_string(x) + "; " + std::to_string(y) + ") " + std::to_string(key) + " type");
    } else {
        board->log->write(std::string("Can't add unit at (") + std::to_string(x) + "; " + std::to_string(y) + ") " + std::to_string(key) + " type");
    }
    return tmp_result;
}

bool ProxyBoardfield::add_units(Base& base, int count, int key) {
    board->log->write(std::string("Adding ") + std::to_string(count) + std::string(" units, ") + std::to_string(key) + " type");
    return board->add_units(base, count, key);
}

bool ProxyBoardfield::add_landscapes() {
    board->log->write("Adding landscapes");
    return board->add_landscapes();
}

bool ProxyBoardfield::add_landscape(int x, int y, int key, bool interaction) {
    board->log->write(std::string("Adding landscape at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    return board->add_landscape(x, y, key, interaction);
}

bool ProxyBoardfield::add_neutral_object(int x, int y, int key, bool interaction) {
    board->log->write(std::string("Adding neutral object at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    return board->add_neutral_object(x, y, key, interaction);
}

bool ProxyBoardfield::attack(int first_x, int first_y, int second_x, int second_y, std::string command) {
    bool tmp_result = board->attack(first_x, first_y, second_x, second_y, command);
    if (tmp_result) {
        board->log->write(std::string("Cell at (") + std::to_string(first_x) + "; " + std::to_string(first_y) + ") attack cell at (" +
                          std::to_string(second_x) + "; " + std::to_string(second_y) + ")");
    } else {
        board->log->write(std::string("Cell at (") + std::to_string(first_x) + "; " + std::to_string(first_y) + ") can't attack cell at (" +
                          std::to_string(second_x) + "; " + std::to_string(second_y) + ")");
    }
    return tmp_result;
}

void ProxyBoardfield::get_boardfield() const {
    board->log->write("Getting boardfield");
    return board->get_boardfield();
}

bool ProxyBoardfield::delete_unit(int x, int y) {
    bool tmp_result = board->delete_unit(x, y);
    if (tmp_result) {
        board->log->write(std::string("Delete unit at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    } else {
        board->log->write(std::string("Can't delete unit at (") + std::to_string(x) + "; " + std::to_string(y) + ")");
    }
    return tmp_result;
}

bool ProxyBoardfield::move_unit(int old_x, int old_y, int dest_x, int dest_y) {
    bool tmp_result = board->move_unit(old_x, old_y, dest_x, dest_y);
    if (tmp_result) {
        board->log->write(std::string("Move unit from (") + std::to_string(old_x) + "; " + std::to_string(old_y) + ") to (" +
                          std::to_string(dest_x) + "; " + std::to_string(dest_y) + ")");
    } else {
        board->log->write(std::string("Can't move unit from (") + std::to_string(old_x) + "; " + std::to_string(old_y) + ") to (" +
                          std::to_string(dest_x) + "; " + std::to_string(dest_y) + ")");
    }
    return tmp_result;
}

Boardfield* ProxyBoardfield::get_board() const {
    return board;
}


std::ostream& operator<<(std::ostream& out, const ProxyBoardfield& board) {
    int length = board.get_board()->get_length();
    int width = board.get_board()->get_width();

    out << length << " " << width << std::endl;

    auto tmp_repo = board.get_board()->get_repository();
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            out << i << " " << j << std::endl;
            out << tmp_repo[i][j];
        }
    }

    return out;
}

void ProxyBoardfield::set_params(std::string dest, int x, int y, int health, int attack, int intelligence) {
    board->set_params(dest, x, y, health, attack, intelligence);
}
