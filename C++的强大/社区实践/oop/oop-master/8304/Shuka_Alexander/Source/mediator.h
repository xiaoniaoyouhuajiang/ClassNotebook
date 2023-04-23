#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <memory>

class Logger;


namespace unit {
    class Unit;
}

class GameField;


class Mediator
{
public:
    explicit Mediator(std::shared_ptr<GameField> gameField,
                      std::shared_ptr<Logger> logger);

    bool notify(std::shared_ptr<unit::Unit> unit, const std::string& act);

private:
    std::shared_ptr<GameField> gameField;
    std::shared_ptr<Logger> logger;
};


#endif // MEDIATOR_H
