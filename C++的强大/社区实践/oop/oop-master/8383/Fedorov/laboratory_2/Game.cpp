#include "Game.h"
#include "HumanFactory.h"
#include "ChaosFactory.h"
#include "Gamefield.h"
#include "stdlibrary.h"
#include <SFML/Graphics.hpp>
#include "BaseConstructor.h"
using namespace sf;

Game::Game(){
    this->initCurses();
    this->initWindow();
    this->field = new GameField(width, hight);
}

void Game::initWindow(){
    srand(time(0));
}

void Game::initCurses(){
  /* ... */
}

Game::~Game(){

}

void Game::run(){
    HumanFactory factor;
    BaseConstructor base_constr(field);
    TBattleCharacter* unit1 = factor.createTBattleCharacter(field,0 ,0);
    RenderWindow app(VideoMode(480, 480), "MyGame");
    int w = 32;

    Texture t;
    t.loadFromFile("C:/Qt_EX_CoDe/Example_1/Example_lab_1/images/tiles.jpg");
    Sprite s(t);




    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x / w;
        int y = pos.y / w;

        sf::Event e;

        while (app.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                app.close();
            //Была нажата кнопка мыши…?
            if (e.type == sf::Event::MouseButtonPressed) {
                //Если это - левая кнопка мыши, то открываем клетку
                if (e.key.code == Mouse::Left){
                    unit1->move(x,y);
                }
               else if (e.key.code == Mouse::Right){
                    base_constr.createHumanBase(x,y);
               }
       }
        field->update();
        app.clear(Color::White);

        for (int i = 0; i <= 15; i++)
            for (int j = 0; j <= 15; j++)
            {
                s.setTextureRect(IntRect(field->gridView[i][j] * w, 0, w, w));
                s.setPosition(i*w, j*w);
                app.draw(s);
            }
        app.display();

    }

}

}
