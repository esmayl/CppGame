#include "RenderHandler.h"

// Render setup
void RenderHandler::InitDefault(int screenWidth, int screenHeight)
{
    // render code
    screenTexture.create(screenWidth,screenHeight);

    CreateBackground(screenWidth,screenHeight);
    CreateWalls(screenWidth,screenHeight);
    SetupPlayer(screenWidth,screenHeight,10.f,sf::Color::Green);
}

void RenderHandler::CreateBackground(int screenWidth, int screenHeight)
{
    sf::RectangleShape rectangle;

    screenTexture.clear();

    for (size_t i = borderEdge; i < (screenWidth)-borderEdge-1; i++)
    {
        for (size_t j = borderEdge; j < (screenHeight)-borderEdge-1; j++)
        {
        rectangle.setSize(sf::Vector2f(1,1));
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(1);
        rectangle.setPosition(0+i, 0+j);
        screenTexture.draw(rectangle);
        }
    }
    screenTexture.display();

    backgroundTexture = screenTexture.getTexture();
    backgroundSprite.setTexture(backgroundTexture);
}

void RenderHandler::CreateWalls(int screenWidth, int screenHeight)
{
    sf::Vector2f wallSize(10,10);
    wallRectShape = sf::RectangleShape(wallSize);
    wallRectShape.setFillColor(sf::Color::Cyan);
    wallRectShape.setOutlineColor(sf::Color::Black);
    wallRectShape.setOutlineThickness(1);

    for (size_t i = 0; i <= (screenWidth)-borderEdge; i+=wallSize.x) {
        for (size_t j = 0; j <= (screenHeight)-borderEdge; j+=wallSize.y)
        {
            if(j <= borderEdge ||i <= borderEdge || i >= (screenWidth)-(borderEdge*2) || j >= (screenHeight)-(borderEdge*2))
            {
                wallRectShape.setPosition(0+i,0+j);
                screenTexture.draw(wallRectShape);
            }
        }
    }
    screenTexture.display();
    wallTexture = screenTexture.getTexture();
    currentWallSprite.setTexture(wallTexture);
}

// Setup
void RenderHandler::SetupPlayer(int screenWidth, int screenHeight, float playerSize, sf::Color playerColor)
{
  playerCircleShape = sf::CircleShape(playerSize);
 
  playerCircleShape.setFillColor(playerColor);
  playerCircleShape.setPosition((screenWidth)/2,(screenHeight)*0.75f);
}

// Loops
void RenderHandler::MovePlayer(Vector3* direction)
{
    playerCircleShape.move(direction->x,direction->y);
}

// Render loops
void RenderHandler::DrawBackground()
{
    screenTexture.draw(backgroundSprite);
}

void RenderHandler::DrawWalls()
{
    screenTexture.draw(currentWallSprite);
}

void RenderHandler::DrawPlayer()
{
    screenTexture.draw(playerCircleShape);
}

void RenderHandler::RenderLoop()
{
    screenTexture.clear();

    DrawBackground();
    DrawWalls();
    DrawPlayer();

    screenTexture.display();    
}

