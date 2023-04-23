//
// Created by Alex on 22.03.2020.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H


#include "../OtherClasses/Base/Base.h"
#include "../OtherClasses/Field/Field.h"
#include "../Logging/Logger/Logger.h"
#include "../SaveGame/GameLoader.h"
#include "../SaveGame/GameSaver.h"
#include "../Gamer/Gamer.h"
#include "../OtherClasses/NeutralObjects/Client.h"
#include "../Rules/Rule.h"
#include "../Rules/FirstRule.h"

using namespace Logging;

namespace MyGame {

    class Game {
    public:
        static Game &Instance() {
            // согласно стандарту, этот код ленивый и потокобезопасный
            static Game s;
            return s;
        }

    private:
        Game();

        ~Game();

    private:
        const int widthField = 10;
        const int heightField = 5;
        Logger logger;
        GameLoader *gameLoader;
        GameSaver *gameSaver;
        Field *field;
        NeutralObject **neutralObjects;
        int order = 1;
        Rule *rule;

    public:
        void getInformationAboutEnvironment(int *array, int x, int y);

        void updateUnitPosition(int lastX, int lastY, int newX, int newY);

        bool attackUnit(int xPositionUnit1, int yPositionUnit1, int xPositionUnit2, int yPositionUnit2);

        void setNeutralObject();

        Gamer *gamer1;
        Gamer *gamer2;

        int getOrder() const;

        void setOrder(int order);

        void saveState();

        void loadState();

        bool checkFile();

        void startNewGame();

        void switchOrder();

        Gamer *getCurrentGamer();

    private:
        void loadNeutralObject();

        void loadOrder();

        void saveOrder();

        void loadGamers();

        void saveNeutralObject();

        void saveGamers();

        void initGame();

        void checkAttack(int xPositionUnit1, int yPositionUnit1, int xPositionUnit2, int yPositionUnit2);

        void checkAddUnit(int x,int y);

    };

}
#endif //GAME_GAME_H
