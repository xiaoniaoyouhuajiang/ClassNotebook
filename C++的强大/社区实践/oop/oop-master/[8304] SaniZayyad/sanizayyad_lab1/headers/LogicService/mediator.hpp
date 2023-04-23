#ifndef mediator_hpp
#define mediator_hpp

class Unit;
class BattleField;

#include <memory>


class Mediator
{
public:
    explicit Mediator(std::shared_ptr<BattleField> battleField);
    ~Mediator() = default;

    bool notify(std::shared_ptr<Unit> unit, const std::string& action);
 
private:
    std::shared_ptr<BattleField> battleField;
};

#endif /* mediator_hpp */
