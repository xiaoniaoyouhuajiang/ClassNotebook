#include "Originator.h"

std::shared_ptr<Save> Originator::save() {
    return std::make_shared<Save>(board, base);
}

void Originator::load(std::shared_ptr<Save> save) {
    ProxyBoardfield* new_proxy_board = nullptr;
    int length = 0;
    int width = 0;
    int base_size = -1;

    if (!save->input.is_open()) {
        save->input = std::ifstream("save.txt");
    }
    save->input >> base_size;
    save->input >> length;
    save->input >> width;

    auto new_board = new Boardfield(length, width);
    Base* new_base = new Base(base_size);
    new_proxy_board = new ProxyBoardfield(*new_board);
    int tmp_x = -1;
    int tmp_y = -1;
    int tmp_unit_health = -1;
    int tmp_unit_attack = -1;
    int tmp_unit_intelligence = -1;
    int tmp_unit_type = -1;
    int tmp_landscape_type = -1;
    int tmp_neutral_object_type = -1;
    int tmp_base_size = -1;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            save->input >> tmp_x;
            save->input >> tmp_y;

            if (tmp_x != i || tmp_y != j) {
                std::cout << "Error!" << std::endl;
                return;
            }

            save->input >> tmp_unit_health;
            if (tmp_unit_health != -1) {
                save->input >> tmp_unit_attack;
                save->input >> tmp_unit_intelligence;
                save->input >> tmp_unit_type;
                new_proxy_board->add_unit(*new_base, tmp_x, tmp_y, tmp_unit_type);
                new_proxy_board->set_params("unit", tmp_x, tmp_y, tmp_unit_health, tmp_unit_attack, tmp_unit_intelligence);
            }

            save->input >> tmp_landscape_type;
            if (tmp_landscape_type != -1) {
                new_proxy_board->add_landscape(tmp_x, tmp_y, tmp_landscape_type, false);
            }
            save->input >> tmp_base_size;
            if (tmp_base_size != -1) {
                new_proxy_board->add_base(*new_base, tmp_x, tmp_y);
            }
            save->input >> tmp_neutral_object_type;
            if (tmp_neutral_object_type != -1) {
                new_proxy_board->add_neutral_object(tmp_x, tmp_y, tmp_neutral_object_type, false);
            }
        }
    }
    *base = *new_base;
    *board->get_board() = *new_proxy_board->get_board();
}