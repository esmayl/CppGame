#ifndef SFML_LIBS
#define SFML_LIBS
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#endif

class SpriteList
{
    public:
        ~SpriteList();
        SpriteList();
        SpriteList(int size);
        void AddToList(sf::Sprite spriteToAdd);
        void Clear();
        sf::Sprite* GetSprites();
        int Length();
    private:
        sf::Sprite* spritesToDraw;
        int counter = 0;
        void Resize(int* newSize);
};