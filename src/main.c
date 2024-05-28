#include "include/interface.h"

int main() {
    // inicializa a interface.
    Interface interface = interface_init();

    // pede os nomes dos jogadores
    interface_get_names(&interface);

    // mostra o jogo
    interface_display_game(&interface);

    while (1) {
        // faz a jogada
        interface_make_move(&interface);

        // mostra o jogo
        interface_display_game(&interface);

        // se o jogo tiver acabado, pergunta se quer jogar novamente
        // se não quiser, sai do programa.
        if (interface_game_is_over(&interface)) {
            bool new_game = interface_ask_new_game(&interface);

            if (new_game == false) {
                return 0;
            }
        }
    }

    return 0;
}
