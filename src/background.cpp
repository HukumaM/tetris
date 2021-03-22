#include "background.h"

namespace Tetris
{
    // BACKGROUND

    Background::Background()
    {
        this->m_texture.loadFromFile("textures/background_line.jpg");
        this->m_texture.setRepeated(true);
        this->m_sprite.setTexture(this->m_texture);
        this->m_sprite.setTextureRect(sf::IntRect(0, 0, 2200, 4400));
        this->m_sprite.setScale(
            WIDTH_WINDOW / 2200,
            HEIGHT_WINDOW / 4400); // 0.0818f
    }

    void Background::Draw(sf::RenderWindow &window)
    {
        window.draw(this->m_sprite);
    }
}