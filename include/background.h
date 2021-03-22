#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "tetris_const.h"

namespace Tetris
{
    class Background
    {
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    public:
        Background();
        void Draw(sf::RenderWindow &window);
    };
}