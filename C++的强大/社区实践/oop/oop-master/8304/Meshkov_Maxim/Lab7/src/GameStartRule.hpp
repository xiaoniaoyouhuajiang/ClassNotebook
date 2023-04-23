#pragma once

#include "GameInterface.hpp"
#include "Field/Field.hpp"

#include "Terrains/GroundTerrain.hpp"
#include "Terrains/StoneTerrain.hpp"
#include "Terrains/WaterTerrain.hpp"
#include "Terrains/ConcreteTerrainFactory.hpp"
#include "Base.hpp"
#include "Things/MedicineThing.hpp"
#include "Things/MicroMedicineThing.hpp"
#include "Things/SmallMedicineThing.hpp"
#include "Things/PowerfulMedicineThing.hpp"

class GameStartRule {
private:
    static constexpr float waterProbability = 0.1f;
    static constexpr float stoneProbability = 0.1f;
    static constexpr float thingProbability = 0.025f;
public:
    static void startNewGame(GameInterface *game, std::shared_ptr<Field> &field, int width, int height) {
        field.reset(new Field(width, height));
        srand(time(0));
        for (auto [cell, position] : *field) {
            auto randomNumber = (float)rand() / RAND_MAX;
            if (randomNumber <= waterProbability) {
                field->setTerrain(std::make_shared<ConcreteTerrainFactory < WaterTerrain>>(), position);
            }
            else if (randomNumber <= waterProbability + stoneProbability) {
                field->setTerrain(std::make_shared<ConcreteTerrainFactory < StoneTerrain>>(), position);
            }
            else if (randomNumber <= waterProbability + stoneProbability + 1 * thingProbability) {
                field->getCell(position)->setThing(std::make_shared<MedicineThing>());
            }
            else if (randomNumber <= waterProbability + stoneProbability + 2 * thingProbability) {
                field->getCell(position)->setThing(std::make_shared<MicroMedicineThing>());
            }
            else if (randomNumber <= waterProbability + stoneProbability + 3 * thingProbability) {
                field->getCell(position)->setThing(std::make_shared<PowerfulMedicineThing>());
            }
            else if (randomNumber <= waterProbability + stoneProbability + 4 * thingProbability) {
                field->getCell(position)->setThing(std::make_shared<SmallMedicineThing>());
            }
        }

        int baseRow = height / 2;
        int baseColOffset = 5;
        field->createBase({baseRow, baseColOffset}, 0);
        field->createBase({baseRow, (width - 1) - baseColOffset}, 1);

        game->setPlayerState(std::make_shared<PlayerState>(0, game));
    }
};