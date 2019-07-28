#include "RenderHandler.h"

// Render setup
void RenderHandler::InitDefault(int screenWidth, int screenHeight,RenderHandler* handler)
{
    XInitThreads();
    
    // render code
    screenTexture.create(screenWidth, screenHeight);

    Vector3 test(screenWidth, screenHeight, 0);

    wallSize = sf::Vector2f(3,3); // Width and height of the walls

    screenSize.x = screenWidth;
    screenSize.y = screenHeight;

    CreatePlayer(10.f, sf::Color::Green);

    screenTexture.clear();

    handler->CreateBackground();
    handler->CreateWalls();

    // sf::Thread bgThread(&RenderHandler::CreateBackground,handler);
    // sf::Thread wallThread(&RenderHandler::CreateWalls,handler);
    
    // bgThread.launch();
    // wallThread.launch();
    
    // bgThread.wait();
    // wallThread.wait();
}

void RenderHandler::ResetFrameCounter()
{
    frameCounter = 0;
}

void RenderHandler::CreateBackground()
{
    std::cout << "Drawing bg" << std::endl;

    sf::RectangleShape rectangle;

    mutex.lock();
    size_t tempSizeX = wallSize.x;
    size_t tempSizeY = wallSize.y;
    size_t tempScreenSizeX = screenSize.x;
    size_t tempScreenSizeY = screenSize.y;
    mutex.unlock();

    for (size_t i = wallSize.x; i < (screenSize.x) - wallSize.x - 1; i++)
    {
        for (size_t j = wallSize.y; j < (screenSize.y) - wallSize.y - 1; j++)
        {
            rectangle.setSize(sf::Vector2f(1,1));
            rectangle.setFillColor(sf::Color::Red);
            rectangle.setPosition(0+i, 0+j);
            mutex.lock();
            screenTexture.draw(rectangle);
            mutex.unlock();
        }
    }
    
    mutex.lock();
    screenTexture.display();
    backgroundTexture = screenTexture.getTexture();
    mutex.unlock();

    backgroundSprite.setTexture(backgroundTexture);

    std::cout << "Done drawing bg" << std::endl;

    return;
}

void RenderHandler::CreateWalls()
{
    std::cout << "Drawing walls" << std::endl;

    wallRectShape = sf::RectangleShape(wallSize);
    wallRectShape.setFillColor(sf::Color::Cyan);
    wallRectShape.setOutlineColor(sf::Color::Black);
    wallRectShape.setOutlineThickness(0.1f);

    mutex.lock();
    size_t tempSizeX = wallSize.x;
    size_t tempSizeY = wallSize.y;
    size_t tempScreenSizeX = screenSize.x;
    size_t tempScreenSizeY = screenSize.y;
    mutex.unlock();

    // use wallSize as start instead 0, wall is offscreen at 0
    for (size_t i = 0; i <= tempScreenSizeX - tempSizeX; i += tempSizeX) 
    {
        for (size_t j = 0; j <= tempScreenSizeY - tempSizeY - 1; j+= tempSizeY)
        {
            if(j < tempSizeY ||i < tempSizeX || i >= tempScreenSizeX - (tempSizeX*2) || j >= tempScreenSizeY - tempSizeY )
            {
                wallRectShape.setPosition(0+i,0+j);
    
                mutex.lock();
                screenTexture.draw(wallRectShape);
                mutex.unlock();
            }
        }
    }

    mutex.lock();
    screenTexture.display();
    wallTexture = screenTexture.getTexture();
    mutex.unlock();

    currentWallSprite.setTexture(wallTexture);

    std::cout << "Done drawing walls" << std::endl;
    return;
}

void RenderHandler::CreatePlayer(float playerSize, sf::Color playerColor)
{
    playerCircleShape = sf::CircleShape(playerSize);

    playerCircleShape.setFillColor(playerColor);
    playerCircleShape.setPosition((screenSize.x)/2,(screenSize.y)*0.75f);
}

void RenderHandler::CreateSprite(sf::Texture shapeToDraw, sf::Vector2f& pos)
{
    sf::Sprite temp;
    temp.setTexture(sf::Texture(shapeToDraw));
    temp.setPosition(pos);

    // spriteListToDraw.AddToList(temp);
}

// Loops
void RenderHandler::MovePlayer(Vector3* direction)
{
    playerCircleShape.move(direction->x,direction->y);
}

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

void RenderHandler::DrawEnemies()
{
    return;
}

void RenderHandler::RenderLoop(sf::RenderWindow* mainWindow)
{
    mainWindow->clear();

    screenTexture.clear();

    DrawBackground();
    DrawWalls();
    DrawPlayer();
    DrawEnemies();

    screenTexture.display();

    // convert backbuffer to drawable
    sprite.setTexture(screenTexture.getTexture());

    // draw backbuffer to the screen
    mainWindow->draw(sprite);
    mainWindow->display();
    
    frameCounter++;
}

