//
// Created by smokfyz on 12.04.19.
//

#include <iostream>
#include "../runtime/Game.h"
#include "UI.h"
#include "../impediment/StaticImpediment.h"
#include "../logger/Logger.h"
#include "Ultralight/String.h"

static UI *g_ui = nullptr;

UI::UI(Ref<Window> window) : window_(window) {
    int window_width = App::instance()->window()->width();
    int window_height = App::instance()->window()->height();
    overlay_ = Overlay::Create(window_, window_width, window_height, 0, 0);
    g_ui = this;

    view()->set_load_listener(this);
    view()->LoadURL("file:///field.html");
}

UI::~UI() {
    view()->set_load_listener(nullptr);
    g_ui = nullptr;
}

void UI::OnClose() {
}

void UI::OnResize(int width, int height) {
    RefPtr<Window> window = App::instance()->window();
    overlay_->Resize(window->width(), window->height());
}

void UI::OnDOMReady(ultralight::View* caller) {
    // Set the context for all subsequent JS* calls
    SetJSContext(view()->js_context());

    JSObject global = JSGlobalObject();

    createField = global["createField"];
    renderUnit = global["renderUnit"];
    renderImp = global["renderImp"];
    makeReachable = global["makeReachable"];
    showHexInfo = global["showHexInfo"];
    setLogMode = global["setLogMode"];
    showNextTurn = global["showNextTurn"];
    newGame = global["newGame"];
    endGame = global["endGame"];
    showPickedUnit = global["showPickedUnit"];
    printLogs = global["printLogs"];
    showCreateUnitModal = global["showCreateUnitModal"];
    pickCell = global["pickCell"];
    addUserDefineUnit = global["addUserDefineUnit"];

    global["OnPickHex"] = BindJSCallback(&UI::OnPickHex);
    global["OnNextTurn"] = BindJSCallback(&UI::OnNextTurn);
    global["OnRecreate"] = BindJSCallback(&UI::OnRecreate);
    global["OnClearField"] = BindJSCallback(&UI::OnClearField);
    global["OnNewGame"] = BindJSCallback(&UI::OnNewGame);
    global["OnLogMode"] = BindJSCallback(&UI::OnLogMode);
    global["OnCreateUnit"] = BindJSCallback(&UI::OnCreateUnit);
    global["OnCreateNewUnit"] = BindJSCallback(&UI::OnCreateNewUnit);

    endGame({});

    CreateField();
    RenderField();
}

void UI::OnPickHex(const JSObject& obj, const JSArgs& args) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    unsigned x = args[0].ToInteger();
    unsigned y = args[1].ToInteger();

    game.pickCell(Coord(x, y));

    CreateField();
    RenderField();

    shared_ptr<Cell> current_cell = game.getCurrentCell();

    auto imp_name = current_cell->hasImp() ? current_cell->getImp()->getTypeName() : "None";
    auto unit_name = current_cell->hasUnit() ? current_cell->getUnit()->getTypeName() : "None";

    showHexInfo({ current_cell->getX(), current_cell->getY(), unit_name.c_str(), imp_name.c_str() });

    if(current_cell->hasUnit()) {
        shared_ptr<Unit> unit = current_cell->getUnit();
        showPickedUnit(
                {unit->getAttack(), unit->getRange(), unit->getHealth(), unit->getHealthMax(), unit->getEnergy(),
                 unit->getEnergyMax()});
    }

    if(!!game.getCurrentPlayer()) {
        vector<shared_ptr<Cell>> paths = game.getCurrentPlayer()->getPaths();

        for (auto &cell : paths)
            makeReachable({cell->getX(), cell->getY()});
    }

    Logger &logger = Logger::getLogger();
    printLogs({ logger.read().c_str() });
}

void UI::OnNextTurn(const JSObject &obj, const JSArgs &args) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    game.nextTurn();

    showNextTurn({ game.getCurrentPlayer()->getName().c_str(), game.getNumOfMoves() });

    CreateField();
    RenderField();

    Logger &logger = Logger::getLogger();
    printLogs({ logger.read().c_str() });
}

void UI::OnRecreate(const JSObject &obj, const JSArgs &args) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    int field_size = args[0].ToInteger();
    if( !(field_size > 19 && field_size <= 35) ) field_size = 25;

    if(field_size != field.getSize())
        game.createField(field_size);

    game.getField().clear();
    game.clearPlayers();

    game.createImp(Coord(0, 5), "River");
    game.createImp(Coord(5, 5), "Mountains");
    game.createImp(Coord(15, 5), "Forest");
    game.createImp(Coord(15, 15), "Swamp");
    game.createImp(Coord(19, 19), "Rain");
    game.createImp(Coord(2, 18), "Snow");
    game.createImp(Coord(1, 10), "Fog");

    showNextTurn({ "None", game.getNumOfMoves() });

    endGame({});

    CreateField();
    RenderField();
}

void UI::OnClearField(const JSObject &obj, const JSArgs &args) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    endGame({});

    field.clear();
    CreateField();
    RenderField();
}

void UI::OnNewGame(const JSObject &obj, const JSArgs &args) {

    shared_ptr<Player> p1 = make_shared<Player>("Player 1", "#000000");
    shared_ptr<Player> p2 = make_shared<Player>("Player 2", "#555555");

    Game &game = Game::getGame();
    game.clearPlayers();
    game.resetNumOfMoves();

    game.addPlayer(p1);
    game.addPlayer(p2);

    unsigned size = game.getField().getSize();
    unsigned cord = size / 2;

    game.createUnit(Coord(cord,0), "Archer", p1);
    game.createUnit(Coord(cord + 1,0), "Tank", p1);
    game.createUnit(Coord(cord + 2,0), "Knight", p1);
    game.createUnit(Coord(cord + 3,0), "King", p1);
    game.createUnit(Coord(cord + 4,0), "Priest", p1);
    game.createUnit(Coord(cord + 5,0), "Killer", p1);

    game.createUnit(Coord(cord,size - 1), "Archer", p2);
    game.createUnit(Coord(cord - 1,size - 1), "Tank", p2);
    game.createUnit(Coord(cord - 2,size - 1), "Knight", p2);
    game.createUnit(Coord(cord - 3,size - 1), "King", p2);
    game.createUnit(Coord(cord - 4,size - 1), "Priest", p2);
    game.createUnit(Coord(cord - 5,size - 1), "Killer", p2);

    showNextTurn({ game.getCurrentPlayer()->getName().c_str(), game.getNumOfMoves() });
    newGame({});

    CreateField();
    RenderField();

    Logger &logger = Logger::getLogger();
    printLogs({ logger.read().c_str() });
}

void UI::OnLogMode(const JSObject &obj, const JSArgs &args) {
    Logger &logger = Logger::getLogger();

    bool logging = logger.getLogging();
    bool cached = logger.getCached();

    if(!logging && !cached) {
        logger.loggingMode(true);
        setLogMode({ 1 });
    } else if(logging && !cached) {
        logger.cachedMode(true);
        setLogMode({ 2 });
    } else {
        logger.loggingMode(false);
        logger.cachedMode(false);
        setLogMode({ 3 });
    }
}

void UI::OnCreateUnit(const JSObject &obj, const JSArgs &args) {
    Game &game = Game::getGame();
    Logger &logger = Logger::getLogger();

    shared_ptr<Cell> cur_cell = game.getCurrentCell();

    if(!cur_cell) {
        logger.write("Pick cell before create unit");

        return;
    }

    showCreateUnitModal({});

    int i = 6;
    for(auto &unit : game.getOwnUnits().getOwnUnits()) {
        addUserDefineUnit({ i, unit->getTypeName().c_str() });
        i++;
    }

}

void UI::OnCreateNewUnit(const JSObject &obj, const JSArgs &args) {
    Game &game = Game::getGame();
    Logger &logger = Logger::getLogger();

    shared_ptr<Cell> cur_cell = game.getCurrentCell();

    if(cur_cell->getUnit()) {
        logger.write("Unit already exist in this cell");

        printLogs({ logger.read().c_str() });

        return;
    }


    if(args[0].IsNumber()) {
        int unit_type = args[0].ToInteger();

        switch (unit_type) {
            case 0:
                game.createUnit(Coord(cur_cell->getX(), cur_cell->getY()), "Archer", game.getCurrentPlayer());
                break;
            case 1:
                game.createUnit(Coord(cur_cell->getX(), cur_cell->getY()), "Tank", game.getCurrentPlayer());
                break;
            case 2:
                game.createUnit(Coord(cur_cell->getX(), cur_cell->getY()), "Knight", game.getCurrentPlayer());
                break;
            case 3:
                game.createUnit(Coord(cur_cell->getX(), cur_cell->getY()), "King", game.getCurrentPlayer());
                break;
            case 4:
                game.createUnit(Coord(cur_cell->getX(), cur_cell->getY()), "Priest", game.getCurrentPlayer());
                break;
            case 5:
                game.createUnit(Coord(cur_cell->getX(), cur_cell->getY()), "Killer", game.getCurrentPlayer());
                break;
            default:
                auto &own_units = game.getOwnUnits().getOwnUnits();
                game.createUnit(game.getCurrentCell(), own_units[unit_type - 6], game.getCurrentPlayer());
        }
    } else {
        JSString unit_type = args[0].ToString();
        int attack = args[1].ToInteger();
        int range = args[2].ToInteger();
        int armor = args[3].ToInteger();
        int health = args[4].ToInteger();
        int energy = args[5].ToInteger();
        int style = args[6].ToInteger();

        auto &own_units = game.getOwnUnits();

        string ut{String(unit_type).utf8().data()};

        own_units.createUnit(ut, attack, range, armor, health, energy, style);

        auto player = game.getCurrentPlayer();

        player->addUnit(own_units.getLast());
        player->placeUnit(Coord(game.getCurrentCell()->getX(), game.getCurrentCell()->getY()), own_units.getLast());
    }

    auto own_units = game.getOwnUnits().getOwnUnits();

    showCreateUnitModal({});

    int i = 6;
    for(auto &unit : game.getOwnUnits().getOwnUnits()) {
        addUserDefineUnit({ i, unit->getTypeName().c_str() });
        i++;
    }

    CreateField();
    RenderField();
}

void UI::CreateField() {
    Game &game = Game::getGame();
    Field &field = game.getField();

    createField({ field.getSize() });

}

void UI::RenderField() {
    Game &game = Game::getGame();
    Field &field = game.getField();

    vector<shared_ptr<Impediment>> &imps = game.getImps();
    vector<shared_ptr<Player>> &players = game.getPlayers();

    for(auto &imp : imps) {
        for(auto &cell : imp->getFilled()) {
            std::string s = imp->getTypeName();
            char imp_type[s.size() + 1];
            strcpy(imp_type, s.c_str());
            renderImp({ cell->getX(), cell->getY(), imp_type });
        }
    }

    for(auto &player : players) {
        for(auto &unit : player->getUnits()) {
            std::string s = unit->getTypeName();
            auto unit_type = s.c_str();
            std::string d = player->getColor();
            auto unit_color = d.c_str();
            shared_ptr<Cell> position = unit->getPosition();
            unsigned style = unit->getStyle();
            renderUnit({ position->getX(), position->getY(), unit_type, unit_color, style});
        }
    }

    if(game.getCurrentCell())
        pickCell({game.getCurrentCell()->getX(), game.getCurrentCell()->getY()});

}