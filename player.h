#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING};

class Player {
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Clock animationTimer;
        bool canJump;

        // Rdzeń postaci
        void initVariables();
        void initTexture();
        void initSprite();
        void initAnimations();
        void initPhysics();

        // Fizyka
        sf::Vector2f velocity;
        float acceleration;
        float drag;
        float velocityMax;
        float velocityMin;
        float gravity;
        float velocityMaxY;

        // Animacja
        short animState;
        sf::IntRect currentFrame;
        bool animationSwitch;

        // Poruszanie

        // Charakterystyka
    public:
        Player();
        virtual ~Player();

        // Dostępy
        const bool getAnimSwitch();
        const sf::FloatRect getGlobalBounds() const;

        // Modyfikatory
        void setPosition(const float x, const float y);
        void resetVelocityY();

        // Funkcje
        void resetAnimationTimer();
        void move(const float dir_x, const float dir_y);
        void updatePhysics();
        void update();
        void render(sf::RenderTarget & target);
        void playerMovement();
        void updateAnimations();
};