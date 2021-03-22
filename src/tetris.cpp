
#include "tetris.h"

namespace Tetris
{
    // TETRIS
    Tetris::Tetris()
    {
        this->m_window.create(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), "Tetris", sf::Style::Titlebar | sf::Style::Close);
        this->m_window.setFramerateLimit(60);

        this->m_background = new Background;
        this->m_tetromino = new Tetromino;

        this->m_current_delayed_fall = DELAYED_FALL;
        this->m_gm_texture.loadFromFile("textures/game_over.png");
        this->m_gm_sprite.setTexture(this->m_gm_texture);
        this->m_gm_sprite.setTextureRect(sf::IntRect(0, 0, 1080, 1080));
        this->m_gm_sprite.setScale(0.1f, 0.1f);
        this->m_gm_sprite.setPosition(36.f, 106.f);
    }

    Tetris::~Tetris()
    {
        delete this->m_background;
        delete this->m_tetromino;
    }

    void Tetris::SetState(const State state)
    {
        this->m_current_state = state;
    }
    void Tetris::Input()
    {
        while (this->GetWindow().pollEvent(this->GetEvent()))
        {
            if (this->GetEvent().type == sf::Event::Closed)
            {
                this->GetWindow().close();
            }
            if (this->GetEvent().type == sf::Event::KeyPressed)
            {
                if (this->GetEvent().key.code == sf::Keyboard::Up)
                {
                    this->SetState(State::ROTATE);
                    //this->Rotate();
                }
                else if (this->GetEvent().key.code == sf::Keyboard::Down)
                {
                    this->SetState(State::ACCELERATED_FALL);
                    //this->SetDelayedFall(DELAYED_FALL_PRESS_DOWN);
                }
                else if (this->GetEvent().key.code == sf::Keyboard::Left)
                {
                    this->SetState(State::MOVE_LEFT);
                    //this->MoveDX(DirectionMovements::LEFT);
                }
                else if (this->GetEvent().key.code == sf::Keyboard::Right)
                {
                    this->SetState(State::MOVE_RIGHT);
                    //this->MoveDX(DirectionMovements::RIGHT);
                }
                else if (this->GetEvent().key.code == sf::Keyboard::R)
                {
                    this->restart();
                }
                else if (this->GetEvent().key.code == sf::Keyboard::Key::Escape)
                {
                    this->GetWindow().close();
                }
                else
                {
                    this->SetState(State::IDLE);
                }
            }
            else if (this->GetEvent().type == sf::Event::KeyReleased)
            {
                if (this->GetEvent().key.code == sf::Keyboard::Down)
                {
                    this->SetState(State::NORMAL_FALL);
                    //this->SetDelayedFall(DELAYED_FALL);
                }
            }
        }
    }
    void Tetris::Update()
    {
        float fall_elapsed_time = this->m_fall_timer.getElapsedTime().asSeconds();
        float tick_elapsed_time = this->m_tick_timer.getElapsedTime().asSeconds();

        if (tick_elapsed_time <= 0.5f)
        {
            switch (this->m_current_state)
            {
            case State::MOVE_LEFT:
                if (this->m_tetromino->PermissibilityMovement(DirectionMovements::LEFT))
                {
                    this->m_tetromino->MovementShape(-1, 0);
                }
                break;
            case State::MOVE_RIGHT:
                if (this->m_tetromino->PermissibilityMovement(DirectionMovements::RIGHT))
                {
                    this->m_tetromino->MovementShape(1, 0);
                }
                break;
            case State::ROTATE:
                this->m_tetromino->Rotate();
                break;
            case State::NORMAL_FALL:
                this->m_current_delayed_fall = DELAYED_FALL;
                break;
            case State::ACCELERATED_FALL:
                this->m_current_delayed_fall = DELAYED_FALL_PRESS_DOWN;
                break;
            default:
                std::cout << "IDLE" << std::endl;
                break;
            }
            if (fall_elapsed_time >= this->m_current_delayed_fall)
            {
                if (this->m_tetromino->PermissibilityMovement(DirectionMovements::FALL))
                {
                    this->m_tetromino->MovementShape(0, 1);
                    this->m_fall_timer.restart();
                }
            }
        }
        else
        {
            if (!this->m_tetromino->PermissibilityMovement(DirectionMovements::FALL))
            {
                this->m_tetromino->AddingShapeToField();
                delete this->m_tetromino;
                this->m_tetromino = new Tetromino;
            }
            this->m_tick_timer.restart();
        }
    }

    void Tetris::Move()
    {
        if (this->m_tetromino->MoveDY())
        {
            delete this->m_tetromino;
            this->m_tetromino = new Tetromino;
        }
    }
    void Tetris::Draw()
    {
        this->m_background->Draw(this->m_window);
        this->m_tetromino->Draw(this->m_window);
        if (!this->AbilityGenerate())
        {
            this->m_window.draw(this->m_gm_sprite);
        }
    }
};