#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Bullet : public sf::Drawable
{

    public:
        sf::Sprite m_sprite;
        sf::Texture m_texture;
        sf::VertexArray m_vertices;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
};