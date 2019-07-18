#include "BaseDrawable.h"
#include "Player.h"
#include <iostream>

Player* player;

sf::RenderTexture screenTexture;
sf::Texture backgroundTexture;
sf::Texture wallTexture;
sf::Sprite backgroundSprite;
sf::Sprite currentWallSprite;
sf::Sprite sprite;
sf::Clock klok;
sf::CircleShape playerCircleShape;
sf::RectangleShape wallRectShape;
Vector3* moveSpeed;
const int screenWidth = 1920;
const int screenHeight = 1080;
const int borderEdge = 10;
float speed = 3;
float time1,time2;
float deltaTime;
float oneSecond;
int frameCounter = 0;

// Render setup
void CreateBackground()
{
  sf::RectangleShape rectangle;

  screenTexture.clear();

  for (size_t i = borderEdge; i < screenWidth-borderEdge-1; i++)
  {
    for (size_t j = borderEdge; j < screenHeight-borderEdge-1; j++)
    {
      rectangle.setSize(sf::Vector2f(1,1));
      rectangle.setOutlineColor(sf::Color::Red);
      rectangle.setOutlineThickness(1);
      rectangle.setPosition(0+i, 0+j);
      screenTexture.draw(rectangle);
    }
  }
  screenTexture.display();

  backgroundTexture = screenTexture.getTexture();
  backgroundSprite.setTexture(backgroundTexture);
}

void CreateWalls()
{
  sf::Vector2f wallSize(10,10);
  wallRectShape = sf::RectangleShape(wallSize);
  wallRectShape.setFillColor(sf::Color::Cyan);
  wallRectShape.setOutlineColor(sf::Color::Black);
  wallRectShape.setOutlineThickness(1);

  for (size_t i = 0; i <= screenWidth-borderEdge; i+=wallSize.x) {
    for (size_t j = 0; j <= screenHeight-borderEdge; j+=wallSize.y)
    {
        if(j <= borderEdge ||i <= borderEdge || i >= screenWidth-(borderEdge*2) || j >= screenHeight-(borderEdge*2))
        {
            wallRectShape.setPosition(0+i,0+j);
            screenTexture.draw(wallRectShape);
        }
    }
  }
  screenTexture.display();
  wallTexture = screenTexture.getTexture();
  currentWallSprite.setTexture(wallTexture);
}

// Render loops
void DrawBackground()
{
  screenTexture.draw(backgroundSprite);
}

void DrawPlayer()
{
  if(player->isAlive)
  {
      screenTexture.draw(playerCircleShape);
  }
}

void DrawWalls()
{
  screenTexture.draw(currentWallSprite);
}

// Setup
void SetupPlayer(float playerSize = 10.f,sf::Color playerColor = sf::Color::Green)
{
  playerCircleShape = sf::CircleShape(playerSize);
  player = new Player();
  moveSpeed = new Vector3();
  playerCircleShape.setFillColor(playerColor);
  playerCircleShape.setPosition(screenWidth/2,screenHeight*0.75f);
}

// Loops
void PlayerInputCheck()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    moveSpeed->y = -speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    moveSpeed->x = -speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    moveSpeed->x = speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    moveSpeed->y = speed;
  }
}

void TimeLoop()
{
  time2 = klok.getElapsedTime().asSeconds();

  deltaTime = time2-time1;

  oneSecond += deltaTime;

  time1 = time2;

}

void PlayerSpriteMovement(Vector3* direction)
{
    playerCircleShape.move(direction->x,direction->y);
}

int main()
{
    sf::VideoMode temp(screenWidth,screenHeight);

    sf::RenderWindow window(temp, "SFML works!" , sf::Style::Fullscreen);

    SetupPlayer();

    // render code
    screenTexture.create(screenWidth,screenHeight);

    time1 = klok.getElapsedTime().asSeconds();

    CreateBackground();
    CreateWalls();


    while (window.isOpen())
    {
        TimeLoop();

        time2 = time1;

        if(oneSecond >= 1)
        {
          std::cout << "One second passed, fps: " << frameCounter << std::endl;
          oneSecond = 0;
          frameCounter = 0;
        }


        screenTexture.clear();
        moveSpeed->Clear();

        DrawBackground();
        DrawWalls();
        DrawPlayer();

        // done adding to the screen
        screenTexture.display();

        PlayerInputCheck();

        PlayerSpriteMovement(moveSpeed);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // convert to drawable
        sprite.setTexture(screenTexture.getTexture());
        window.draw(sprite);
        window.display();

        frameCounter++;
    }

    return 0;
}
