#include <iostream>
#include "game.h"

int main() {
    // Inizjalizacja silnika gry
    Game game;

    // Pętla gry

    while (game.getWindowIsOpen()) {
        // Update
        game.update();
        // Render
        game.render();
    }

    return 0;
}
