#pragma once
#include <string>
#include <sstream>
#include "Enemy.h"
#include "Player.h"
#include "BlockingShip.h"
#include "BonusShip.h"
#include "Projectile.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Game {

public:
    Game();
    ~Game();


    void run(Game &game);
    void update(Game &game);
    void draw();

    void moveAliens();
    void spawnEnemyRow(float spawnPointX, float spawnPointY);
    void shoot(Game &game);
    void createUserInterface();
    void createTextures();
    void gameOver();
    void spawnBlockingShips();
    void spawnBonusShip();

private:

    sf::RenderWindow window;
    
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture gameOverTexture;
    sf::Sprite gameOverSprite;

    //Text and Font//
    sf::Font font;
    sf::Text textAlienCount;
    sf::Text textRoundCount;
    sf::Text textHealthCount;
    sf::Text textScoreCount;
    sf::Text gameOverText;
    sf::Text restartGameText;
    int roundCount = 1;
    int alienCount = 16;
    int healthCount = 3;
    int score = 0;
    std::ostringstream ssRoundCount;
    std::ostringstream ssAlienCount;
    std::ostringstream ssHealthCount;
    std::ostringstream ssScoreCount;
    //Text and Font//

    Enemy Alien[16];
    Player Defender;
    Projectile playerProjectile;
    Projectile enemyProjectile[16];
    BlockingShip blockingShip[3];
    const int nrOfBlockingShips = 3;
    BonusShip bonusShip;



    const int nrOfAliens = 16;
    float nrOfDeadAliens = 0;

    float speedIncrease = 1.6;

    int chanceToShoot = 32760;

    int direction = 1;
    const int down = 30;
    int row = 1;
    int currentRow = 0;
    int doubleSpeed = 1;

    const int alienRow1 = 8;
    const int alienRow2 = 16;

    float spawnPointX = 20;
    float spawnPointY = 10;

    //Enemy Shoot//
    bool isShot = false;
    int canShoot = 0;
    float cooldown = 0;
    //Enemy Shoot//

    //BounsShip//
    int bonusShipCooldown = 0;
    int willSpawn = 0;
    int scoreMultiply = 1;
    //BounsShip//
};
