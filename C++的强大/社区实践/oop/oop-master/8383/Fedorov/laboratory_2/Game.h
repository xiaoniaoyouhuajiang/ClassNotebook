#ifndef GAME_H
#define GAME_H

class GameField;


class Game{
  private:
    int width = 40;
    int hight = 40;
    int xWin;
    int yWin;
    void initWindow();
    void initCurses();
    GameField* field;
  public:
    void run();
    Game();
    virtual ~Game();

};
#endif // GAME_H
