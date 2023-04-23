#include <memory>

#include "Game.hpp"
#include "Gui/Gui.hpp"

int main() {
    std::shared_ptr<Game> game(new Game);
    std::shared_ptr<Gui> gui(new Gui(game));
    gui->show();
    return 0;
}
