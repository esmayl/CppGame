#include <iostream>
#include "Player.h"

Player::Player()
{
    isAlive = true;
    bulletDrawable.m_sprite = bulletSprite;
}

void Player::Shoot()
{
    std::cout << "Bang!";
}
