#include "Enemy.h"
#include "Game.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;

Enemy::Enemy() 
{
	setSpeed(1.0f);
}

Enemy::~Enemy() 
{
}

