#pragma once
#include <string>
#include "Ship.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Player : public Ship {
public:
    Player();
    ~Player();

    void moveObject(sf::RenderWindow &window); 
                                               
private:

};


