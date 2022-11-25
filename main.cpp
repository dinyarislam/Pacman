/*
Author: Dinyar Islam
Class: ECE4122
        Last Date Modified: 26 October 2022

Description: Lab 3

What is the purpose of this file?
Application that uses SFML to create a simple pacman game.
*/

#include <sstream>
#include <SFML/Graphics.hpp>
#include "iostream"
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

// speed of pacman
const int PACMAN_SPEED = 120;
const int GHOST_SPEED = 1500;

// ghost class
class Ghost
{
public:
    Sprite ghostType; // type of ghost
    int ghostDir; // direction of motion
    int lastPosGhost_x;
    int lastPosGhost_y;
    bool reverse = false; // is pacman powered up
    // constructor
    Ghost(){}
};

// main function that uses SFML to create a simple pacman game.
int main() {
    // Create a video mode object
    VideoMode vm(645, 730);

    // Create and open a window for the game
    RenderWindow window(vm, "Pacman");

    // Create a texture to hold a graphic on the GPU
    Texture textureBackground;

    // Load a graphic into the texture
    textureBackground.loadFromFile("../graphics/maze.bmp");

    // Create a sprite
    Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);

    // Start Text
    Text startText;
    Font font;
    font.loadFromFile("../fonts/KOMIKAP_.ttf");
    startText.setFont(font);
    startText.setString("PRESS ENTER TO START");
    startText.setCharacterSize(40);
    startText.setPosition(80, 300);

    // Score text
    int score = 0;
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(std::to_string(score));
    scoreText.setCharacterSize(32);
    scoreText.setPosition(142, 673);

    // Game Over Text
    Text endText;
    endText.setFont(font);
    endText.setString("GAME OVER");
    endText.setCharacterSize(60);
    endText.setPosition(153, 300);

    // Make the pink ghost sprite
    Texture texturePinkGhost;
    texturePinkGhost.loadFromFile("../graphics/pink_ghost.bmp");
    Sprite spritePinkGhost;
    spritePinkGhost.setTexture(texturePinkGhost);
    spritePinkGhost.setScale(0.8,0.8);
    spritePinkGhost.setPosition(304, 248);

    // Make the orange ghost sprite
    Texture textureOrangeGhost;
    textureOrangeGhost.loadFromFile("../graphics/orange_ghost.bmp");
    Sprite spriteOrangeGhost;
    spriteOrangeGhost.setTexture(textureOrangeGhost);
    spriteOrangeGhost.setScale(0.8,0.8);
    spriteOrangeGhost.setPosition(304, 248);

    // Make the blue ghost sprite
    Texture textureBlueGhost;
    textureBlueGhost.loadFromFile("../graphics/blue_ghost.bmp");
    Sprite spriteBlueGhost;
    spriteBlueGhost.setTexture(textureBlueGhost);
    spriteBlueGhost.setScale(0.8,0.8);
    spriteBlueGhost.setPosition(304, 248);

    // Make the red ghost sprite
    Texture textureRedGhost;
    textureRedGhost.loadFromFile("../graphics/red_ghosts.bmp");
    Sprite spriteRedGhost;
    spriteRedGhost.setTexture(textureRedGhost);
    spriteRedGhost.setScale(0.8,0.8);
    spriteRedGhost.setPosition(304, 248);

    // Make the pacman sprite
    Texture texturePacman;
    texturePacman.loadFromFile("../graphics/pacman.bmp");
    Sprite spritePacman;
    spritePacman.setTexture(texturePacman);
    spritePacman.setScale(0.8, 0.8);
    spritePacman.setPosition(304, 492);

    // create ghost classes
    Ghost blueGhost;
    blueGhost.ghostType = spriteBlueGhost;
    blueGhost.ghostDir = 1;
    Ghost redGhost;
    redGhost.ghostType = spriteRedGhost;
    redGhost.ghostDir = 2;
    Ghost orangeGhost;
    orangeGhost.ghostType = spriteOrangeGhost;
    orangeGhost.ghostDir = 1;
    Ghost pinkGhost;
    pinkGhost.ghostType = spritePinkGhost;
    pinkGhost.ghostDir = 2;

    // Make powerup sprites
    CircleShape powerup[4];
    for (int i = 0; i < 4; i++) {
        powerup[i].setRadius(7.f);
        powerup[i].setFillColor(sf::Color::White);
    }
    powerup[0].setPosition(57.f, 94.f);
    powerup[1].setPosition(568.f, 94.f);
    powerup[2].setPosition(57.f, 503.f);
    powerup[3].setPosition(568.f, 503.f);

    // Make coin sprites
    // temp coin for initializing

    std::vector<CircleShape> coins;
    CircleShape coin[458];
    int index = 0;
    int row;
    int col = 0;
    for (int i = 62; i <= 292; i = i + 20) {
        row = 0;
        for (int j = 60; j <= 200; j = j + 20) {
            coin[index].setPosition(0, 0);
            if (col > 0 && col < 5 && (row == 1 || row == 2 || row == 3 || row == 5 || row == 6)) {
                coin[index].setFillColor(sf::Color::Transparent);
            } else if (col >= 6 && col <= 10 && (row == 1 || row == 2 || row == 3)) {
                coin[index].setFillColor(sf::Color::Transparent);
            } else if ((row >= 5 && col > 5 && col != 8) && !(row == 7 && col >= 9)) {
                coin[index].setFillColor(sf::Color::Transparent);
            } else {
                coin[index].setFillColor(sf::Color::White);
                coin[index].setPosition(i, j);
            }
            coin[index].setRadius(2.f);
            //coin[index].setFillColor(sf::Color::White);
            //coin[index].setPosition(i, j);
            index++;
            if (row == 4 && col == 11) {
                coin[index].setFillColor(sf::Color::White);
                coin[index].setRadius(2.f);
                coin[index].setPosition(i + 23, j);
                index++;
                coin[index].setFillColor(sf::Color::White);
                coin[index].setRadius(2.f);
                coin[index].setPosition(i + 46, j);
                index++;
            }
            row++;
        }
        col++;
    }
    int temp_i = 162;
    for (int j = 220; j <= 439; j = j + 21) {
        coin[index].setRadius(2.f);
        coin[index].setFillColor(sf::Color::White);
        coin[index].setPosition(temp_i, j);
        index++;
    }
    col = 0;
    for (int i = 352; i <= 585; i = i + 20) {
        row = 0;
        for (int j = 60; j <= 200; j = j + 20) {
            coin[index].setPosition(0, 0);
            if (col >= 7 && col <= 10 && (row == 1 || row == 2 || row == 3 || row == 5 || row == 6)) {
                coin[index].setFillColor(sf::Color::Transparent);
            } else if (col >= 1 && col <= 5 && (row == 1 || row == 2 || row == 3)) {
                coin[index].setFillColor(sf::Color::Transparent);
            } else if ((row >= 5) && (col < 6) && (col != 3) && !(row == 7 && col >= 0 && col <= 2)) {
                coin[index].setFillColor(sf::Color::Transparent);
            } else {
                coin[index].setFillColor(sf::Color::White);
                coin[index].setPosition(i, j);
            }
            coin[index].setRadius(2.f);
            //coin[index].setFillColor(sf::Color::White);
            //coin[index].setPosition(i, j);
            index++;
            row++;
        }
        col++;
    }
    temp_i = 472;
    for (int j = 220; j <= 439; j = j + 21) {
        coin[index].setRadius(2.f);
        coin[index].setFillColor(sf::Color::White);
        coin[index].setPosition(temp_i, j);
        index++;
    }
    col = 0;
    for (int i = 62; i <= 292; i = i + 20) {
        row = 0;
        for (int j = 450; j <= 640; j = j + 20) {
            coin[index].setPosition(0, 0);
            if (row >= 1 && row <= 2 && ((col >= 1 && col <= 4) || (col >= 6 && col <= 10)))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else if (row == 3 && (col == 3 || col == 4))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else if (row >= 4 && row <= 5 &&
                       ((col == 0 || col == 1) || (col == 3 || col == 4) || (col == 6 || col == 7) ||
                        (col >= 9 && col <= 11)))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else if (row == 6 && (col == 6 || col == 7))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else if (row >= 7 && row <= 8 && ((col >= 1 && col <= 10)))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else
            {
                coin[index].setFillColor(sf::Color::White);
                coin[index].setPosition(i, j);
            }
            coin[index].setRadius(2.f);
            index++;
            if (row == 9 && col == 11) {
                coin[index].setFillColor(sf::Color::White);
                coin[index].setRadius(2.f);
                coin[index].setPosition(i + 23, j);
                index++;
                coin[index].setFillColor(sf::Color::White);
                coin[index].setRadius(2.f);
                coin[index].setPosition(i + 46, j);
                index++;
            }
            row++;
        }
        col++;
    }
    col = 0;
    for (int i = 352; i <= 585; i = i + 20) {
        row = 0;
        for (int j = 450; j <= 640; j = j + 20) {
            coin[index].setPosition(0, 0);
            if (row >= 1 && row <= 2 && ((col >= 1 && col <= 5) || (col >= 7 && col <= 10)))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else if (row == 3 && (col == 7 || col == 8))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else if (row >= 4 && row <= 5 &&
                       ((col == 10 || col == 11) || (col == 7 || col == 8) || (col == 4 || col == 5) ||
                        (col >= 0 && col <= 2)))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else if (row == 6 && (col == 4 || col == 5))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else if (row >= 7 && row <= 8 && ((col >= 1 && col <= 10)))
            {
                coin[index].setFillColor(sf::Color::Transparent);
            }
            else
            {
                coin[index].setFillColor(sf::Color::White);
                coin[index].setPosition(i, j);
            }
            coin[index].setRadius(2.f);
            index++;
            row++;
        }
        col++;
    }
    std::cout << index << "\n";
    for (int i = 0; i < index; i++)
    {
        coins.push_back(coin[i]);
    }

    // Make invisible barriers
    std::vector<RectangleShape> barriers;
    RectangleShape barrier1;
    barrier1.setSize(Vector2f(61, 40));
    barrier1.setFillColor(Color::Transparent);
    barrier1.setPosition(83, 78);
    barriers.push_back(barrier1);
    RectangleShape barrier2;
    barrier2.setSize(Vector2f(81, 40));
    barrier2.setFillColor(Color::Transparent);
    barrier2.setPosition(185, 78);
    barriers.push_back(barrier2);
    RectangleShape barrier3;
    barrier3.setSize(Vector2f(81, 40));
    barrier3.setFillColor(Color::Transparent);
    barrier3.setPosition(370, 78);
    barriers.push_back(barrier3);
    RectangleShape barrier4;
    barrier4.setSize(Vector2f(62, 41));
    barrier4.setFillColor(Color::Transparent);
    barrier4.setPosition(492, 77);
    barriers.push_back(barrier4);
    RectangleShape barrier5;
    barrier5.setSize(Vector2f(11, 650));
    barrier5.setFillColor(Color::Transparent);
    barrier5.setPosition(31, 18);
    barriers.push_back(barrier5);
    RectangleShape barrier6;
    barrier6.setSize(Vector2f(11, 650));
    barrier6.setFillColor(Color::Transparent);
    barrier6.setPosition(595, 18);
    barriers.push_back(barrier6);
    RectangleShape barrier7;
    barrier7.setSize(Vector2f(600, 11));
    barrier7.setFillColor(Color::Transparent);
    barrier7.setPosition(20, 26);
    barriers.push_back(barrier7);
    RectangleShape barrier8;
    barrier8.setSize(Vector2f(600, 11));
    barrier8.setFillColor(Color::Transparent);
    barrier8.setPosition(20, 651);
    barriers.push_back(barrier8);
    RectangleShape barrier9;
    barrier9.setSize(Vector2f(62, 20));
    barrier9.setFillColor(Color::Transparent);
    barrier9.setPosition(82, 161);
    barriers.push_back(barrier9);
    RectangleShape barrier10;
    barrier10.setSize(Vector2f(62, 20));
    barrier10.setFillColor(Color::Transparent);
    barrier10.setPosition(492, 161);
    barriers.push_back(barrier10);
    RectangleShape barrier11;
    barrier11.setSize(Vector2f(144, 20));
    barrier11.setFillColor(Color::Transparent);
    barrier11.setPosition(246, 160);
    barriers.push_back(barrier11);
    RectangleShape barrier12;
    barrier12.setSize(Vector2f(62, 20));
    barrier12.setFillColor(Color::Transparent);
    barrier12.setPosition(82, 467);
    barriers.push_back(barrier12);
    RectangleShape barrier13;
    barrier13.setSize(Vector2f(62, 20));
    barrier13.setFillColor(Color::Transparent);
    barrier13.setPosition(492, 467);
    barriers.push_back(barrier13);
    RectangleShape barrier14;
    barrier14.setSize(Vector2f(144, 20));
    barrier14.setFillColor(Color::Transparent);
    barrier14.setPosition(246, 405);
    barriers.push_back(barrier14);
    RectangleShape barrier15;
    barrier15.setSize(Vector2f(144, 20));
    barrier15.setFillColor(Color::Transparent);
    barrier15.setPosition(246, 528);
    barriers.push_back(barrier15);
    RectangleShape barrier16;
    barrier16.setSize(Vector2f(82, 20));
    barrier16.setFillColor(Color::Transparent);
    barrier16.setPosition(185, 467);
    barriers.push_back(barrier16);
    RectangleShape barrier17;
    barrier17.setSize(Vector2f(82, 20));
    barrier17.setFillColor(Color::Transparent);
    barrier17.setPosition(370, 467);
    barriers.push_back(barrier17);
    RectangleShape barrier18;
    barrier18.setSize(Vector2f(82, 20));
    barrier18.setFillColor(Color::Transparent);
    barrier18.setPosition(370, 221);
    barriers.push_back(barrier18);
    RectangleShape barrier19;
    barrier19.setSize(Vector2f(82, 20));
    barrier19.setFillColor(Color::Transparent);
    barrier19.setPosition(185, 221);
    barriers.push_back(barrier19);
    RectangleShape barrier20;
    barrier20.setSize(Vector2f(21, 82));
    barrier20.setFillColor(Color::Transparent);
    barrier20.setPosition(185, 221);
    barriers.push_back(barrier20);
    RectangleShape barrier21;
    barrier21.setSize(Vector2f(21, 82));
    barrier21.setFillColor(Color::Transparent);
    barrier21.setPosition(431, 221);
    barriers.push_back(barrier21);
    RectangleShape barrier22;
    barrier22.setSize(Vector2f(21, 82));
    barrier22.setFillColor(Color::Transparent);
    barrier22.setPosition(185, 345);
    barriers.push_back(barrier22);
    RectangleShape barrier23;
    barrier23.setSize(Vector2f(21, 82));
    barrier23.setFillColor(Color::Transparent);
    barrier23.setPosition(431, 345);
    barriers.push_back(barrier23);
    RectangleShape barrier24;
    barrier24.setSize(Vector2f(21, 82));
    barrier24.setFillColor(Color::Transparent);
    barrier24.setPosition(185, 530);
    barriers.push_back(barrier24);
    RectangleShape barrier25;
    barrier25.setSize(Vector2f(21, 82));
    barrier25.setFillColor(Color::Transparent);
    barrier25.setPosition(431, 530);
    barriers.push_back(barrier25);
    RectangleShape barrier26;
    barrier26.setSize(Vector2f(21, 82));
    barrier26.setFillColor(Color::Transparent);
    barrier26.setPosition(185, 161);
    barriers.push_back(barrier26);
    RectangleShape barrier27;
    barrier27.setSize(Vector2f(21, 82));
    barrier27.setFillColor(Color::Transparent);
    barrier27.setPosition(431, 161);
    barriers.push_back(barrier27);
    RectangleShape barrier28;
    barrier28.setSize(Vector2f(21, 80));
    barrier28.setFillColor(Color::Transparent);
    barrier28.setPosition(308, 530);
    barriers.push_back(barrier28);
    RectangleShape barrier29;
    barrier29.setSize(Vector2f(21, 80));
    barrier29.setFillColor(Color::Transparent);
    barrier29.setPosition(308, 405);
    barriers.push_back(barrier29);
    RectangleShape barrier30;
    barrier30.setSize(Vector2f(21, 80));
    barrier30.setFillColor(Color::Transparent);
    barrier30.setPosition(308, 160);
    barriers.push_back(barrier30);
    RectangleShape barrier31;
    barrier31.setSize(Vector2f(21, 80));
    barrier31.setFillColor(Color::Transparent);
    barrier31.setPosition(308, 35);
    barriers.push_back(barrier31);
    RectangleShape barrier32;
    barrier32.setSize(Vector2f(21, 81));
    barrier32.setFillColor(Color::Transparent);
    barrier32.setPosition(123, 467);
    barriers.push_back(barrier32);
    RectangleShape barrier33;
    barrier33.setSize(Vector2f(21, 81));
    barrier33.setFillColor(Color::Transparent);
    barrier33.setPosition(492, 467);
    barriers.push_back(barrier33);
    RectangleShape barrier34;
    barrier34.setSize(Vector2f(184, 20));
    barrier34.setFillColor(Color::Transparent);
    barrier34.setPosition(83, 591);
    barriers.push_back(barrier34);
    RectangleShape barrier35;
    barrier35.setSize(Vector2f(184, 20));
    barrier35.setFillColor(Color::Transparent);
    barrier35.setPosition(370, 591);
    barriers.push_back(barrier35);
    RectangleShape barrier36;
    barrier36.setSize(Vector2f(100, 80));
    barrier36.setFillColor(Color::Transparent);
    barrier36.setPosition(43, 222);
    barriers.push_back(barrier36);
    RectangleShape barrier37;
    barrier37.setSize(Vector2f(100, 80));
    barrier37.setFillColor(Color::Transparent);
    barrier37.setPosition(43, 345);
    barriers.push_back(barrier37);
    RectangleShape barrier38;
    barrier38.setSize(Vector2f(100, 80));
    barrier38.setFillColor(Color::Transparent);
    barrier38.setPosition(492, 222);
    barriers.push_back(barrier38);
    RectangleShape barrier39;
    barrier39.setSize(Vector2f(100, 80));
    barrier39.setFillColor(Color::Transparent);
    barrier39.setPosition(492, 345);
    barriers.push_back(barrier39);
    RectangleShape barrier40;
    barrier40.setSize(Vector2f(40, 20));
    barrier40.setFillColor(Color::Transparent);
    barrier40.setPosition(43, 529);
    barriers.push_back(barrier40);
    RectangleShape barrier41;
    barrier41.setSize(Vector2f(40, 20));
    barrier41.setFillColor(Color::Transparent);
    barrier41.setPosition(554, 529);
    barriers.push_back(barrier41);
    RectangleShape barrier42;
    barrier42.setSize(Vector2f(145, 81));
    barrier42.setFillColor(Color::Transparent);
    barrier42.setPosition(246, 283);
    barriers.push_back(barrier42);

    //Make life icon
    //pacman_life.bmp
    Texture texturePacmanLife;
    texturePacmanLife.loadFromFile("../graphics/pacman_life.bmp");
    Sprite spritePacmanLife;
    spritePacmanLife.setTexture(texturePacmanLife);
    spritePacmanLife.setPosition(418, 680);

    // Make tunnels
    RectangleShape tunnel1;
    tunnel1.setSize(Vector2f(50, 37));
    tunnel1.setFillColor(Color::Transparent);
    tunnel1.setPosition(6, 305);
    RectangleShape tunnel2;
    tunnel2.setSize(Vector2f(50, 37));
    tunnel2.setFillColor(Color::Transparent);
    tunnel2.setPosition(582, 305);

    // timer clock
    Clock clock;
    Clock powerupClock;
    int dir = 0; // the direction of motion
    int lastPos_x; // pacman's x position before moving
    int lastPos_y; // y pacman's position before moving
    bool moveLeft = false; // pacman moving left?
    bool moveRight = false; // pacman moving right?
    bool moveUp = false; // pacman moving up?
    bool moveDown = false; // pacman moving down?
    bool startFlag = false; // has the game started?
    bool endFlag = false; // has the game ended?
    bool moveFlag = false; // can pacman move?
    bool scoreFlag = false; // has pacman scored?
    bool gomeOver = false; // has the game ended?
    bool powerupFlag = false; // has the game ended?
    int ghostStartSeq = 0; // starting sequence for ghosts' motion
    float timeRemaining;

    // the ghosts' direction of motion
    srand (time(0));

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // End game
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Start Game
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            startFlag = true;
        }

        // game has begun
        if (startFlag && !endFlag)
        {
            // Measure time
            Time moveTime = clock.restart();

            lastPos_x = spritePacman.getPosition().x;
            lastPos_y = spritePacman.getPosition().y;

            // Determine pacman movement based on input
            if (Keyboard::isKeyPressed(Keyboard::Right) || moveRight)
            {
                dir = 1;
                spritePacman.setPosition(spritePacman.getPosition().x + (moveTime.asSeconds() * PACMAN_SPEED), spritePacman.getPosition().y);
                moveRight = true;
                moveLeft = false;
                moveDown = false;
                moveUp = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) || moveLeft)
            {
                dir = 2;
                spritePacman.setPosition(spritePacman.getPosition().x - (moveTime.asSeconds() * PACMAN_SPEED), spritePacman.getPosition().y);
                moveLeft = true;
                moveRight = false;
                moveDown = false;
                moveUp = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Up) || moveUp)
            {
                dir = 3;
                spritePacman.setPosition(spritePacman.getPosition().x, spritePacman.getPosition().y - (moveTime.asSeconds() * PACMAN_SPEED));
                moveUp = true;
                moveLeft = false;
                moveRight = false;
                moveDown = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down) || moveDown)
            {
                dir = 4;
                spritePacman.setPosition(spritePacman.getPosition().x, spritePacman.getPosition().y + (moveTime.asSeconds() * PACMAN_SPEED));
                moveDown = true;
                moveUp = false;
                moveLeft = false;
                moveRight = false;
            }

            Time moveTimeGhosts = clock.restart();
            redGhost.lastPosGhost_x = spriteRedGhost.getPosition().x;
            redGhost.lastPosGhost_y = spriteRedGhost.getPosition().y;
            if (redGhost.ghostDir == 1)
            {
                //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                spriteRedGhost.setPosition(spriteRedGhost.getPosition().x + (moveTimeGhosts.asSeconds() * GHOST_SPEED), spriteRedGhost.getPosition().y);
            }
            if (redGhost.ghostDir == 2)
            {
                //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                spriteRedGhost.setPosition(spriteRedGhost.getPosition().x - (moveTimeGhosts.asSeconds() * GHOST_SPEED), spriteRedGhost.getPosition().y);
            }
            if (redGhost.ghostDir == 3)
            {
                //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y - (moveTimeGhosts.asSeconds() * GHOST_SPEED));
            }
            if (redGhost.ghostDir == 4)
            {
                //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                spriteRedGhost.setPosition(spriteRedGhost.getPosition().x, spriteRedGhost.getPosition().y + (moveTimeGhosts.asSeconds() * GHOST_SPEED));
            }

            if (ghostStartSeq >= 1)
            {
                blueGhost.lastPosGhost_x = spriteBlueGhost.getPosition().x;
                blueGhost.lastPosGhost_y = spriteBlueGhost.getPosition().y;
                if (blueGhost.ghostDir == 1)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x + (moveTimeGhosts.asSeconds() * GHOST_SPEED), spriteBlueGhost.getPosition().y);
                }
                if (blueGhost.ghostDir == 2)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x - (moveTimeGhosts.asSeconds() * GHOST_SPEED), spriteBlueGhost.getPosition().y);
                }
                if (blueGhost.ghostDir == 3)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y - (moveTimeGhosts.asSeconds() * GHOST_SPEED));
                }
                if (blueGhost.ghostDir == 4)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spriteBlueGhost.setPosition(spriteBlueGhost.getPosition().x, spriteBlueGhost.getPosition().y + (moveTimeGhosts.asSeconds() * GHOST_SPEED));
                }
            }

            if (ghostStartSeq >= 2)
            {
                orangeGhost.lastPosGhost_x = spriteOrangeGhost.getPosition().x;
                orangeGhost.lastPosGhost_y = spriteOrangeGhost.getPosition().y;
                if (orangeGhost.ghostDir == 1)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x + (moveTimeGhosts.asSeconds() * GHOST_SPEED), spriteOrangeGhost.getPosition().y);
                }
                if (orangeGhost.ghostDir == 2)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x - (moveTimeGhosts.asSeconds() * GHOST_SPEED), spriteOrangeGhost.getPosition().y);
                }
                if (orangeGhost.ghostDir == 3)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y - (moveTimeGhosts.asSeconds() * GHOST_SPEED));
                }
                if (orangeGhost.ghostDir == 4)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spriteOrangeGhost.setPosition(spriteOrangeGhost.getPosition().x, spriteOrangeGhost.getPosition().y + (moveTimeGhosts.asSeconds() * GHOST_SPEED));
                }
            }

            if (ghostStartSeq >= 3)
            {
                pinkGhost.lastPosGhost_x = spritePinkGhost.getPosition().x;
                pinkGhost.lastPosGhost_y = spritePinkGhost.getPosition().y;
                if (pinkGhost.ghostDir == 1)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spritePinkGhost.setPosition(spritePinkGhost.getPosition().x + (moveTimeGhosts.asSeconds() * GHOST_SPEED), spritePinkGhost.getPosition().y);
                }
                if (pinkGhost.ghostDir == 2)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spritePinkGhost.setPosition(spritePinkGhost.getPosition().x - (moveTimeGhosts.asSeconds() * GHOST_SPEED), spritePinkGhost.getPosition().y);
                }
                if (pinkGhost.ghostDir == 3)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y - (moveTimeGhosts.asSeconds() * GHOST_SPEED));
                }
                if (pinkGhost.ghostDir == 4)
                {
                    //std::cout<< moveTimeGhosts.asSeconds()<<"\n";
                    spritePinkGhost.setPosition(spritePinkGhost.getPosition().x, spritePinkGhost.getPosition().y + (moveTimeGhosts.asSeconds() * GHOST_SPEED));
                }
            }
        }

        // in the case of motion
        if (dir != 0)
        {
            // Is there a coin in Pacman's way
            for (int i = 0; i < index; i++)
            {
                if(spritePacman.getGlobalBounds().intersects(coin[i].getGlobalBounds()))
                {
                    coin[i].setFillColor(Color::Transparent);
                    coin[i].setPosition(0,0);
                    score++;
                }
            }

            // update score
            scoreText.setString(std::to_string(score));

            // Is there a barrier in Pacman's way?
            for (int i = 0; i < 42; i++)
            {
                if(spritePacman.getGlobalBounds().intersects(barriers[i].getGlobalBounds()))
                {
                    spritePacman.setPosition(lastPos_x, lastPos_y);
                }
            }

            // Is there a tunnel in Pacman's way
            if (spritePacman.getGlobalBounds().intersects(tunnel1.getGlobalBounds()))
            {
                spritePacman.setPosition(531, 305);
            }
            if (spritePacman.getGlobalBounds().intersects(tunnel2.getGlobalBounds()))
            {
                spritePacman.setPosition(57, 305);
            }

            // Is there a powerup pellet in Pacman's way
            for (int i = 0; i < 4; i++)
            {
                if (spritePacman.getGlobalBounds().intersects(powerup[i].getGlobalBounds()))
                {
                    powerup[i].setFillColor(Color::Transparent);
                    powerup[i].setPosition(0,0);
                    powerupFlag = true;
                }
            }

            // when Pacman eats a powerup pellet
            if (powerupFlag)
            {
                if (!(blueGhost.reverse && redGhost.reverse && orangeGhost.reverse && pinkGhost.reverse))
                {
                    blueGhost.reverse = true;
                    redGhost.reverse = true;
                    orangeGhost.reverse = true;
                    pinkGhost.reverse = true;
                    timeRemaining = 5.0;
                }
                else
                {
                    // if power pellet consumed start timer
                    Time powerupTime = powerupClock.restart();
                    int elapsedTime = powerupClock.getElapsedTime().asSeconds();
                    timeRemaining -= elapsedTime;
                }

                if (timeRemaining >= 0.0f)
                {
                    if (spritePacman.getGlobalBounds().intersects(spriteBlueGhost.getGlobalBounds()))
                    {
                        spriteBlueGhost.setColor(Color::Transparent);
                        spriteBlueGhost.setPosition(645,730);
                        blueGhost.ghostDir = 0; //immobililze ghost
                    }
                    if (spritePacman.getGlobalBounds().intersects(spriteRedGhost.getGlobalBounds()))
                    {
                        spriteRedGhost.setColor(Color::Transparent);
                        spriteRedGhost.setPosition(645,730);
                        redGhost.ghostDir = 0; //immobililze ghost
                    }
                    if (spritePacman.getGlobalBounds().intersects(spriteOrangeGhost.getGlobalBounds()))
                    {
                        spriteOrangeGhost.setColor(Color::Transparent);
                        spriteOrangeGhost.setPosition(645,730);
                        orangeGhost.ghostDir = 0; //immobililze ghost
                    }
                    if (spritePacman.getGlobalBounds().intersects(spritePinkGhost.getGlobalBounds()))
                    {
                        spritePinkGhost.setColor(Color::Transparent);
                        spritePinkGhost.setPosition(645,730);
                        pinkGhost.ghostDir = 0; //immobililze ghost
                    }
                }
                else if (timeRemaining < 0.0f)
                {
                    blueGhost.reverse = false;
                    redGhost.reverse = false;
                    orangeGhost.reverse = false;
                    pinkGhost.reverse = false;
                    powerupFlag = false;
                }
            }
            else if (!powerupFlag)
            {
                if ((spritePacman.getGlobalBounds().intersects(spriteBlueGhost.getGlobalBounds()))
                    || (spritePacman.getGlobalBounds().intersects(spriteRedGhost.getGlobalBounds()))
                    || (spritePacman.getGlobalBounds().intersects(spriteOrangeGhost.getGlobalBounds()))
                    || (spritePacman.getGlobalBounds().intersects(spritePinkGhost.getGlobalBounds())))
                {
                    spritePacman.setColor(Color::Transparent);
                    endFlag = true;
                }
            }

            // is the game over
            if (score == 244)
            {
                endFlag = true;
            }
        }

        // Move ghosts based on random direction
        srand (time(0));
        // If there's a barrier in ghosts' ways, set a new rand
        for (int i = 0; i < 42; i++)
        {
            if((spriteBlueGhost.getGlobalBounds().intersects(barriers[i].getGlobalBounds())))
            {
                spriteBlueGhost.setPosition(blueGhost.lastPosGhost_x, blueGhost.lastPosGhost_y);
                blueGhost.ghostDir = 1 + (rand() % 4);
                //ghostStartSeq++;
            }
        }
        for (int i = 0; i < 42; i++)
        {
            if ((spriteRedGhost.getGlobalBounds().intersects(barriers[i].getGlobalBounds())))
            {
                spriteRedGhost.setPosition(redGhost.lastPosGhost_x,redGhost.lastPosGhost_y);
                redGhost.ghostDir = 1 + (rand() % 4);
                ghostStartSeq++;
            }
        }
        for (int i = 0; i < 42; i++)
        {
            if ((spriteOrangeGhost.getGlobalBounds().intersects(barriers[i].getGlobalBounds())))
            {
                spriteOrangeGhost.setPosition(orangeGhost.lastPosGhost_x, orangeGhost.lastPosGhost_y);
                orangeGhost.ghostDir = 1 + (rand() % 4);
                //ghostStartSeq++;
            }
        }
        for (int i = 0; i < 42; i++)
        {
            if ((spritePinkGhost.getGlobalBounds().intersects(barriers[i].getGlobalBounds())))
            {
                spritePinkGhost.setPosition(pinkGhost.lastPosGhost_x,pinkGhost.lastPosGhost_y);
                pinkGhost.ghostDir = 1 + (rand() % 4);
                //ghostStartSeq++;
            }
        }

        // Clear everything from the last frame
        window.clear();

        // Draw our game scene here
        window.draw(spriteBackground);

        //Draw pink Ghost
        window.draw(spritePinkGhost);

        //Draw orange Ghost
        window.draw(spriteOrangeGhost);

        //Draw blue Ghost
        window.draw(spriteBlueGhost);

        //Draw red Ghost
        window.draw(spriteRedGhost);

        //Draw Pacman
        window.draw(spritePacman);


        //Draw powerups
        for (int i = 0; i < 4; i++)
        {
            window.draw(powerup[i]);
        }

        //Draw coins
        for (int i = 0; i < index; i++)
        {
            window.draw(coin[i]);
        }

        //Draw life icon
        window.draw(spritePacmanLife);

        //Draw barriers
//        window.draw(barrier1);
//        window.draw(barrier2);
//        window.draw(barrier3);
//        window.draw(barrier4);
//        window.draw(barrier5);
//        window.draw(barrier6);
//        window.draw(barrier7);
//        window.draw(barrier8);
//        window.draw(barrier9);
//        window.draw(barrier10);
//        window.draw(barrier11);
//        window.draw(barrier12);
//        window.draw(barrier13);
//        window.draw(barrier14);
//        window.draw(barrier15);
//        window.draw(barrier16);
//        window.draw(barrier17);
//        window.draw(barrier18);
//        window.draw(barrier19);
//        window.draw(barrier20);
//        window.draw(barrier21);
//        window.draw(barrier22);
//        window.draw(barrier23);
//        window.draw(barrier24);
//        window.draw(barrier25);
//        window.draw(barrier26);
//        window.draw(barrier27);
//        window.draw(barrier28);
//        window.draw(barrier29);
//        window.draw(barrier30);
//        window.draw(barrier31);
//        window.draw(barrier32);
//        window.draw(barrier33);
//        window.draw(barrier34);
//        window.draw(barrier35);
//        window.draw(barrier36);
//        window.draw(barrier37);
//        window.draw(barrier38);
//        window.draw(barrier39);
//        window.draw(barrier40);
//        window.draw(barrier41);
//        window.draw(barrier42);
        for (int i = 0; i < 42; i++)
        {
            window.draw(barriers[i]);
        }

        //Draw tunnels
        window.draw(tunnel1);
        window.draw(tunnel2);

        // Draw start message
        if (!startFlag)
        {
            // Draw Start Text
            window.draw(startText);
        }

        // Draw score text
        window.draw(scoreText);

        // Game over
        if (endFlag)
        {
            window.draw(endText);
        }

        // Show everything we just drew
        window.display();
    }
    return 0;
}
