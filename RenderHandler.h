#include "BaseDrawable.h"
#include "Vector3.h"

class RenderHandler
{
    public:
        sf::RenderTexture screenTexture;
        sf::Texture backgroundTexture;
        sf::Texture wallTexture;
        sf::Sprite backgroundSprite;
        sf::Sprite currentWallSprite;
        sf::CircleShape playerCircleShape;
        sf::RectangleShape wallRectShape;
        sf::Mutex mutex;
        const int borderEdge = 10;
        void InitDefault(int screenWidth, int screenHeight);
        void RenderLoop();
        void MovePlayer(Vector3* direction);
    private:
        void CreateBackground(int screenWidth, int screenHeight);
        void CreateWalls(int screenWidth, int screenHeight);
        void DrawBackground();
        void DrawWalls();
        void DrawPlayer();
        void SetupPlayer(int screenWidth, int screenHeight, float playerSize, sf::Color playerColor);
};