#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "player.h"

/* 
    Ta klasa będzie zachowywała się jak silnik gry
*/

class Game {
    private:
        // Zmienne
        // Okno
        sf::RenderWindow*  window; // Wskaźnik jest po to, aby dynamiczne alokować okno gry, ponieważ możemy chcieć takie okno usunąć
        sf::VideoMode videoMode;
        sf::Event ev;

        Player* player;

        // Funkcje prywatne
        void initVariables();
        void initWindow();
        void initPlayer();

    public:
        // Kontruktory & Destruktory
        Game();
        virtual ~Game();

        // Dostęp
        const bool getWindowIsOpen() const;

        // Funkcje
        void pollEvents();
        void update();
        void render();
        void updatePlayer();
        void renderPlayer();
        void updateCollison();
};