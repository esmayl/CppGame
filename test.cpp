#include "RenderHandler.h"
#include "Player.h"
#include <iostream>
#include <X11/Xlib.h>   

Player* player;
RenderHandler* renderHandler;

sf::Sprite sprite;
sf::Clock klok;
Vector3 moveDirection;
int screenWidth= 1920;
int screenHeight= 1080;
float speed = 120;
float time1,time2;
float deltaTime;
float oneSecond;
float counter,timer = 1;
int frameCounter = 0;
bool canShoot = true;

// Setup

void SetupRendering()
{
  renderHandler = new RenderHandler();
  renderHandler->InitDefault(screenWidth,screenHeight);
}

void SetupPlayer(float playerSize = 10.f)
{
  player = new Player();
  
  moveDirection.Clear();
}

// Loops
void PlayerInputCheck()
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot)
  {
    player->Shoot();
    canShoot = false;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
  {
    moveDirection.y = -speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
  {
    moveDirection.x = -speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
  {
    moveDirection.x = speed;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
  {
    moveDirection.y = speed;
  }
}

void TimeLoop()
{
    time2 = klok.getElapsedTime().asSeconds();

    deltaTime = time2-time1;

    oneSecond += deltaTime;

    time1 = time2;

    time2 = time1;

    if(oneSecond >= 1)
    {
      std::cout << "One second passed, fps: " << frameCounter << std::endl;
      oneSecond = 0;
      frameCounter = 0;
    }
}

void PlayerSpriteMovement(Vector3* direction)
{
    direction->Normalize();

    renderHandler->MovePlayer(direction);
}

int main()
{
    XInitThreads();
    sf::VideoMode temp(screenWidth,screenHeight);

    // , sf::Style::Fullscreen
    sf::RenderWindow window(temp, "C plus plus game" );

    SetupRendering();
    SetupPlayer(10.f);

    time1 = klok.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        TimeLoop();
        moveDirection.Clear();

        PlayerInputCheck();

        if(moveDirection.magnitude() > 0)
        {
          moveDirection *= deltaTime;

          PlayerSpriteMovement(&moveDirection);
        }

        renderHandler->RenderLoop();

        // check if the player has clicked the close button of the window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        // convert backbuffer to drawable
        sprite.setTexture(renderHandler->screenTexture.getTexture());

        // draw backbuffer to the screen
        window.draw(sprite);
        window.display();

        frameCounter++;

        // shoot counter

        if(counter >= timer)
        {
            canShoot = true;
            counter = 0;
        }
        else
        {
            counter += deltaTime;
        }
    }

    return 0;
}
