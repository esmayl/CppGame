#ifndef BaseDrawable_H
#define BaseDrawable_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#endif

class BaseDrawable : public sf::Drawable
{
  public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
};
