#ifndef SFML_LIBS
#define SFML_LIBS
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#endif

class Enemy
{
    public:
        sf::Texture enemyTexture;
        sf::Vector2f currentPos;
        void Move(sf::Vector2f* moveDir);
};