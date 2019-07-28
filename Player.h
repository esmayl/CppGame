#include "Vector3.h"
#include "Bullet.h"

class Player
{

    public:
      Player();
      Bullet bulletDrawable;
      sf::Sprite playerSprite;
      sf::Sprite bulletSprite;
      Vector3 position;
      bool isAlive;
      void Shoot();
};
