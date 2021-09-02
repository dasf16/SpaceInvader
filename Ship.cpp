#include "Enemy.h"
#include "Game.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;

Ship::Ship() {
    shipTexture.loadFromFile("../resources/AlienGlasses.png");
    this->shipSprite.setScale(Vector2f(0.3f, 0.3f));
    this->shipSprite.setTexture(shipTexture);
    this->shipSprite.setPosition(Vector2f(450.f, 900.f));
}

Ship::~Ship() {
}

int Ship::getPositionX() const
{
    return shipSprite.getPosition().x;
}

int Ship::getPositionY() const
{
    return shipSprite.getPosition().y;
}

sf::FloatRect Ship::getGlobalBounds() const
{
    return shipSprite.getGlobalBounds();
}

void Ship::setPosition(sf::Vector2f setPosition)
{
    shipSprite.setPosition(setPosition);
}

void Ship::move(sf::Vector2f newMove)
{
    shipSprite.move(newMove);
}

void Ship::setTexture(std::string newTexture)
{
	shipTexture.loadFromFile(newTexture);
	this->shipSprite.setTexture(shipTexture);
}


void Ship::draw(sf::RenderTarget & target, sf::RenderStates states) const 
{
    target.draw(shipSprite, states);
}

float Ship::getSpeed()
{
	return speed;
}

float Ship::setSpeed(float newSpeed)
{
	this->speed = newSpeed;
	return speed;
}
