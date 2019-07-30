#include "RenderHandler.h"
#include "Player.h"
#ifndef SYSTEM_LIBS
#define SYSTEM_LIBS
#include <iostream>
#include <functional>
#include <X11/Xlib.h>
#endif

Player* player;
RenderHandler renderHandler;
sf::CircleShape extraShape;
sf::Sprite p;
sf::Texture* textureHolder;

sf::Sprite sprite;
sf::Clock gameClock;
Vector3 moveDirection;
int screenWidth = 800;
int screenHeight = 600;
float speed = 3;
float startTime,time2;
float deltaTime;
float oneSecond;
float counter,timer = 1;
bool canShoot = true;

// Setup

void SetupPlayer(float playerSize = 10.f)
{
  player = new Player();

  moveDirection.Clear();
}

// Loops

void PlayerSpriteMovement(Vector3* direction)
{
    renderHandler.MovePlayer(direction);
}

void PlayerInputCheck(sf::RenderWindow* window)
{  
    moveDirection.Clear();

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

    if(moveDirection.magnitude() > 0)
    {
        PlayerSpriteMovement(&moveDirection);
    }
}

void TimeLoop(sf::RenderWindow* window)
{
  while(window->isOpen())
  {
    time2 = gameClock.getElapsedTime().asSeconds();

    deltaTime = time2-startTime;

    oneSecond += deltaTime;

    startTime = time2;

    time2 = startTime;

    if(oneSecond >= 1)
    {
      std::cout << "One second passed, fps: " << renderHandler.frameCounter << std::endl;
      oneSecond = 0;
      renderHandler.frameCounter = 0;
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

    // sf::Thread inputThread(&PlayerInputCheck,&window);
    // inputThread.launch();

    while (window.isOpen())
    {
        window.setActive(false);

        renderHandler.RenderLoop(&window);

        PlayerInputCheck(&window);        
        
        // check if the player has clicked the close button of the window
        // has to stay in this thread, will block the screen from closing
        sf::Event event;
        
        while (window.pollEvent(event))
        {
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