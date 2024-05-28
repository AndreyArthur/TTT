#include "include/interface.h"
#include "include/game.h"
#include <stdio.h>
#include <string.h>

/*
 * Inicializa a interface, inicializando uma instância do jogo da velha, e
 * adicionando nela.
 */
Interface interface_init() {
    Game game = game_init();
    Interface interface;
    interface.game = game;
    return interface;
}

/*
 * Pede os nomes dos jogadores e adiciona-os na interface.
 *
 * interface: ponteiro para a interface.
 */
void interface_get_names(Interface* interface) {
    printf("Insira o nome do jogador X: ");
    scanf(" %32[^\n]", interface->x_player);

    printf("Insira o nome do jogador O: ");
    scanf(" %32[^\n]", interface->o_player);
}

/*
 * Função que mostra o jogo da velha graficamente.
 *
 * interface: ponteiro para a interface.
 */
void interface_display_game(Interface* interface) {
    printf("\n");

    int row, column;

    // mostra os números das colunas
    printf("   ");
    for (column = 0; column < GAME_SIZE; column++) {
        printf(" %d  ", column);
    }
    printf("\n");

    for (row = 0; row < GAME_SIZE; row++) {
        // mostra o número da linha
        printf(" %d ", row);

        for (column = 0; column < GAME_SIZE; column++) {
            printf(" %c ", interface->game.board[row][column]);

            if (column != GAME_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");

        if (row != GAME_SIZE - 1) {
            printf("   -----------\n");
        }
    }

    printf("\n");
}

/*
 * Função que valida, captura, e insere a jogada na posição.
 *
 * interface: ponteiro para a interface.
 */
void interface_make_move(Interface* interface) {
    // Usando a vez (turn) e o nome do jogador na vez (name).
    char turn = interface->game.turn;
    char name[32];
    if (turn == 'X') {
        strcpy(name, interface->x_player);
    } else {
        strcpy(name, interface->o_player);
    }

    // Define se a posição está ocupada, inicializada como true para entrar
    // no while.
    bool occupied = true;

    while (occupied) {
        // linha e coluna, inicializadas como -1 para entrar nos loops.
        int row = -1, column = -1;

        while (row < 0 || row > 2) {
            printf(
                "%s (%c), escolha a linha que voce quer jogar: ", name, turn);
            scanf("%d", &row);

            if (row < 0 || row > 2) {
                printf("Entrada invalida, precisa estar entre 0 e 2.\n");
            }
        }

        while (column < 0 || column > 2) {
            printf(
                "%s (%c), escolha a coluna que voce quer jogar: ", name, turn);
            scanf("%d", &column);

            if (column < 0 || column > 2) {
                printf("Entrada invalida, precisa estar entre 0 e 2.\n");
            }
        }

        // verifica se a posição está vazia antes de inserir.
        if (game_position_is_empty(&interface->game, row, column)) {
            // se estiver vazia, pode inserir e sair do loop
            occupied = false;
            game_insert(&interface->game, row, column);
        } else {
            printf("Entrada invalida, esta posicao ja esta ocupada.\n");
        }
    }
}

/*
 * Verifica se alguém já ganhou o jogo, se sim, mostra uma mensagem indicando
 * quem ganhou o jogo e retorne true, senão, retorne falso.
 *
 * interface: ponteiro para a interface.
 */
bool interface_game_is_over(Interface* interface) {
    char win = game_verify_win(&interface->game);

    if (win == 'X') {
        printf("Parabens %s, voce venceu!\n", interface->x_player);
        return true;
    } else if (win == 'O') {
        printf("Parabens %s, voce venceu!\n", interface->o_player);
        return true;
    } else if (win == '=') {
        printf("Deu velha! Ninguem ganhou.\n");
        return true;
    }

    return false;
}

/*
 * Pergunta aos jogadores se querem iniciar um novo jogo ou não.
 *
 * interface: ponteiro para a interface.
 */
bool interface_ask_new_game(Interface* interface) {
    // define a escolha (sim ou não)
    char choice = ' ';

    while (choice != 'S' && choice != 'N') {
        printf("Desejam jogar novamente (S/N)? ");
        scanf(" %c", &choice);

        if (choice == 's') {
            choice = 'S';
        } else if (choice == 'n') {
            choice = 'N';
        }
    }

    // se não quiserem jogar, retorna false
    if (choice == 'N') {
        return false;
    }

    // se quiserem pergunte se serão os mesmos jogadores
    choice = ' ';
    while (choice != 'S' && choice != 'N') {
        printf("Sao os mesmos jogadores (S/N)? ");
        scanf(" %c", &choice);

        if (choice == 's') {
            choice = 'S';
        } else if (choice == 'n') {
            choice = 'N';
        }
    }

    // se não forem os mesmos jogadores, peça os nomes novamente
    if (choice == 'N') {
        interface_get_names(interface);
    }

    // inicializa um novo jogo
    interface->game = game_init();

    return true;
}
