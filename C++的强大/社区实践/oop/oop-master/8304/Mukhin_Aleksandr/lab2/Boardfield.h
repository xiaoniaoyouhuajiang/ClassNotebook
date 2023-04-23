#ifndef LAB2_BOARDFIELD_H
#define LAB2_BOARDFIELD_H

#include <memory>
#include "Cell.h"
#include "vector"

class Cell;
class Boardfield {
    int length = 0;
    int width = 0;
    int booked_cell = 0;
    std::vector<std::vector<Cell>> repository;
    bool is_base(int, int);
    bool is_unit(int, int);
    bool is_free_coordinates(int, int);
    bool is_valid_coordinates(int, int);
    bool landscape_action(int, int);
    bool is_free_space();
    void check_for_die(int, int);
    bool is_neutral_object(int, int);
    bool neutral_object_action(int, int);
    bool is_landscape(int, int);
    std::shared_ptr<Unit> get_unit(int);


public:
    Boardfield(int, int);
    Boardfield(const Boardfield& old_obj);
    bool add_unit(Base&, int, int, int);
    bool add_units(Base&, int, int);
    bool add_base(Base&, int, int);
    bool add_landscapes();
    bool add_landscape(int, int, int);
    bool attack(int, int, int, int);
    bool add_neutral_object(int, int, int);
    void get_boardfield();
    bool delete_unit(int, int);
    bool move_unit(int, int, int, int);
};


#endif
