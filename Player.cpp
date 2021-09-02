#include "Player.h"
#include "Game.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;


Player::Player() {
}

Player::~Player() {
}


void Player::moveObject(sf::RenderWindow &window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && getPositionX() > 0)
        move(sf::Vector2f(-getSpeed(), 0.0f));


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && getPositionX() + getGlobalBounds().width <= window.getSize().x)
        move(sf::Vector2f(getSpeed(), 0.0f));
}




