#ifndef LAB2_PROXYBOARDFIELD_H
#define LAB2_PROXYBOARDFIELD_H

#include "Boardfield.h"
#include "AbstractionBoardfield.h"

class ProxyBoardfield : public AbstractionBoardfield {
private:
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
    friend std::ostream& operator<< (std::ostream&, const ProxyBoardfield&);
    Boardfield* board = nullptr;

public:
    ProxyBoardfield() = default;
    explicit ProxyBoardfield(Boardfield& board) : board(&board) {}
    bool add_base(Base&, int, int) override;
    bool add_unit(Base&, int, int, int) override;
    bool add_units(Base&, int, int) override;
    bool add_landscapes() override;
    bool add_landscape(int, int, int, bool = true) override;
    bool add_neutral_object(int, int, int, bool = true) override;
    void set_params(std::string, int, int, int, int, int) override;

    bool attack(int, int, int, int, std::string) override;
    void get_boardfield() const override;
    bool delete_unit(int, int) override;
    bool move_unit(int, int, int, int) override;
    [[nodiscard]] Boardfield* get_board() const;
};


#endif
