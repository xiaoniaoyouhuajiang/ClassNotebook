

#ifndef Handler_h
#define Handler_h

class Base;
class GameMap;
//class FriendsEntity;
//class EnemiesEntity;
class TeamEntity;
class Unit;
class Command;
class GameMaster;
class Memento;

class Handler{
public:
    virtual Handler *setNext(Handler* handler) = 0;
    virtual Command* handle(char request, Base *base, bool* death, GameMaster* GM) = 0;
};


class AbstractHandler: public Handler{
private:
    Handler *nextHandler;
public:
    AbstractHandler(): nextHandler(nullptr){};
    Handler *setNext(Handler* handler) override;
    Command* handle(char request, Base *base, bool* death, GameMaster* GM) override;
};


class AttackHandler: public AbstractHandler{
public:
    Command* handle(char request, Base *base, bool* death, GameMaster* GM) override;
};


class MoveHandler: public AbstractHandler{
    public:

    Command* handle(char request, Base *base, bool* death, GameMaster* GM) override;
};


class ChangeUnitHandler: public AbstractHandler{
    public:
    Command* handle(char request,  Base *base, bool* death, GameMaster* GM) override;
    
};


class BaseControlHandler: public AbstractHandler{
    public:
    Command* handle(char request,  Base *base, bool* death, GameMaster* GM) override;
};


class HelpHandler: public AbstractHandler{
    public:
    Command* handle(char request, Base *base, bool* death, GameMaster* GM) override;
};

class OptionsHandler: public AbstractHandler{
public:
    Command* handle(char request, Base *base, bool* death, GameMaster* GM) override;
};
#endif /* Handler_h */


