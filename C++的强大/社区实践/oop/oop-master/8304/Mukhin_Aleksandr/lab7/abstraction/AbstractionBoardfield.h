#ifndef LAB2_ABSTRACTIONBOARDFIELD_H
#define LAB2_ABSTRACTIONBOARDFIELD_H

#include "Base.h"

class AbstractionBoardfield {
private:
    virtual bool is_base(int, int) const = 0;
    virtual bool is_unit(int, int) const = 0;
    virtual bool is_free_coordinates(int, int) const = 0;
    virtual bool is_valid_coordinates(int, int) const = 0;
    virtual bool landscape_action(int, int) = 0;
    virtual void check_for_die(int, int) = 0;
    virtual bool is_neutral_object(int, int) const = 0;
    virtual bool neutral_object_action(int, int) = 0;
    virtual bool is_landscape(int, int) const = 0;
    virtual std::shared_ptr<Unit> get_unit(int) const = 0;

public:
    AbstractionBoardfield() = default;
    virtual bool add_base(Base&, int, int) = 0;
    virtual bool add_unit(Base&, int, int, int) = 0;
    virtual bool add_units(Base&, int, int) = 0;
    virtual bool add_landscapes() = 0;
    virtual bool add_landscape(int, int, int, bool) = 0;
    virtual bool add_neutral_object(int, int, int, bool) = 0;
    virtual void set_params(std::string, int, int, int, int, int) = 0;

    virtual bool attack(int, int, int, int, std::string) = 0;
    virtual void get_boardfield() const = 0;
    virtual bool delete_unit(int, int) = 0;
    virtual bool move_unit(int, int, int, int) = 0;
//    virtual bool load(Save& save) = 0;

    virtual bool is_free_space() const = 0;
    virtual ~AbstractionBoardfield() = default;
};


#endif
