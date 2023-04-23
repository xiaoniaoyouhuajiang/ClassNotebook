#ifndef LAB2_UNARYINTERACTIONCOMMAND_H
#define LAB2_UNARYINTERACTIONCOMMAND_H

#include "Command.h"
#include "Cell.h"
#include "Mediator.h"
class UnaryInteractionCommand : public Command {
private:
    Cell cell;
    std::shared_ptr<Mediator> mediator = nullptr;
    std::string command;

public:
    explicit UnaryInteractionCommand(std::string command, Cell& cell) : command(std::move(command)), cell(cell) {
        if (this->command == "neutral object action") {
            mediator = std::make_shared<Mediator>(this->cell.unit, this->cell.neutral_object);
        } else if (this->command == "landscape action") {
            mediator = std::make_shared<Mediator>(this->cell.unit, this->cell.landscape);
        }
    }
    void execute() const override;
};


#endif
