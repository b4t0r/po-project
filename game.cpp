#include "game.h"
#include <iostream>

// Funkcje prywatne
void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 1600;
    this->window = new sf::RenderWindow(this->videoMode, "Baffin: The Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(144);
}

void Game::initPlayer() {
    this->player = new Player();
}

// Konstruktory i dekonstruktory
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initPlayer();
}

Game::~Game() {
    delete this->window; 
    delete this->player; 
}

// Dostępy / Akcesja
const bool Game::getWindowIsOpen() const {
    return this->window->isOpen();
}

// Funkcje

void Game::pollEvents() {
    // Sprawdzanie zdarzeń
    while(this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) this->window->close();
                break;
            case sf::Event::KeyReleased:
                if (
                    this->ev.key.code == sf::Keyboard::A
                    || this->ev.key.code == sf::Keyboard::D
                    || this->ev.key.code == sf::Keyboard::Space
                ) this->player->resetAnimationTimer();
        }
    }
}

void Game::update() {
    this->pollEvents();
    this->updatePlayer();
    this->updateCollison();
}

void Game::render() {
    /*
        @return void
        
        Renderowanie (rysowanie) obiektów gry na ekranie
        1. Czyczenie ekranu
        2. Wyrysowanie obiektów na ekranie
        3. Wyświetlenie klatki na ekranie
     */

    this->window->clear(sf::Color(3, 135, 255, 255));

    // Rysowanie obiektów
    this->renderPlayer();
    this->window->display();
}

void Game::updatePlayer() {
    this->player->update();
}

void Game::renderPlayer() {
    this->player->render(*this->window);
}

void Game::updateCollison() {
    // Kolizja dołu ekranu
    if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height > this->window->getSize().y) {
        this->player->resetVelocityY();
        this->player->setPosition(
            this->player->getGlobalBounds().left,
            this->window->getSize().y - this->player->getGlobalBounds().height
        );
    }
}
