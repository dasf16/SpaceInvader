#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "BlockingShip.h"
#include "BonusShip.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

Game::Game()
    : window(sf::VideoMode(1000, 1000), "Space Invaders") {
    createUserInterface();
    createTextures();
    bonusShip.setPosition(Vector2f(1000.f, 70.f));
}

Game::~Game() {
}

void Game::run(Game &game)
{
    srand(time(NULL));
    game.spawnEnemyRow(spawnPointX, spawnPointY);
    game.spawnBlockingShips();
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        window.clear();
        if (healthCount != 0) {
            game.update(game);
        }
        if (healthCount == 0) {
            gameOver();
        }
        draw();
        window.display();
    }
}

void Game::update(Game &game) 
{
    window.setFramerateLimit(60);
    game.moveAliens();
    Defender.moveObject(window);
    game.shoot(game);
    game.spawnBonusShip();

    if (nrOfDeadAliens == 16) {
        // Sets all Aliens speed back to normal //
        for (int i = 0; i < nrOfAliens; i++) {
            Alien[i].setSpeed(1.0f + speedIncrease);
            enemyProjectile[i].setProjectileSpeed(15.0f + roundCount);
            enemyProjectile[i].setPosition(Vector2f(450.f, 2000.f));
        }

        chanceToShoot -= 10;
		doubleSpeed = 1;
        game.spawnEnemyRow(spawnPointX, spawnPointY);

        //Aliens//
        alienCount = 16; //UI
        nrOfDeadAliens = 0; //GameCheck
        ssAlienCount.str("");
        ssAlienCount << "Aliens: " << this->alienCount;
        textAlienCount.setString(ssAlienCount.str());
        //Aliens//

        //Round//
        roundCount += 1;
        speedIncrease += 0.3;
        ssRoundCount.str("");
        ssRoundCount << "Round: " << this->roundCount;
        textRoundCount.setString(ssRoundCount.str());
        //Round//


        currentRow = 0;
    }
    ssHealthCount.str("");
    ssHealthCount << "Health: " << this->healthCount;
    textHealthCount.setString(ssHealthCount.str());

}

void Game::draw() // Draw out all my objects //
{
    window.draw(backgroundSprite);
    for (int i = 0; i < nrOfAliens; i++) {
        window.draw(Alien[i]);
        window.draw(enemyProjectile[i]);
    }
    for (int i = 0; i < nrOfBlockingShips; i++) {
        window.draw(blockingShip[i]);
    }
    window.draw(bonusShip);
    window.draw(playerProjectile);
    window.draw(Defender);
    window.draw(textAlienCount);
    window.draw(textRoundCount);
    window.draw(textHealthCount);
    window.draw(textScoreCount);

    if (healthCount == 0) {
        window.draw(gameOverSprite);
        window.draw(textScoreCount);
        window.draw(textRoundCount);
        window.draw(gameOverText);
        window.draw(restartGameText);
    }

}

void Game::moveAliens()
{	// sets the starting direction //
    for (int i = 0; i < nrOfAliens; i++) {
        if (Alien[i].getPositionX() <= 0) {
            direction = 1;
            row = 1;
        } else if (Alien[i].getPositionX() + Alien[i].getGlobalBounds().width >= window.getSize().x) {
            direction = 0;
            row = 0;
        }
    }
    // tells all Aliens when to go down //
    for (int i = 0; i < nrOfAliens; i++) {
        if (Alien[i].getPositionX() <= 0) {
            row = 0;
        }
    }
    // Halfway down Aliens speed gets doubled //
    if (currentRow == 10) {
        if (doubleSpeed == 1) {
            for (int i = 0; i < nrOfAliens; i++) {
                Alien[i].setSpeed(Alien[i].getSpeed() * 2);
            }
			doubleSpeed = 0;
        }
    }

    // Makes Alien go down //
    if (row == 0 && currentRow != 20) {
        for (int i = 0; i < nrOfAliens; i++) {
            Alien[i].move(sf::Vector2f(0.0f, down));
            row = 1;
        }
        currentRow++;
    }

    // left or right movement //
    if (direction == 0) {
        for (int i = 0; i < nrOfAliens; i++) {
            Alien[i].move(sf::Vector2f(-Alien[i].getSpeed(), 0.0f));
        }
    } else {
        for (int i = 0; i < nrOfAliens; i++) {
            Alien[i].move(sf::Vector2f(Alien[i].getSpeed(), 0.0f));
        }
    }
    // Changes direction //
    for (int i = 0; i < nrOfAliens; i++) {
        if (Alien[i].getPositionX() + Alien[i].getGlobalBounds().width > window.getSize().x) {
            direction = 1;
        }
    }


}

void Game::spawnEnemyRow(float spawnPointX, float spawnPointY)
{
    {
        // Spawns first row //
        for (int i = 0; i < alienRow1; i++) {
            this->Alien[i].setPosition(Vector2f(spawnPointX, spawnPointY));
            spawnPointX += 90;
        }

        spawnPointX = 20;
        spawnPointY = 80;

        // Spawns Second row //
        for (int i = 8; i < alienRow2; i++) {
            this->Alien[i].setPosition(Vector2f(spawnPointX, spawnPointY));
            spawnPointX += 90;
        }

    }
}

void Game::shoot(Game &game)
{
    playerProjectile.setProjectileSpeed(-18);

    //shoot//
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isShot) {
        playerProjectile.setPosition(Vector2f(Defender.getPositionX() + 50, Defender.getPositionY() + 35));
        isShot = true;
    }

    //Projectile Movement
    if (isShot) {
        playerProjectile.move(Vector2f(0.f, playerProjectile.getProjectileSpeed()));
    }

    //Collision
    if (playerProjectile.getPositionY() < 0 - playerProjectile.getPositionY()) {
        isShot = false;
        playerProjectile.setPosition(Vector2f(450.f, 2000.f));
    }

    //Hit An Alien
    for (int i = 0; i < nrOfAliens; i++) {
        if (playerProjectile.getGlobalBounds().intersects(Alien[i].getGlobalBounds())) {
            isShot = false;
            playerProjectile.setPosition(Vector2f(450.f, 2000.f));

            Alien[i].setPosition(Vector2f(500.0f, -2000.0f));
            Alien[i].setSpeed(0.0f);


            if (enemyProjectile[i].getPositionY() > 1000) {
                enemyProjectile[i].setPosition(Vector2f(450.f, -2000.f));
                enemyProjectile[i].setProjectileSpeed(0.0f);
            }

            nrOfDeadAliens++;

            ssScoreCount.str("");
            score += 1 * scoreMultiply;
            ssScoreCount << "Score: " << this->score;
            textScoreCount.setString(ssScoreCount.str());

            ssAlienCount.str("");
            alienCount--;
            ssAlienCount << "Aliens: " << this->alienCount;
            textAlienCount.setString(ssAlienCount.str());

        }
    }

    //Hit a Blockingship//
    for (int i = 0; i < nrOfBlockingShips; i++) {
        if (playerProjectile.getGlobalBounds().intersects(blockingShip[i].getGlobalBounds())) {
            isShot = false;
            playerProjectile.setPosition(Vector2f(450.f, 2000.f));
        }
    }

    //Hit a BonusShip//
    if (playerProjectile.getGlobalBounds().intersects(bonusShip.getGlobalBounds())) {
        playerProjectile.setPosition(Vector2f(450.f, 2000.f));
        bonusShip.setPosition(Vector2f(1000.f, 70.f));
        isShot = false;
        willSpawn = 0;
        ssScoreCount.str("");
        score += 10;
        scoreMultiply++;
        ssScoreCount << "Score: " << this->score;
        textScoreCount.setString(ssScoreCount.str());
    }


    //Enemy Shoot//
    for (int i = 0; i < nrOfAliens; i++) {

        if (canShoot = rand() % 96000 + 1 >= chanceToShoot && enemyProjectile[i].getCanShoot() == 0 && Alien[i].getPositionY() > -1000) {
            enemyProjectile[i].setPosition(Vector2f(Alien[i].getPositionX() + 50, Alien[i].getPositionY() + 35));
            enemyProjectile[i].setCanShoot(1);
        }

        if (enemyProjectile[i].getCanShoot() == 1) {
            enemyProjectile[i].move(Vector2f(0.0f, enemyProjectile[i].getProjectileSpeed()));
        }


        if (enemyProjectile[i].getPositionY() > 1000) {
            enemyProjectile[i].setCanShoot(0);
            enemyProjectile[i].setPosition(Vector2f(450.f, -2000.f));
        }


        if (enemyProjectile[i].getGlobalBounds().intersects(Defender.getGlobalBounds())) {
            enemyProjectile[i].setCanShoot(0);
            enemyProjectile[i].setPosition(Vector2f(450.f, -2000.f));

            //Health//
            ssHealthCount.str("");
            healthCount--;
            ssHealthCount << "Health: " << this->healthCount;
            textHealthCount.setString(ssHealthCount.str());
            //Health//

        }

        //Enemy hits an blockingship//
        for (int j = 0; j < nrOfBlockingShips; j++) {
            if (enemyProjectile[i].getGlobalBounds().intersects(blockingShip[j].getGlobalBounds())) {
                enemyProjectile[i].setCanShoot(0);
                enemyProjectile[i].setPosition(Vector2f(450.f, -2000.f));

                blockingShip[j].takeDamage();

                if (blockingShip[j].getBlockingShipHealth() <= 0) {
                    blockingShip[j].setPosition(Vector2f(450.f, -2000.f));
                }

            }
        }
    }
}

void Game::createUserInterface()
{
    ssAlienCount << "Aliens: " << this->alienCount;
    ssRoundCount << "Round: " << this->roundCount;
    ssHealthCount << "Health: " << this->healthCount;
    ssScoreCount << "Score: " << this->score;

    font.loadFromFile("../resources/arial.ttf");

    //Round//
    textRoundCount.setFont(font);
    textRoundCount.setString(ssRoundCount.str());
    textRoundCount.setCharacterSize(30);
    textRoundCount.setFillColor(sf::Color::Yellow);
    textRoundCount.setPosition(Vector2f(10.f, 0.f));

    //Current Aliens Alive//
    textAlienCount.setFont(font);
    textAlienCount.setString(ssAlienCount.str());
    textAlienCount.setCharacterSize(30);
    textAlienCount.setFillColor(sf::Color::Red);
    textAlienCount.setPosition(Vector2f(850.f, 0.f));
    //Current Aliens Alive//

    //Health//
    textHealthCount.setFont(font);
    textHealthCount.setString(ssHealthCount.str());
    textHealthCount.setCharacterSize(30);
    textHealthCount.setFillColor(sf::Color::Green);
    textHealthCount.setPosition(Vector2f(10.f, 40.f));
    //Health//

    //Score//
    textScoreCount.setFont(font);
    textScoreCount.setString(ssScoreCount.str());
    textScoreCount.setCharacterSize(30);
    textScoreCount.setFillColor(sf::Color::Yellow);
    textScoreCount.setPosition(Vector2f(440.f, 0.f));
    //Score//
}

void Game::createTextures()
{
	string playerTexture = "../resources/Defender.png";
	string invaderTexture = "../resources/Alien.png";
	string bonusShipTexture = "../resources/BonusShip.png";
	string blockingShipTexture = "../resources/BlockingShip.png";
	string playerProjectileTexture = "../resources/GreenProjectile2.png";

	Defender.setTexture(playerTexture);
	bonusShip.setTexture(bonusShipTexture);
	playerProjectile.setTexture(playerProjectileTexture);

	for (int i = 0; i < nrOfAliens; i++)
	{
		Alien[i].setTexture(invaderTexture);
		enemyProjectile[i].setProjectileSpeed(15.0f);
	}

	for (int i = 0; i < nrOfBlockingShips; i++)
	{
		blockingShip[i].setTexture(blockingShipTexture);
	}

	backgroundTexture.loadFromFile("../resources/background.jpg");
	backgroundSprite.setScale(Vector2f(1.3f, 1.7f));
	backgroundSprite.setTexture(backgroundTexture);

	gameOverTexture.loadFromFile("../resources/DestroyedCity.jpg");
	gameOverSprite.setTexture(gameOverTexture);
	gameOverSprite.setScale(Vector2f(1.1f, 2.1f));
}

void Game::gameOver()
{
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(90);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(Vector2f(220.f, 300.f));

    restartGameText.setFont(font);
    restartGameText.setString("Press Escape to quit game \n press the R-key to retry");
    restartGameText.setCharacterSize(35);
    restartGameText.setFillColor(sf::Color::Red);
    restartGameText.setPosition(Vector2f(280.f, 500.f));

    ssScoreCount.str("");
    ssScoreCount << "Final Score: " << this->score;
    textScoreCount.setString(ssScoreCount.str());
    textScoreCount.setPosition(Vector2f(500.f, 430.f));

    ssRoundCount.str("");
    ssRoundCount << "Final round: " << this->roundCount;
    textRoundCount.setString(ssRoundCount.str());
    textRoundCount.setPosition(Vector2f(280.f, 430.f));


    //Restarts the game putting all variables back to deafult//
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && healthCount == 0) {
  

        //Puts all ships to their starting positions//
        for (int i = 0; i < nrOfAliens; i++) {
            Alien[i].setSpeed(1.0f);
            enemyProjectile[i].setProjectileSpeed(15.0f);
            enemyProjectile[i].setPosition(Vector2f(450.f, -2000.f));
            
        }
        for (int i = 0; i < nrOfBlockingShips; i++) {
            blockingShip[i].setBlockingShipHealth(3);
        }
        bonusShip.setPosition(Vector2f(1000.f, 70.f));
        spawnEnemyRow(spawnPointX, spawnPointY);
        spawnBlockingShips();
        Defender.setPosition(Vector2f(450.f, 900.f));
        playerProjectile.setPosition(Vector2f(450.f, 2000.f));
        //Puts all ships to their starting positions//

        textScoreCount.setPosition(Vector2f(440.f, 0.f));
        textRoundCount.setPosition(Vector2f(10.f, 0.f));
		isShot = false;

        chanceToShoot = 32760;
        speedIncrease = 0.3;
        direction = 1;
        row = 1;
        alienCount = 16;
        roundCount = 1;
        currentRow = 0;
        nrOfDeadAliens = 0;
        healthCount = 3;
        score = 0;
        scoreMultiply = 1;


        ssAlienCount.str("");
        ssAlienCount << "Aliens: " << this->alienCount;
        textAlienCount.setString(ssAlienCount.str());

        ssRoundCount.str("");
        ssRoundCount << "Round: " << this->roundCount;
        textRoundCount.setString(ssRoundCount.str());

        ssScoreCount.str("");
        ssScoreCount << "Score: " << this->score;
        textScoreCount.setString(ssScoreCount.str());
    }
}

void Game::spawnBlockingShips()
{
    int spawnPointX = 100;
    int spawnPointY = 750;

    for (int i = 0; i < nrOfBlockingShips; i++) {
        this->blockingShip[i].setPosition(Vector2f(spawnPointX, spawnPointY));
        spawnPointX += 350;
    }
}

void Game::spawnBonusShip()
{

    if (roundCount >= 3) {

        if (bonusShipCooldown != 900) {
            bonusShipCooldown += 1;
        }
        if (bonusShipCooldown == 900) {
            willSpawn = rand() % 100 + 1;
        }

        if (willSpawn >= 50) {
            bonusShip.move(sf::Vector2f(-5.0f, 0.0f));
            bonusShipCooldown = 0;
        }

        if (bonusShip.getPositionX() + bonusShip.getGlobalBounds().width < 0) {
            bonusShip.setPosition(Vector2f(1000.f, 70.f));
            willSpawn = 0;
        }
    }
}
