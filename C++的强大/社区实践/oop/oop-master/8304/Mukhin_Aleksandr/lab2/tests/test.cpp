#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Boardfield.h"
#include "Base.h"


TEST_CASE("Test of adding units", "" ) {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    REQUIRE(result);

    result = a.add_unit(b, 0, 5, 1);
    REQUIRE(!result);

    result = a.add_unit(b, 0, 0, 2);
    REQUIRE(!result);

    REQUIRE(b.current_size == 1);
}


TEST_CASE("Test of moving units", "" ) {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    REQUIRE(result);

    result = a.move_unit(0, 0, 4, 3);
    REQUIRE(result);

    result = a.move_unit(4, 3, 0, 0);
    REQUIRE(result);

    result = a.add_unit(b, 1, 4, 4);
    REQUIRE(result);

    result = a.move_unit(1, 4, 0, 0);
    REQUIRE(!result);

    REQUIRE(b.current_size == 2);

    result = a.add_unit(b, 4, 4, 3);
    REQUIRE(!result);

    a.get_boardfield();
}

TEST_CASE("Test of deleting units", "" ) {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    REQUIRE(result);
    REQUIRE(b.current_size == 1);

    result = a.delete_unit(0, 0);
    REQUIRE(result);
    REQUIRE(b.current_size == 0);

    result = a.delete_unit(3, 4);
    REQUIRE(!result);
}

TEST_CASE("Attack", "") {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    result = a.add_unit(b, 0, 1, 3);
    REQUIRE(result);
    REQUIRE(b.current_size == 2);
    result = a.attack(0, 0, 0, 1);
    REQUIRE(!result);
}

TEST_CASE("Add_units", "") {
    Boardfield a(5, 5);
    Base b(6);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_units(b, 5, 3);
    REQUIRE(result);
    REQUIRE(b.current_size == 5);
    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();
}

TEST_CASE("Landscape_action", "") {
    Boardfield a(5, 5);
    Base b(6);

    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 2, 3);
    REQUIRE(result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();

    result = a.add_landscape(0, 2, 0);
    REQUIRE(result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();
}

TEST_CASE("Overload attack between units", "") {
    Boardfield a(5, 5);
    Base b(6);

    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 3);
    result = a.add_unit(b, 0, 1, 3);
    REQUIRE(result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();

    result = a.attack(0, 0, 0, 1);
    REQUIRE(!result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();
}