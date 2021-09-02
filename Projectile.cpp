#include "Projectile.h"
#include "Game.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;

Projectile::Projectile() {
    projectileTexture.loadFromFile("../resources/RedProjectile.png");
    this->projectileSprite.setScale(Vector2f(0.3f, 0.5f));
    this->projectileSprite.setTexture(projectileTexture);
    this->projectileSprite.setPosition(Vector2f(450.f, 2000.f));
}

Projectile::~Projectile() {
}

int Projectile::getPositionX() const {
    return projectileSprite.getPosition().x;
}

int Projectile::getPositionY() const {
    return projectileSprite.getPosition().y;
}

sf::FloatRect Projectile::getGlobalBounds() const {
    return projectileSprite.getGlobalBounds();
}

void Projectile::setPosition(sf::Vector2f setPosition) {
    projectileSprite.setPosition(setPosition);
}

void Projectile::move(sf::Vector2f newMove) {
    projectileSprite.move(newMove);
}

void Projectile::setTexture(sf::String newTexture)
{
	projectileTexture.loadFromFile(newTexture);
	this->projectileSprite.setTexture(projectileTexture);
}

int Projectile::getCanShoot() const {
    return this->canShoot;
}

int Projectile::setCanShoot(int canShoot) {
    this->canShoot = canShoot;

    return canShoot;
}

float Projectile::getCooldown() const {
    return this->cooldown;
}

float Projectile::setCooldown() {
    this->cooldown = cooldown;

    return cooldown;
}

float Projectile::setProjectileSpeed(float newSpeed) {
    this->projectileSpeed = newSpeed;

    return projectileSpeed;
}

float Projectile::getProjectileSpeed() const {
    return projectileSpeed;
}

void Projectile::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    target.draw(projectileSprite, states);
}


