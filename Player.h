#ifndef SYSTEM_LIBS
#define SYSTEM_LIBS
#include <iostream>
#include <functional>
#include "math.h"
#endif

#ifndef SFML_LIBS
#define SFML_LIBS
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#endif

class Player
{

    public:
      Player();
      sf::Sprite playerSprite;
      sf::Sprite bulletSprite;
      sf::Vector2f* position;
      bool isAlive;
      void Shoot();
};
