#pragma once 
#include <SFML/Graphics.hpp>
#include "point.h"
#include "tetris_const.h"
#include <iostream>
#include <cmath>


namespace Tetris
{
    extern std::vector<std::vector<int16_t>> field;
    class Tetromino
    {
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Clock m_clock_fall;

        Tetris::Types m_type;

        int16_t m_score;
        int16_t m_color;

        std::vector<Tetris::Point<int16_t>> figure;

        Point<float> rotation_point;

        float delayed_fall;
        bool ability_generate;

    public:
        Tetromino();
        virtual ~Tetromino() = default;

        void SetDelayedFall(const float value);
        bool PermissibilityMovement(DirectionMovements direction);

        void Generator();
        inline bool GetAbilityGenerate() const
        {
            return this->ability_generate;
        }
        inline sf::String GetScore() const 
        {
            return std::to_string(this->m_score);
        }
        void MoveDX(DirectionMovements direction);
        bool MoveDY();
        void Draw(sf::RenderWindow &window);
        void Rotate();
        void CleaningLine();
        void MovementShape(int16_t x_offset, int16_t y_offset);
        void AddingShapeToField();
    };
}