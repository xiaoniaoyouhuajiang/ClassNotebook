#ifndef LAB2_RULE_H
#define LAB2_RULE_H


class Rule {
public:
    Rule(int board_length, int board_width, int base_size, bool last_move, bool first, int player_count) :
    board_length(board_length), board_width(board_width), base_size(base_size), last_move(last_move), first(first), player_count(player_count) {}
    int board_length;
    int board_width;
    int base_size;
    int player_count;

    bool last_move;
    bool first;
};


#endif
