#ifndef INTERFACE_H
#define INTERFACE_H
// Lida com coisas relacionadas à interação com o usuário.

#include "game.h"

/*
 * Estrutura que define a interface.
 *
 * x_player: nome do jogador 'X'
 * o_player: nome do jogador 'O'
 * game: a estrutura do jogo
 */
typedef struct Interface {
    char x_player[32];
    char o_player[32];
    Game game;
} Interface;

Interface interface_init();

void interface_get_names(Interface* interface);

void interface_display_game(Interface* interface);

void interface_make_move(Interface* interface);

bool interface_game_is_over(Interface* interface);

bool interface_ask_new_game(Interface* interface);

#endif
