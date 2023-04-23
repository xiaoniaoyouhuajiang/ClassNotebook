#define CATCH_CONFIG_MAIN

#include "Game.hpp"
#include "Rule.h"
#include "EasyRule.h"
#include "HardRule.h"
#include "ProxyBase.h"
#include "SimpleLogger.h"
#include "ComplexLogger.h"
#include "ProxyBoardfield.h"
#include "catch.hpp"
#include "Boardfield.h"
#include "File.h"
#include "Originator.h"

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

TEST_CASE("Test of adding units via proxy", "" ) {
//    auto simple_log = new SimpleLogger("log.txt");
    auto simple_log = new SimpleLogger();
    std::shared_ptr<ComplexLogger> complex_log = std::make_shared<ComplexLogger>(simple_log);

    Boardfield board(5, 5, complex_log);
    auto proxy_board = std::make_shared<ProxyBoardfield>(board);

    Base base(4);
    bool result = proxy_board->add_base(base, 3, 3);
    REQUIRE(result);

    result = proxy_board->add_unit(base, 0, 0, 0);
    REQUIRE(result);

    result = proxy_board->add_unit(base, 0, 5, 1);
    REQUIRE(!result);

    result = proxy_board->add_unit(base, 0, 0, 2);
    REQUIRE(!result);

    REQUIRE(base.current_size == 1);
    delete simple_log;
}


TEST_CASE("Test of moving units", "") {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    REQUIRE(result);

    result = a.move_unit(0, 0, 4, 3);
    REQUIRE(result);
    a.get_boardfield();
    result = a.move_unit(4, 3, 0, 0);
    REQUIRE(result);
    a.get_boardfield();
    result = a.add_unit(b, 1, 4, 4);
    REQUIRE(result);
    a.get_boardfield();
    result = a.move_unit(1, 4, 0, 0);
    REQUIRE(!result);

    REQUIRE(b.current_size == 2);
    a.get_boardfield();
    result = a.add_unit(b, 4, 4, 3);
    REQUIRE(!result);

    a.get_boardfield();
}

TEST_CASE("Test of moving units via proxy", "") {
    std::shared_ptr<SimpleLogger> log = std::make_shared<SimpleLogger>("logs.txt");
    Boardfield a(5, 5, log);
    auto proxy_board = std::make_shared<ProxyBoardfield>(a);
    Base b(2);

    bool result = proxy_board->add_base(b, 3, 3);
    REQUIRE(result);

    result = proxy_board->add_unit(b, 0, 0, 0);
    REQUIRE(result);

    result = proxy_board->move_unit(0, 0, 4, 3);
    REQUIRE(result);

    result = proxy_board->move_unit(4, 3, 0, 0);
    REQUIRE(result);

    result = proxy_board->add_unit(b, 1, 4, 4);
    REQUIRE(result);

    result = proxy_board->move_unit(1, 4, 0, 0);
    REQUIRE(!result);
}


TEST_CASE("Test of deleting units", "") {
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

TEST_CASE("Test of deleting units via proxy", "") {
    auto simple_log = new SimpleLogger("logs.txt");
    std::shared_ptr<ComplexLogger> complex_log = std::make_shared<ComplexLogger>(simple_log);
    Boardfield a(5, 5, complex_log);
    auto proxy_board = std::make_shared<ProxyBoardfield>(a);
    Base b(2);

    bool result = proxy_board->add_base(b, 3, 3);
    REQUIRE(result);

    result = proxy_board->add_unit(b, 0, 0, 0);
    REQUIRE(result);
    REQUIRE(b.current_size == 1);

    result = proxy_board->delete_unit(0, 0);
    REQUIRE(result);
    REQUIRE(b.current_size == 0);

    result = proxy_board->delete_unit(3, 4);
    REQUIRE(!result);
    delete simple_log;
}


TEST_CASE("Base attack", "") {
    Boardfield a(5, 5);
    Base b(6);

    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 3);
    REQUIRE(result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();

    result = a.attack(3, 3, 0, 0, "base action");
    REQUIRE(result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();
}

TEST_CASE("Base attack via proxy", "") {
    auto simple_logger = new SimpleLogger();
    auto complex_logger = std::make_shared<ComplexLogger>(simple_logger);
    Boardfield a(5, 5, complex_logger);
//    auto proxy_board = new ProxyBoardfield(a);
    std::shared_ptr<ProxyBoardfield> proxy_board = std::make_shared<ProxyBoardfield>(a);
    Base b(6);

    bool result = proxy_board->add_base(b, 3, 3);
    REQUIRE(result);

    result = proxy_board->add_unit(b, 0, 0, 3);
    REQUIRE(result);

    result = proxy_board->attack(3, 3, 0, 0, "base action");
    REQUIRE(result);
    delete simple_logger;
}


TEST_CASE("Attack", "") {
    Boardfield a(5, 5);
    Base b(2);
    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 0, 0);
    REQUIRE(result);

    result = a.add_unit(b, 0, 1, 3);
    REQUIRE(result);
    REQUIRE(b.current_size == 2);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();

    result = a.attack(0, 0, 0, 1, "unit action");
    REQUIRE(result);

    result = a.attack(3, 3, 0, 1, "base action");
    REQUIRE(!result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();
}

TEST_CASE("Attack via proxy", "") {
    std::shared_ptr<SimpleLogger> log = std::shared_ptr<SimpleLogger>();
    Boardfield board(5, 5, log);
    std::shared_ptr<ProxyBoardfield> proxy_board = std::make_shared<ProxyBoardfield>(board);
    Base base(4);

    bool result = proxy_board->add_base(base, 3, 3);
    REQUIRE(result);

    result = proxy_board->add_unit(base, 0, 0, 0);
    REQUIRE(result);

    result = proxy_board->add_unit(base, 0, 1, 3);
    REQUIRE(result);
    REQUIRE(base.current_size == 2);

    result = proxy_board->attack(0, 0, 0, 1, "unit action");
    REQUIRE(result);

    result = proxy_board->attack(3, 3, 0, 1, "base action");
    REQUIRE(!result);
}


TEST_CASE("Safe state to file", "") {
    auto simple_log = new SimpleLogger();
    std::shared_ptr<ComplexLogger> complex_log = std::make_shared<ComplexLogger>(simple_log);

    Boardfield board(5, 8, complex_log);
    auto proxy_board = new ProxyBoardfield(board);
    proxy_board->add_landscapes();
    Base base(4);

    Originator* originator = new Originator(proxy_board, &base);
    File* file = new File(originator->save());

    proxy_board->add_base(base, 3, 3);
    proxy_board->add_unit(base, 0, 0, 0);
    proxy_board->add_unit(base, 0, 5, 1);
    proxy_board->add_unit(base, 0, 2, 2);
    proxy_board->add_neutral_object(0, 1, 2);
    REQUIRE(base.current_size == 3);

    originator->load(file->get_save());
    REQUIRE(base.current_size == 0);
    delete simple_log;
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

TEST_CASE("Neutral object action", "") {
    Boardfield a(5, 5);
    Base b(6);

    bool result = a.add_base(b, 3, 3);
    REQUIRE(result);

    result = a.add_unit(b, 0, 2, 3);
    REQUIRE(result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();

    result = a.add_neutral_object(0, 2, 0);
    REQUIRE(result);

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
    result = a.add_unit(b, 0, 1, 0);
    REQUIRE(result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();
    result = a.attack(0, 0, 0, 1, "unit action");
    REQUIRE(result);

    b.get_base();
    std::cout << std::endl;
    a.get_boardfield();
}

TEST_CASE("Easy rules", "") {
    std::shared_ptr<Rule> rule = std::make_shared<EasyRule>();
    Game<Rule>* game = Game<Rule>::get_game(rule);
    Boardfield a;
    Base b;
    game->init(a, b);
    game->play(a, b);
}

TEST_CASE("Hard rules", "") {
    std::shared_ptr<Rule> rule = std::make_shared<HardRule>();
    Game<Rule>* game = Game<Rule>::get_game(rule);
    Boardfield a;
    Base b;
    game->init(a, b);
    game->play(a, b);
}