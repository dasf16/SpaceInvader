#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Ship : public sf::Drawable {
public:
    Ship();
    ~Ship();
 



    int getPositionX() const;
    int getPositionY() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(sf::Vector2f setPosition);
    void move(sf::Vector2f newMove);
	void setTexture(std::string newTexture);

	float getSpeed();
	float setSpeed(float newSpeed);

private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture shipTexture;
    sf::Sprite shipSprite;

	float speed = 8;
};


