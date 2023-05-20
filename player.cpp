#include "player.h"
#include <cmath>
#include <iostream>

void Player::initVariables() {
    this->animState = PLAYER_ANIMATION_STATES::IDLE;
    this->canJump = true;
}

void Player::initTexture()
{
    if (!this->texture.loadFromFile("textures\\main_character_spritesheet.png")) {
        std::cout <<  "ERROR: Cannot load the player's texture!" << std::endl;
    }
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
    this->currentFrame = sf::IntRect(0, 0, 48, 48);
    this->sprite.setScale(2.f, 2.f);
    this->sprite.setTextureRect(this->currentFrame);
}

void Player::initAnimations() {
    this->animationSwitch = true;
    this->animationTimer.restart();
}

void Player::initPhysics() {
    this->velocityMax = 3.f;
	this->velocityMin = 1.f;
	this->acceleration = 3.0f;
	this->drag = 0.93f;
	this->gravity = 2.f;
	this->velocityMaxY = 7.f;  
}

Player::Player()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->initAnimations();
    this->initPhysics();
}

Player::~Player() {

}

void Player::render(sf::RenderTarget & target) {
    target.draw(this->sprite);
}

const bool Player::getAnimSwitch() {
    bool anim_switch = this->animationSwitch;

    if (this->animationSwitch) this->animationSwitch = false;
    return anim_switch;
}

const sf::FloatRect Player::getGlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y) {
    this->sprite.setPosition(x, y);
}

void Player::resetVelocityY() {
    this->velocity.y = 0.f;
}

void Player::resetAnimationTimer() {
    this->animationTimer.restart();
    this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y) {
    // Przyspieszenie
    this->velocity.x += dir_x * this->acceleration;
    this->velocity.y += dir_y * this->gravity;

    // Limit predkosci
    if (std::abs(this->velocity.x) > this->velocityMax) this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
    if (std::abs(this->velocity.y) > this->velocityMaxY) this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);
}

void Player::updatePhysics() {
    this->velocity.y += 1.0 * this->gravity;

    // Deakceleracja
    this->velocity *= this->drag;

    // Limit deakceleracji
    if (std::abs(this->velocity.x) < this->velocityMin) this->velocity.x = 0.f;
    if (std::abs(this->velocity.y) < this->velocityMin) this->velocity.y = 0.f;

    if (std::abs(this->velocity.y) > this->velocityMaxY) this->velocity.y = this->velocityMaxY * ((this->velocity.y < 0.f) ? -1.f : 1.f);

    this->sprite.move(this->velocity);
}

void Player::playerMovement() {
    this->animState = PLAYER_ANIMATION_STATES::IDLE;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->move(1.f, 0.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->move(-1.f, 0.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
    } else if (
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)
        && this->canJump == true
    ) {
        this->move(0.f, -3.f);
        this->canJump = false;
        this->animState = PLAYER_ANIMATION_STATES::JUMPING;
    } else this->animState = PLAYER_ANIMATION_STATES::IDLE;
    
}

void Player::updateAnimations() {
    if (this->animState ==  PLAYER_ANIMATION_STATES::IDLE) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
            this->currentFrame.top = 0.f;
            this->currentFrame.left += 48.f;
            if (this->currentFrame.left >= 480.f) this->currentFrame.left = 0;
            
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    } else if (this->animState ==  PLAYER_ANIMATION_STATES::MOVING_RIGHT) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
            this->currentFrame.top = 96.f;
            this->currentFrame.left += 48.f;
            if (this->currentFrame.left >= 384.f) this->currentFrame.left = 0;
            
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    } else if (this->animState ==  PLAYER_ANIMATION_STATES::MOVING_LEFT) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch()) {
            this->currentFrame.top = 96.f;
            this->currentFrame.left += 48.f;
            if (this->currentFrame.left >= 384.f) this->currentFrame.left = 0;
            
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    } else if (this->animState ==  PLAYER_ANIMATION_STATES::JUMPING) {
        if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch()) {
            this->currentFrame.top = 48.f;
            this->currentFrame.left += 48.f;
            if (this->currentFrame.left >= 144.f) this->currentFrame.left = 0;
            
            this->animationTimer.restart();
            this->sprite.setTextureRect(this->currentFrame);
        }
    } else this->animationTimer.restart();
}

void Player::update()
{
    this->playerMovement();
    this->updateAnimations();
    this->updatePhysics();
}
