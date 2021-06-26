#include "RenderHandler.h"

// Render setup
void RenderHandler::InitDefault(int screenWidth, int screenHeight,RenderHandler* handler)
{
    XInitThreads();

    playerSize = 10;

    // render code
    screenTexture.create(screenWidth, screenHeight);

    wallSize = sf::Vector2f(6 ,6); // Width and height of the walls

    screenSize.x = screenWidth;
    screenSize.y = screenHeight;

    CreatePlayer(playerSize, sf::Color::Green);

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
    size_t tempScreenSizeX = screenSize.x;
    size_t tempScreenSizeY = screenSize.y;
    mutex.unlock();

    // for (size_t i = wallSize.x; i < (screenSize.x) - wallSize.x - 1; i++)
    // {
    //     for (size_t j = wallSize.y; j < (screenSize.y) - wallSize.y - 1; j++)
    //     {
    //         rectangle.setSize(sf::Vector2f(1,1));
    //         rectangle.setFillColor(sf::Color::Red);
    //         rectangle.setPosition(0+i, 0+j);
    //         mutex.lock();
    //         screenTexture.draw(rectangle);
    //         mutex.unlock();
    //     }
    // }

    rectangle.setSize(sf::Vector2f(tempScreenSizeX,tempScreenSizeY));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(0,0);

    mutex.lock();
    screenTexture.draw(rectangle);
    mutex.unlock();

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

    //Temporary create variables to make threading work
    mutex.lock();
    size_t tempSizeX = wallSize.x;
    size_t tempSizeY = wallSize.y;
    size_t tempScreenSizeX = screenSize.x;
    size_t tempScreenSizeY = screenSize.y;
    mutex.unlock();

    // for (size_t i = 0; i <= tempScreenSizeX - tempSizeX; i += tempSizeX)
    // {
    //     for (size_t j = 0; j <= tempScreenSizeY - tempSizeY; j+= tempSizeY)
    //     {
    //         //Use tempSizeX to indicate a wall has to be drawn
    //         if(j < tempSizeY ||i < tempSizeX || i >= tempScreenSizeX - tempSizeX || j >= tempScreenSizeY - tempSizeY )
    //         {
    //             wallRectShape.setPosition(0+i,0+j);
    //             wallRectShape.setSize(sf::Vector2f(tempSizeX,tempSizeY));
    //
    //             mutex.lock();
    //             screenTexture.draw(wallRectShape);
    //             mutex.unlock();
    //         }
    //     }
    // }

    wallRectShape.setPosition(0,0);
    wallRectShape.setSize(sf::Vector2f(tempScreenSizeX,tempSizeY));

    mutex.lock();
    screenTexture.draw(wallRectShape);
    mutex.unlock();

    wallRectShape.setPosition(0,0);
    wallRectShape.setSize(sf::Vector2f(tempSizeX,tempScreenSizeY));

    mutex.lock();
    screenTexture.draw(wallRectShape);
    mutex.unlock();

    wallRectShape.setPosition(tempScreenSizeX-tempSizeX,0);
    wallRectShape.setSize(sf::Vector2f(tempSizeX,tempScreenSizeY));

    mutex.lock();
    screenTexture.draw(wallRectShape);
    mutex.unlock();

    wallRectShape.setPosition(0,tempScreenSizeY-tempSizeY);
    wallRectShape.setSize(sf::Vector2f(tempScreenSizeX,tempSizeY));

    mutex.lock();
    screenTexture.draw(wallRectShape);
    mutex.unlock();


    mutex.lock();
    screenTexture.display();
    wallTexture = screenTexture.getTexture();
    mutex.unlock();

    currentWallSprite.setTexture(wallTexture);

    std::cout << "Done drawing walls" << std::endl;
    return;
}

void RenderHandler::CreatePlayer(float pSize, sf::Color playerColor)
{
    playerCircleShape = sf::CircleShape(pSize);

    playerCircleShape.setFillColor(playerColor);
    playerCircleShape.setPosition((screenSize.x)/2,(screenSize.y)*0.75f);
}

void RenderHandler::CreateSprite(sf::Texture shapeToDraw, sf::Vector2f* pos)
{
    sf::Sprite temp;
    temp.setTexture(sf::Texture(shapeToDraw));
    temp.setPosition(*pos);

    // spriteListToDraw.AddToList(temp);
}

void RenderHandler::SpawnEnemies()
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(playerSize*3, screenSize.x); // define the range

    std::uniform_int_distribution<> distr2(playerSize*3, screenSize.y); // define the range

    for (size_t i = 0; i < 10; i++)
    {
      sf::RectangleShape enemy = sf::RectangleShape(sf::Vector2f(playerSize,playerSize));

      enemy.setFillColor(sf::Color::Black);
      enemy.setPosition(distr(gen),distr2(gen));

      //Add enemy to list
      //Drawn enemies from list

      screenTexture.draw(enemy);
    }



}

// Loops
void RenderHandler::MovePlayer(sf::Vector2f* direction)
{
    sf::Vector2f currentPos = playerCircleShape.getPosition();


    sf::Vector2f border = screenSize;

    border.x -= wallSize.x;
    border.y -= wallSize.y;

    border.x -= playerSize;
    border.y -= playerSize;

    if(currentPos.x + direction->x < border.x && currentPos.y + direction->y < border.y && currentPos.x + direction->x > wallSize.x && currentPos.y + direction->y > wallSize.y)
    {
        playerCircleShape.move(direction->x,direction->y); //Not able to move in fractions of an int
    }
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

    SpawnEnemies();

    screenTexture.display();

    // convert backbuffer to drawable
    sprite.setTexture(screenTexture.getTexture());

    // draw backbuffer to the screen
    mainWindow->draw(sprite);
    mainWindow->display();

    frameCounter++;
}
