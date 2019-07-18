#include <iostream>
#include "Player.h"

Player::Player()
{
  isAlive = true;
}

void Player::Shoot()
{
  std::cout << "Bang!";
}
