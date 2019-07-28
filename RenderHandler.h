#include "Vector3.h"
#include "SpriteList.h"
#include <iostream>

#ifndef SFML_LIBS
#define SFML_LIBS
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#endif

#ifndef SYSTEM_LIBS
#define SYSTEM_LIBS
#include <iostream>
#include <functional>
#include <X11/Xlib.h>
#endif

class RenderHandler
{
    public:
        sf::RenderTexture screenTexture;
        sf::Texture backgroundTexture;
        sf::Texture wallTexture;
        sf::Sprite backgroundSprite;
        sf::Sprite currentWallSprite;
        sf::Sprite sprite;        
        sf::CircleShape playerCircleShape;
        sf::RectangleShape wallRectShape;
        sf::Mutex mutex;
        sf::Vector2f wallSize;
        Vector3 screenSize;
        int frameCounter = 0;         
        void InitDefault(int screenWidth, int screenHeight, RenderHandler* handler);
        void ResetFrameCounter();
        void RenderLoop(sf::RenderWindow* mainWindow);
        void MovePlayer(Vector3* direction);
        void CreateWalls();
        void CreateBackground();
        void CreateSprite(sf::Texture spriteToDraw,sf::Vector2f& pos);
        void DrawEnemies();
        void SetWindow(sf::RenderWindow* newWindow);
    private:
        int amountOfShapes = 0;
        void DrawBackground();
        void DrawWalls();
        void DrawPlayer();
        void CreatePlayer(float playerSize, sf::Color playerColor);
};