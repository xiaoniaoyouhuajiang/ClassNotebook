#include "Game.h"
#include "HumanFactory.h"
#include "ChaosFactory.h"
#include "Gamefield.h"
#include "stdlibrary.h"
#include <SFML/Graphics.hpp>
#include "BaseConstructor.h"
#include "GameFacade.h"
//using namespace sf;

Game::Game()
{
    initCurses();
    initWindow();
    field = new GameField(width, hight);
    baseConstructor = new BaseConstructor(field);
    facade = new GameFacade(field, this, baseConstructor);
}

void Game::initWindow(){
    srand(time(0));
}

void Game::initCurses(){
  /* ... */
    setInactive();
}

Game::~Game(){

}

void Game::run(){
    HumanFactory factor;
    BaseConstructor base_constr(field);
    TBattleCharacter* unit1 = factor.createTBattleCharacter(field,0 ,0);
    sf::RenderWindow app(sf::VideoMode(480, 650), "MyGame");
    int w = 32;

    sf::Texture t;
    t.loadFromFile("C:/Qt_EX_CoDe/Example_1/Example_lab_1/images/tiles.jpg");
    sf::Sprite s(t);

    sf::Texture tmp;
    tmp.loadFromFile("C:/Qt_EX_CoDe/Example_1/Example_lab_1/images/tiles_button.jpg");
    sf::Sprite buttons(tmp);

    sf::Texture tl;
    tl.loadFromFile("C:/Qt_EX_CoDe/Example_1/Example_lab_1/images/map.jpg");
    sf::Sprite messageBox(tl);

    sf::Font font;
    if (!font.loadFromFile("C:/Qt_EX_CoDe/Example_1/Example_lab_1/font/arial.ttf")){
        return;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::Black);



    while (app.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(app);
        int x = pos.x / w;
        int y = pos.y / w;

        sf::Event e;

        while (app.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                app.close();
            if (e.type == sf::Event::MouseButtonPressed) {
                if (e.key.code == sf::Mouse::Left){
                    facade->clicked(x,y);
                }
               else if (e.key.code == sf::Mouse::Right){
                    if (unitActive || baseActive)
                        continue;
                    facade->createBase(x,y);
               }
       }
        field->update();
        app.clear(sf::Color::White);


        for (int i = 0; i <= 15; i++)
            for (int j = 0; j <= 15; j++)
            {
                s.setTextureRect(sf::IntRect(field->gridView[i][j] * w, 0, w, w));
                s.setPosition(i*w, j*w);
                app.draw(s);
            }

        if (this->infoActive){
            messageBox.setTextureRect(sf::IntRect(0, 0, 224, 200));
            messageBox.setPosition(260,512);
            app.draw(messageBox);
            text.setPosition(275,520) ;
            text.setString(message) ;
            app.draw(text);
       }

        if(this->baseActive){
            buttons.setTextureRect(sf::IntRect(0,0,64*4,64));
            buttons.setPosition(0,512);
            app.draw(buttons);
        }

        app.display();

    }

}

}




bool Game::getUnitActive(){
    return unitActive;
}


bool Game::getBaseActive(){
    return baseActive;
}


bool Game::getInfoActive(){
    return infoActive;
}


void Game::setInactive(){
    unitActive = baseActive = infoActive = false;
}


void Game::setInfoMessage(Event event){
    message = "";
    infoActive = true;
    if (event.type==Event::UNIT_INFO){
        message += "Race: ";
        if (event.unitInfo.rase == Event::CHAOS)
            message = message + "chaos" + "\n";
        else
            message = message + "human" + "\n";
        message += "Type: ";
        if (event.unitInfo.unitType == Event::WARRIOR)
            message = message + "warrior" + "\n";
        else if(event.unitInfo.unitType == Event::MAGIC)
            message = message + "mag" + "\n";
        else
            message = message + "siege" + "\n";
        message += "Relation: ";
       if (event.unitInfo.relation == Event::FRIEND){
            message = message + "enemy" + "\n";
            message = message + "HP: " + std::to_string(event.unitInfo.hitPoint) + "\n";
            message = message + "Armor: " + std::to_string(event.unitInfo.armor) + "\n";
        }
        else{
            message = message + "friend" + "\n";
            message = message + "HP: " + std::to_string(event.unitInfo.hitPoint) + "\n";
            message = message + "Armor: " + std::to_string(event.unitInfo.armor) + "\n";
            message = message + "Act Points: " + std::to_string(event.unitInfo.actionPoint) + "\n";
            message = message + "Damage: " + std::to_string(event.unitInfo.damagePoint) + "\n";
            message = message + "Distant attack: " + std::to_string(event.unitInfo.distantAttack) + "\n";
        }



    }

    else {
        message += "Race: ";
        if (event.baseInfo.race == Event::CHAOS)
            message = message + "chaos" + "\n";
        else
            message = message + "human" + "\n";
        message += "Relation: ";
        if (event.baseInfo.relation == Event::ENEMY){
            message = message + "enemy" + "\n";
            message = message + "HP: " + std::to_string(event.baseInfo.hitPoint) + "\n";
        }
        else{
            message = message + "friend" + "\n";
            message = message + "HP: " + std::to_string(event.baseInfo.hitPoint) + "\n";
            message = message + "Limit: " + std::to_string(event.baseInfo.unitLimit) + "\n";
            message = message + "Was create: " + std::to_string(event.baseInfo.unitCount) + "\n";
            message = message + "Can create: " + std::to_string(event.baseInfo.canCreate) + "\n";
         }

   }
}


void Game::setUnitActive(bool val){
    unitActive = val;
}


void Game::setBaseActive(bool val){
    baseActive = val;
}













