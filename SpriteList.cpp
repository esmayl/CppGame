#include "SpriteList.h"

SpriteList::SpriteList()
{
    spritesToDraw = new sf::Sprite[2];
    counter = 0;
}

SpriteList::~SpriteList()
{
    delete[] spritesToDraw;
}

SpriteList::SpriteList(int size)
{
    spritesToDraw = new sf::Sprite[size];
    counter = 0;
}

void SpriteList::AddToList(sf::Sprite spriteToAdd)
{
    spritesToDraw[counter] = spriteToAdd;

    counter++;    
}
void SpriteList::Clear()
{

}
sf::Sprite* SpriteList::GetSprites()
{
    return spritesToDraw;
}
void SpriteList::Resize(int* newSize)
{

}

int SpriteList::Length()
{
    return counter;
}