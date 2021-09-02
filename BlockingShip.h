#pragma once
#include <string>
#include "Ship.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class BlockingShip : public Ship
{
public:
	BlockingShip();
	~BlockingShip();
	int getBlockingShipHealth();
	void setBlockingShipHealth(int newHealth);
	void takeDamage();

private:

	int blockingShipHealth = 3;
};


