#include <Mountains.h>
#include <Champaign.h>
#include "AirborneCreator.h"
#include "SpecialForcesCreator.h"
#include "DoctorCreator.h"
#include "Boardfield.h"
#include "EngineerCreator.h"
#include "AmbassadorCreator.h"
#include "MinistryCreator.h"
#include <FireExtinguisher.h>
#include <Sword.h>
#include <Serum.h>
#include <SuperNeutralObject.h>

Boardfield::Boardfield(int length, int width) {
    this->length = length;
    this->width = width;

    repository = std::vector<std::vector<Cell>>(length);
    for (int i = 0; i < length; i++) {
        repository[i] = std::vector<Cell>(width);
    }
}


std::shared_ptr<Unit> Boardfield::get_unit(int key) {
    if (is_free_space()) {
        Creator* tmp = nullptr;
        std::shared_ptr<Creator> return_pointer;

        switch (key) {
            case 0:
                tmp = new SpecialForcesCreator();
                break;
            case 1:
                tmp = new DoctorCreator();
                break;
            case 2:
                tmp = new AirborneCreator();
                break;
            case 3:
                tmp = new EngineerCreator();
                break;
            case 4:
                tmp = new AmbassadorCreator();
                break;
            case 5:
                tmp = new MinistryCreator();
                break;
            default:
                throw std::out_of_range("Wrong param, read documentation before");
        }

        return_pointer = std::shared_ptr<Creator>(tmp);
        tmp = nullptr;

        return return_pointer->make_unit();
    }
    return nullptr;
}


bool Boardfield::add_unit(Base& to_base, int x, int y, int key) {
    if (to_base.max_size > to_base.current_size && is_valid_coordinates(x, y) && is_free_coordinates(x, y)) {
        if (is_landscape(x, y) && !repository[x][y].landscape->can_stand) {
            return false;
        }
        auto tmp_unit = get_unit(key);
        tmp_unit->greeting();
        tmp_unit->x = x;
        tmp_unit->y = y;
        to_base.add_unit(tmp_unit);
        repository[x][y].base = &to_base;
        repository[x][y].unit = tmp_unit;

        switch(key) {
            case 0:
                repository[x][y].unit->unit_symbol = "★";
                break;
            case 1:
                repository[x][y].unit->unit_symbol = "✋";
                break;
            case 2:
                repository[x][y].unit->unit_symbol = "☆";
                break;
            case 3:
                repository[x][y].unit->unit_symbol = "✐";
                break;
            case 4:
                repository[x][y].unit->unit_symbol = "☠";
                break;
            case 5:
                repository[x][y].unit->unit_symbol = "☎";
                break;
            default:
                std::cout << "Invalid character!" << std::endl;
                return false;
        }

        booked_cell++;

        if (is_landscape(x, y)) {
            landscape_action(x, y);
            check_for_die(x, y);
        }

        if (is_neutral_object(x, y)) {
            neutral_object_action(x, y);
            check_for_die(x, y);
        }
        return true;
    }
    return false;
}


bool Boardfield::add_base(Base& to_base, int x, int y) {
    if (is_valid_coordinates(x, y) && is_free_coordinates(x, y)) {
        repository[x][y].base = &to_base;
        repository[x][y].base->x = x;
        repository[x][y].base->y = y;
        repository[x][y].base_symbol = "❆";
        booked_cell++;
        return true;
    }
    return false;
}


void Boardfield::get_boardfield() {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (repository[i][j].unit != nullptr) {
                std::cout << repository[i][j].unit->unit_symbol;
            }
            std::cout << repository[i][j].base_symbol << repository[i][j].landscape_symbol << repository[i][j].neutral_object_symbol << "     ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


bool Boardfield::delete_unit(int x, int y) {
    if (is_valid_coordinates(x, y) && !is_free_coordinates(x, y)) {
        int i = 0;
        for (auto& item : repository[x][y].base->units) {
            if (item->x == x && item->y == y) {
                repository[x][y].base->current_size--;
                repository[x][y].base->units.erase(repository[x][y].base->units.begin() + i);
                repository[x][y].unit = nullptr;
                repository[x][y].base = nullptr;
                std::cout << "I'm fall, at the (" << x << ", " << y << ") position(" << std::endl;
                return true;
            } else {
                ++i;
            }
        }
    }
    return false;
}


Boardfield::Boardfield(const Boardfield &old_obj) {
    length = old_obj.length;
    width = old_obj.width;
    repository = std::vector<std::vector<Cell>>(length);
    for (int i = 0; i < length; i++) {
        repository[i] = std::vector<Cell>(width);
    }
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            repository[i][j] = old_obj.repository[i][j];
        }
    }
}


void Boardfield::check_for_die(int x, int y) {
    if (is_valid_coordinates(x, y) && is_unit(x, y) && repository[x][y].unit->defense.get_health() <= 0) {
        delete_unit(x, y);
    }
}


bool Boardfield::move_unit(int old_x, int old_y, int dest_x, int dest_y) {
    if (is_valid_coordinates(old_x, old_y) && is_valid_coordinates(dest_x, dest_y)
        && !is_free_coordinates(old_x, old_y) && is_free_coordinates(dest_x, dest_y) && is_unit(old_x, old_y)) {
        if (is_landscape(dest_x, dest_y) && !repository[dest_x][dest_y].landscape->can_stand) {
            return false;
        }
        repository[dest_x][dest_y].unit = repository[old_x][old_y].unit;
        repository[old_x][old_y].unit = nullptr;
        repository[dest_x][dest_y].base = repository[old_x][old_y].base;

        int i = 0;
        for (auto& item : repository[old_x][old_y].base->units) {
            if (item->x == old_x && item->y == old_y) {
                repository[old_x][old_y].base->units.erase(repository[old_x][old_y].base->units.begin() + i);
                repository[old_x][old_y].base->current_size--;
                repository[dest_x][dest_y].unit->x = dest_x;
                repository[dest_x][dest_y].unit->y = dest_y;
                repository[old_x][old_y].base->add_unit(repository[dest_x][dest_y].unit);

                if (is_landscape(dest_x, dest_y)) {
                    landscape_action(dest_x, dest_y);
                    check_for_die(dest_x, dest_y);
                }
                if (is_neutral_object(dest_x, dest_y)) {
                    neutral_object_action(dest_x, dest_y);
                    check_for_die(dest_x, dest_y);
                }
                repository[old_x][old_y].base = nullptr;
                return true;
            } else {
                ++i;
            }
        }
    }
    return false;
}


bool Boardfield::landscape_action(int x, int y) {
    if (is_valid_coordinates(x, y) && !is_free_coordinates(x, y) && is_unit(x, y) && is_landscape(x, y)) {
//        repository[x][y].unit->defense.change(repository[x][y].landscape->defense.get_health());
        repository[x][y].unit->defense.change(repository[x][y].landscape->get_health());
        repository[x][y].unit->attack.change(repository[x][y].landscape->attack.get_attack());
        repository[x][y].unit->intelligence += repository[x][y].landscape->intelligence;
        return true;
    }
    return false;
}


bool Boardfield::neutral_object_action(int x, int y) {
    if (is_valid_coordinates(x, y) && is_unit(x, y) && is_neutral_object(x, y)) {
        repository[x][y] = repository[x][y][repository[x][y].neutral_object];
        repository[x][y].neutral_object = nullptr;
    }

    if (is_valid_coordinates(x, y) && is_unit(x, y) && is_neutral_object(x, y)) {
        repository[x][y].unit->defense.change(repository[x][y].neutral_object->defense.get_health());
        repository[x][y].unit->attack.change(repository[x][y].neutral_object->attack.get_attack());
        repository[x][y].unit->intelligence += repository[x][y].neutral_object->intelligence;
        repository[x][y].neutral_object = nullptr;
        return true;
    }
    return false;
}


bool Boardfield::is_base(int x, int y) {
    return repository[x][y].unit == nullptr && repository[x][y].base != nullptr;
}


bool Boardfield::is_unit(int x, int y) {
    return repository[x][y].unit != nullptr;
}


bool Boardfield::is_free_coordinates(int x, int y) {
    return repository[x][y].unit == nullptr && repository[x][y].base == nullptr;
}


bool Boardfield::is_valid_coordinates(int x, int y) {
    return x < length && x > -1 && y < width && y > -1;
}

bool Boardfield::add_landscapes() {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (is_free_coordinates(i, j)) {
                int choice = (i+j) % 3;
                std::shared_ptr<Landscape> tmp;
                std::string tmp_image;
                switch (choice) {
                    case 0:
                        tmp = std::make_shared<Fire>();
                        tmp_image = "✨";
                        break;
                    case 1:
                        tmp = std::make_shared<Mountains>();
                        tmp_image = "∆";
                        break;
                    case 2:
                        tmp = std::make_shared<Champaign>();
                        tmp_image = "_";
                        break;
                    default:
                        std::cout << "Something wrong in adding landscape!" << std::endl;
                        return false;
                }
                repository[i][j].landscape = tmp;
                repository[i][j].landscape_symbol = tmp_image;
            }
        }
    }
    return true;
}

bool Boardfield::is_landscape(int x, int y) {
    return repository[x][y].landscape != nullptr;
}

bool Boardfield::is_free_space() {
    return width*length > booked_cell;
}

bool Boardfield::add_neutral_object(int x, int y, int key) {
    if (is_valid_coordinates(x, y)) {
        std::shared_ptr<NeutralObject> tmp;
        std::string tmp_image{};
        switch (key) {
            case 0:
                tmp = std::make_shared<FireExtinguisher>();
                tmp_image = "♻";
                break;
            case 1:
                tmp = std::make_shared<Sword>();
                tmp_image = "➛";
                break;
            case 2:
                tmp = std::make_shared<Serum>();
                tmp_image = "☢";
                break;
            case 3:
                tmp = std::make_shared<SuperNeutralObject>();
                tmp_image = "✔";
                break;
            default:
                std::cout << "Invalid key for neutral object!" << std::endl;
                return false;
        }
        repository[x][y].neutral_object = tmp;
        repository[x][y].neutral_object_symbol = tmp_image;
        if (is_unit(x, y)) {
            neutral_object_action(x, y);
            check_for_die(x, y);
        }
        return true;
    }
    return false;
}

bool Boardfield::is_neutral_object(int x, int y) {
    return repository[x][y].neutral_object != nullptr;
}

bool Boardfield::attack(int first_x, int first_y, int second_x, int second_y) {
//    repository[second_x][second_y] = repository[second_x][second_y][repository[first_x][first_y]]
    if (is_valid_coordinates(first_x, first_y) && is_valid_coordinates(second_x, second_y) &&
        is_unit(first_x, first_y) && is_unit(second_x, second_y) &&
        repository[first_x][first_y].base != repository[second_x][second_y].base) {
//        repository[second_x][second_y].unit->defense.change(-repository[first_x][first_y].unit->attack.get_attack());
        repository[second_x][second_y] = repository[second_x][second_y][repository[first_x][first_y]];
        check_for_die(second_x, second_y);
        return true;
    }
    return false;
}

bool Boardfield::add_units(Base& to_base, int count, int key) {
    if (to_base.max_size - to_base.current_size >= count) {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                if (is_free_coordinates(i, j)) {
                    add_unit(to_base, i, j, key);
                    count--;
                }
                if (count == 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Boardfield::add_landscape(int x, int y, int key) {
    if (!is_landscape(x, y)) {
        std::shared_ptr<Landscape> tmp;
        std::string tmp_image;
        switch (key) {
            case 0:
                tmp = std::make_shared<Fire>();
                tmp_image = "✨";
                break;
            case 1:
                tmp = std::make_shared<Mountains>();
                tmp_image = "∆";
                break;
            case 2:
                tmp = std::make_shared<Champaign>();
                tmp_image = "_";
                break;
            default:
                std::cout << "Something wrong in adding landscape!" << std::endl;
                return false;
        }
        repository[x][y].landscape = tmp;
        repository[x][y].landscape_symbol = tmp_image;
        if (is_unit(x, y)) {
            landscape_action(x, y);
            check_for_die(x, y);
        }
        return true;
    }
    return false;
}
