#include <memory>
#include "Boardfield.h"

template <typename T>
class Game {
private:
    static Game* game;
    std::shared_ptr<T> rule = nullptr;
    Game(std::shared_ptr<T> rule) : rule(rule) {}

public:
    Game(Game&) = delete;
    static Game<T>* get_game(const std::shared_ptr<T> rule);
    void init(Boardfield&, Base&);
    void play(Boardfield&, Base&);
};


template <typename T>
Game<T>* Game<T>::game = nullptr;

template<typename T>
Game<T>* Game<T>::get_game(const std::shared_ptr<T> rule) {
    if (game == nullptr) {
        game = new Game<T>(rule);
    }
    return game;
}

template<typename T>
void Game<T>::init(Boardfield& board, Base& base) {
    board = Boardfield(rule->board_length, rule->board_width);
    base = Base(rule->base_size);

    board.add_base(base, 0, 0);
    board.add_units(base, rule->base_size, 1);
    board.add_landscapes();
}

template<typename T>
void Game<T>::play(Boardfield& board, Base& base) {
    int current_player = rule->first ? 1 : rule->player_count;
    int old_x = -1;
    int old_y = -1;

    int dest_x = -1;
    int dest_y = -1;


    while (base.current_size != 0) {
        std::cout << "\tPlayer " + std::to_string(current_player) + " action:" << std::endl;
        board.get_boardfield();
        std::cout << "Make action from:";
        std::cin >> old_x >> old_y;

        std::cout << "To:";
        std::cin >> dest_x >> dest_y;

        board.move_unit(old_x, old_y, dest_x, dest_y);
        std::cout << std::endl;

        if (current_player == rule->player_count) {
            current_player = 1;
        } else {
            ++current_player;
        }
    }

    if (current_player == 1) {
        if (rule->last_move) {
            std::cout << "Player " << rule->player_count << " win!!!" << std::endl;
        } else {
            std::cout << "Player 1 win!!!" << std::endl;
        }
    } else {
        if (rule->last_move) {
            std::cout << "Player " << --current_player << " win!!!" << std::endl;
        } else {
            std::cout << "Player " << current_player << " win!!!" << std::endl;
        }
    }
}
