#ifndef LAB2_BOARDFIELD_H
#define LAB2_BOARDFIELD_H

#include <vector>
#include "AbstractionBoardfield.h"
#include "Base.h"
#include "Cell.h"
#include "SimpleLogger.h"

class Boardfield : public AbstractionBoardfield {
    int length = 0;
    int width = 0;
    int booked_cell = 0;
    std::vector<std::vector<Cell>> repository;
    bool is_base(int, int) const override;
    bool is_unit(int, int) const override;
    bool is_free_coordinates(int, int) const override;
    bool is_valid_coordinates(int, int) const override;
    bool landscape_action(int, int) override;
    bool is_free_space() const override;
    void check_for_die(int, int) override;
    bool is_neutral_object(int, int) const override;
    bool neutral_object_action(int, int) override;
    bool is_landscape(int, int) const override;
    [[nodiscard]] std::shared_ptr<Unit> get_unit(int) const override;
    friend class ProxyBoardfield;

public:
    std::shared_ptr<AbstractLogger> log;
    Boardfield(int, int, std::shared_ptr<AbstractLogger> = nullptr);
    Boardfield(const Boardfield& old_obj);

    bool add_base(Base&, int, int) override;
    bool add_unit(Base&, int, int, int) override;
    bool add_units(Base&, int, int) override;
    bool add_landscapes() override;
    bool add_landscape(int, int, int) override;
    bool add_neutral_object(int, int, int) override;

    bool attack(int, int, int, int, std::string) override;
    void get_boardfield() const override;
    bool delete_unit(int, int) override;
    bool move_unit(int, int, int, int) override;
};


#endif
