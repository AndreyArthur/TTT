#include "../src/include/game.h"
#include "deps/runner.h"
#include <stdbool.h>

bool test_game_init() {
    Game game = game_init();
    bool is_cleaned = true;

    for (int row = 0; row < GAME_SIZE; row++) {
        for (int column = 0; column < GAME_SIZE; column++) {
            if (game.board[row][column] != ' ') {
                is_cleaned = false;
            }
        }
    }

    return is_cleaned && game.turn == 'X';
}

bool test_game_position_is_empty() {
    Game game = game_init();
    game.board[0][1] = 'X';

    bool empty = game_position_is_empty(&game, 0, 0);
    bool not_empty = game_position_is_empty(&game, 0, 1);

    return empty == true && not_empty == false;
}

bool test_game_insert() {
    Game game = game_init();
    game_insert(&game, 0, 0);
    game_insert(&game, 0, 1);

    return game.board[0][0] == 'X' && game.board[0][1] == 'O';
}

bool test_game_verify_win() {
    Game no = game_init();

    Game x = game_init();
    x.board[0][0] = 'X';
    x.board[0][1] = 'X';
    x.board[0][2] = 'X';

    Game o = game_init();
    o.board[0][0] = 'O';
    o.board[1][0] = 'O';
    o.board[2][0] = 'O';

    Game diagonal = game_init();
    diagonal.board[0][2] = 'O';
    diagonal.board[1][1] = 'O';
    diagonal.board[2][0] = 'O';

    Game draw = game_init();
    draw.board[0][0] = 'O';
    draw.board[0][1] = 'X';
    draw.board[0][2] = 'O';
    draw.board[1][0] = 'X';
    draw.board[1][1] = 'O';
    draw.board[1][2] = 'X';
    draw.board[2][0] = 'X';
    draw.board[2][1] = 'O';
    draw.board[2][2] = 'X';

    return game_verify_win(&no) == ' ' && game_verify_win(&x) == 'X' &&
           game_verify_win(&o) == 'O' && game_verify_win(&diagonal) == 'O' &&
           game_verify_win(&draw) == '=';
}

int main() {
    Runner runner = runner_init("game");
    runner.test("should init with correct values", test_game_init);
    runner.test(
        "should ensure that position is empty", test_game_position_is_empty);
    runner.test("should insert in the position", test_game_insert);
    runner.test("should verify the win", test_game_verify_win);
    return 0;
}
