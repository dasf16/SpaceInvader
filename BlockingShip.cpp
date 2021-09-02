#include "BlockingShip.h"
#include "Game.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;



BlockingShip::BlockingShip()
{
}

BlockingShip::~BlockingShip()
{
}

int BlockingShip::getBlockingShipHealth()
{
	return this->blockingShipHealth;
}

void BlockingShip::setBlockingShipHealth(int newHealth)
{
	this->blockingShipHealth = newHealth;
}

void BlockingShip::takeDamage()
{
	this->blockingShipHealth -= 1;
}
