#include "game.h"

template <>
Player_state<Easy_rule> *Player1_state<Easy_rule>::next_player(bool hard){
    return new Player2_state<Easy_rule>(rule);
}

template <>
Player_state<Easy_rule> *Player2_state<Easy_rule>::next_player(bool hard){
    if (hard)
        return new Player3_state<Easy_rule>(rule);
    else {
        return new Player1_state<Easy_rule>(rule);
    }
}

template <>
Player_state<Easy_rule> *Player3_state<Easy_rule>::next_player(bool hard){
    return new Player1_state<Easy_rule>(rule);
}

template <>
Player_state<Hard_rule> *Player1_state<Hard_rule>::next_player(bool hard){
    return new Player2_state<Hard_rule>(rule);
}

template <>
Player_state<Hard_rule> *Player2_state<Hard_rule>::next_player(bool hard){
    if (hard)
        return new Player3_state<Hard_rule>(rule);
    else {
        return new Player1_state<Hard_rule>(rule);
    }
}
template <>
Player_state<Hard_rule> *Player3_state<Hard_rule>::next_player(bool hard){
    return new Player1_state<Hard_rule>(rule);
}

