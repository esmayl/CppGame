#include "BaseDrawable.h"
#include "Player.h"
#include <iostream>

Player* player;

sf::RenderTexture screenTexture;
sf::RenderTexture backgroundTexture;
sf::Sprite backgroundSprite;
sf::CircleShape playerCircleShape;
Vector3* moveSpeed;
const int screenWidth = 1920;
const int screenHeight = 1080;
sf::RectangleShape backgroundArray[screenWidth][screenHeight];
float jumpHeight = 3;
float speed = 3;
float timer = 1;
float counter = timer;
float deltaTime;

void DrawPlayer()
{
  if(player->isAlive)
  {
      screenTexture.draw(playerCircleShape);
  }
}

void DrawBackground()
{
  sf::RectangleShape rectangle;

  backgroundTexture.clear();

  for (size_t i = 0; i < screenWidth; i++)
  {
    for (size_t j = 0; j < screenHeight; j++)
    {
      rectangle.setSize(sf::Vector2f(1,1));
      rectangle.setOutlineColor(sf::Color::Red);
      rectangle.setOutlineThickness(5);
      rectangle.setPosition(0+i, 0+j);
      backgroundArray[i][j] = rectangle;
    }
  }

  backgroundSprite.setTexture(backgroundTexture.getTexture());
}

void DrawWalls()
{

}

void SetupPlayer(float playerSize = 10.f,sf::Color playerColor = sf::Color::Green)
{
  playerCircleShape = sf::CircleShape(playerSize);
  player = new Player();
  moveSpeed = new Vector3();
  playerCircleShape.setFillColor(playerColor);
}

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

void PlayerSpriteMovement(Vector3* direction)
{
    playerCircleShape.move(direction->x,direction->y);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");

    SetupPlayer();

    // render code
    screenTexture.create(screenWidth,screenHeight);

    sf::Clock clock;

    float time1 = clock.getElapsedTime().asSeconds();

    DrawBackground();

    while (window.isOpen())
    {
        float time2 = clock.getElapsedTime().asSeconds();

        deltaTime = time2-time1;

        std::cout << deltaTime << std::endl;

        time1 = time2;

        screenTexture.clear();
        moveSpeed->Clear();

        screenTexture.draw(backgroundSprite);

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
        sf::Sprite sprite(screenTexture.getTexture());
        window.draw(sprite);
        window.display();

        if(counter < timer)
        {
          counter += 0.01;
        }
    }

    return 0;
}
