#include "RenderHandler.h"
#ifndef SYSTEM_LIBS
#define SYSTEM_LIBS
#include <iostream>
#include <functional>
#include <X11/Xlib.h>
#include "math.h"
#endif
#include "Player.h"

Player* player;
RenderHandler renderHandler;
sf::CircleShape extraShape;
sf::Sprite p;
sf::Texture* textureHolder;

sf::Sprite sprite;
sf::Clock gameClock;
sf::Vector2f moveDirection;
int screenWidth = 800;
int screenHeight = 600;
float speed = 1;
float startTime,time2;
float deltaTime;
float oneSecond;
float counter,timer = 1;
bool canShoot = true;

// Setup

void SetupPlayer(float playerSize = 10.f)
{
  player = new Player();

  moveDirection = sf::Vector2f(0,0);
}

// Loops

void PlayerInputCheck(sf::RenderWindow* window)
{
    moveDirection.x = 0;
    moveDirection.y = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot)
    {
      player->Shoot();
      canShoot = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      moveDirection.y = -speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      moveDirection.x = -speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      moveDirection.x = speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      moveDirection.y = speed;
    }


    if(std::abs(moveDirection.x) > 0 || std::abs(moveDirection.y) > 0)
    {
        renderHandler.MovePlayer(&moveDirection);
    }
}

void TimeLoop(sf::RenderWindow* window)
{
  while(window->isOpen())
  {
    time2 = gameClock.getElapsedTime().asSeconds();

    deltaTime = time2-startTime;

    oneSecond += deltaTime;

    renderHandler.deltaTime = deltaTime;

    startTime = time2;

    time2 = startTime;

    if(oneSecond >= 1)
    {
      std::cout << "One second passed, fps: " << renderHandler.frameCounter << std::endl;
      oneSecond = 0;
      renderHandler.ResetFrameCounter();
    }
  }
}

int main()
{
    XInitThreads(); // needed for multithreading render window

    sf::VideoMode temp(screenWidth,screenHeight);

    renderHandler.InitDefault(temp.width,temp.height,&renderHandler);

    // , sf::Style::Fullscreen
    sf::RenderWindow window(temp, "C plus plus game" );

    startTime = gameClock.getElapsedTime().asSeconds();

    sf::Thread setupPlayerThread(&SetupPlayer,10.f);
    setupPlayerThread.launch();

    sf::Thread setupTimeThread(&TimeLoop,&window);
    setupTimeThread.launch();

    while (window.isOpen())
    {
        window.setActive(false);

        PlayerInputCheck(&window);

        renderHandler.RenderLoop(&window);

        // check if the player has clicked the close button of the window
        // has to stay in this thread, will block the screen from closing
        sf::Event event;

        while (window.pollEvent(event))
        {
          if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                screenWidth = event.size.width;
                screenHeight =  event.size.height;

                temp.width = screenWidth;
                temp.height = screenHeight;

                renderHandler.InitDefault(temp.width,temp.height,&renderHandler);
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

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

    setupTimeThread.terminate();
    setupPlayerThread.terminate();

    return 0;
}
