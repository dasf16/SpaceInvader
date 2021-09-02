#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Projectile : public sf::Drawable {
public:
    Projectile();
    ~Projectile();
    

    int getPositionX() const;
    int getPositionY() const;
    sf::FloatRect getGlobalBounds() const;
    void setPosition(sf::Vector2f setPosition);
    void move(sf::Vector2f newMove);
	void setTexture(sf::String newTexture);

    int getCanShoot() const;
    int setCanShoot(int canShoot);
    float getCooldown() const;
    float setCooldown();
    float setProjectileSpeed(float newSpeed);
    float getProjectileSpeed() const;


private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float projectileSpeed = 15.0;
    int canShoot = 0;
    float cooldown = 0;

    sf::Texture projectileTexture;
    sf::Sprite projectileSprite;
};

