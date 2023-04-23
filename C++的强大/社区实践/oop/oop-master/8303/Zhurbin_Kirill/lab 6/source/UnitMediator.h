#ifndef OOP1_UNITMEDIATOR_H
#define OOP1_UNITMEDIATOR_H


class Mediator;
class UnitMediator{

public:
    Mediator* mediator;
    UnitMediator(Mediator* mediator =nullptr) : mediator(mediator){};

    void setMediator(Mediator* mediator){
        this->mediator = mediator;
    }

};

#endif //OOP1_UNITMEDIATOR_H
