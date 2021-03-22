#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "background.h"
#include "tetris_const.h"
#include "point.h"
#include "tetromino.h"

namespace Tetris
{
    class Tetris
    {
    private:
        sf::RenderWindow m_window;
        sf::Texture m_gm_texture;
        sf::Sprite m_gm_sprite;
        sf::Event m_event;
        sf::Clock m_tick_timer;
        sf::Clock m_fall_timer;

        float m_current_delayed_fall;
        State m_current_state;
        Tetromino *m_tetromino;
        Background *m_background;

    public:
        Tetris();
        virtual ~Tetris();

        void SetState(const State state);
        void Input();
        void Update();
        void Render();

        sf::Event &GetEvent()
        {
            return this->m_event;
        }
        sf::RenderWindow &GetWindow()
        {
            return this->m_window;
        }

        inline bool AbilityGenerate() const
        {
            return this->m_tetromino->GetAbilityGenerate();
        }

     

        inline void Rotate()
        {
            this->m_tetromino->Rotate();
        }
        inline void MoveDX(DirectionMovements direction)
        {
            this->m_tetromino->MoveDX(direction);
        }
        inline void SetDelayedFall(const float value)
        {
            this->m_tetromino->SetDelayedFall(value);
        }
        void Move();
        void Draw();
     
        inline void Display()
        {
            this->m_window.display();
        }
        inline void CleaningLine()
        {
            this->m_tetromino->CleaningLine();
        }
        inline void restart()
        {
            this->m_tetromino = new Tetromino;
        }
      
    };

};