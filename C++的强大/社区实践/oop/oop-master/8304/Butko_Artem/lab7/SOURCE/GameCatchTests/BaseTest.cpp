//
// Created by Artem Butko on 31.05.2020.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../GameLib/Objects/Base/Base.h"

Field* baseTest()
{
    auto field = new Field(10, 10, 1);
    field->createBase(5, 5, 10, 'T', 0);
    return field;
}

TEST_CASE("Base creating test", "[BaseTest]")
{
    auto field = baseTest();
    REQUIRE(field->basesOnField[0]->x == 5);
    REQUIRE(field->basesOnField[0]->y == 5);
    REQUIRE(field->basesOnField[0]->id == 'T');
    REQUIRE(field->basesOnField[0]->gold == 3);
    REQUIRE(field->field[5][5].object == field->field[5][6].object);
}

TEST_CASE("Unit creating test", "[BaseTest]")
{
    auto field = baseTest();
    REQUIRE(field->basesOnField[0]->unitsOnBase.size() == 6);
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    field->basesOnField[0]->createUnit('A');
    REQUIRE(field->basesOnField[0]->unitsOnBase['A'] == field->basesOnField[0]->unitLimit);
}
