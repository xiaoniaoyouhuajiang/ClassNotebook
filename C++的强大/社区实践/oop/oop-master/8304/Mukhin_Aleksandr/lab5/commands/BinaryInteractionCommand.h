#ifndef LAB2_BINARYINTERACTIONCOMMAND_H
#define LAB2_BINARYINTERACTIONCOMMAND_H

#include "Mediator.h"
#include "Cell.h"
#include "Command.h"
class BinaryInteractionCommand : public Command {
private:
    Cell cell1;
    Cell cell2;
    std::shared_ptr<Mediator> mediator = nullptr;
    std::string command;

public:
    BinaryInteractionCommand(std::string command, Cell& cell1, Cell& cell2) : command(command), cell1(cell1), cell2(cell2) {
        if (this->command == "unit action") {
            mediator = std::make_shared<Mediator>(this->cell1.unit, this->cell2.unit);
        } else if (this->command == "base action") {
            mediator = std::make_shared<Mediator>(this->cell1.base, this->cell2.unit);
        }
    }

    void execute() const override;
};


#endif
