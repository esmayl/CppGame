#include "./BaseDrawable.h"

void BaseDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects
    target.draw(m_sprite, states);
    // ... or use the low-level API
    states.texture = &m_texture;
    target.draw(m_vertices, states);
    // ... or draw with OpenGL directly
    // glBegin(GL_QUADS);
    // ...
    // glEnd();
}
