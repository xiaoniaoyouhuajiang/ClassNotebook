//
// Created by Artem Butko on 31.05.2020.
//
//
#include "catch.hpp"
#include "../GameLib/GameField/Field/Field.h"

TEST_CASE("Field creating test", "[FieldTest]")
{
    auto field = new Field(5, 5, 2);
    REQUIRE(field->height == 5);
    REQUIRE(field->width == 5);
    REQUIRE(field->basesOnField.size() == 2);
    for (auto & i : field->basesOnField)
        REQUIRE(i == nullptr);
    for (int i = 0; i < field->height; ++i)
        for (int j = 0; j < field->width; ++j)
        {
            REQUIRE(field->field[i][j].object == nullptr);
            REQUIRE(!field->field[i][j].isBrightView);
            REQUIRE(!field->field[i][j].isDarkView);
            REQUIRE(!field->field[i][j].isUndeadView);
            REQUIRE(field->field[i][j].x == i);
            REQUIRE(field->field[i][j].y == j);
        }
}

TEST_CASE("Field copy test", "[FieldTest]")
{
    auto tmp = new Field(5, 5, 2);
    auto field = tmp;
    REQUIRE(field->height == 5);
    REQUIRE(field->width == 5);
    REQUIRE(field->basesOnField.size() == 2);
    for (auto & i : field->basesOnField)
        REQUIRE(i == nullptr);
    for (int i = 0; i < field->height; ++i)
        for (int j = 0; j < field->width; ++j)
        {
            REQUIRE(field->field[i][j].neutral == tmp->field[i][j].neutral);
            REQUIRE(field->field[i][j].landscape == tmp->field[i][j].landscape);
            REQUIRE(field->field[i][j].object == nullptr);
            REQUIRE(!field->field[i][j].isBrightView);
            REQUIRE(!field->field[i][j].isDarkView);
            REQUIRE(!field->field[i][j].isUndeadView);
            REQUIRE(field->field[i][j].x == i);
            REQUIRE(field->field[i][j].y == j);
        }
}