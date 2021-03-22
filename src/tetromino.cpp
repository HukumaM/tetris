#include "tetromino.h"

namespace Tetris
{

    // TETROMINO

    Tetromino::Tetromino() : m_score(0), delayed_fall(DELAYED_FALL), 
	ability_generate(true)
    {
        srand(static_cast<unsigned>(time(0)));
        int16_t generate_number = 1 + rand() % 7;
        this->m_type = static_cast<Types>(generate_number - 1);
        this->m_color = generate_number;
        this->figure = figures[this->m_type];

        this->m_texture.loadFromFile("textures/tiles.png");
        this->m_sprite.setTexture(this->m_texture);
        this->m_sprite.setTextureRect(sf::IntRect(
		this->m_color * 18, 0, 18, 18));
        this->m_sprite.setScale(SCALE, SCALE);
    }

    void Tetromino::SetDelayedFall(const float value)
    {
        this->delayed_fall = value;
    }

    bool Tetromino::PermissibilityMovement(DirectionMovements direction)
    {
        for (const auto point : this->figure)
        {
            if (point.x + direction >= WIDTH || point.x + direction < 0 || point.y + 1 >= HEIGHT)
            {
                return false;
            }
            else if (field[point.y + 1][point.x] && !direction /*== DirectionMovements::FALL*/)
            {
                return false;
            }
            else if (field[point.y][point.x + direction] && direction /*== DirectionMovements::LEFT || direction == DirectionMovements::RIGHT*/)
            {
                return false;
            }
        }
        return true;
    }

    void Tetromino::MovementShape(int16_t x_offset, int16_t y_offset)
    {
        std::transform(std::begin(this->figure), std::end(this->figure),
                       std::begin(this->figure), [&](auto &point) mutable {
                           return Point<int16_t>(point.x + x_offset,
                                                 point.y + y_offset);
                       });
    }
    void Tetromino::AddingShapeToField()
    {
        for (const auto point : this->figure)
        {
            field[point.y][point.x] = this->m_color;
        }
    }

    void Tetromino::Generator()
    {
        srand(static_cast<unsigned>(time(0)));
        int16_t gen = 1 + rand() % 7;
        this->m_type = static_cast<Types>(gen - 1);
        this->m_color = gen;
        this->figure = figures[this->m_type];
        if (!this->PermissibilityMovement(DirectionMovements::FALL))
        {
            this->ability_generate = false;
        }
    }
    void Tetromino::MoveDX(DirectionMovements direction)
    {
        if (this->PermissibilityMovement(direction))
        {
            for (auto &point : this->figure)
            {
                point.x += direction;
            }
        }
    }
    bool Tetromino::MoveDY()
    {
        if (this->m_clock_fall.getElapsedTime().asSeconds() >= this->delayed_fall)
        {
            if (this->PermissibilityMovement(DirectionMovements::FALL))
            {
                for (auto &point : this->figure)
                {
                    point.y = point.y + 1;
                }
                this->m_clock_fall.restart();
                return false;
            }
            else
            {
                for (const auto point : this->figure)
                {
                    field[point.y][point.x] = this->m_color;
                }
                this->m_clock_fall.restart();
                return true;
            }
        }
        return false;
    }
    void Tetromino::Draw(sf::RenderWindow &window)
    {
        for (auto i{0}; i < HEIGHT; ++i)
        {
            for (auto j{0}; j < WIDTH; ++j)
            {
                if (field[i][j])
                {
                    this->m_sprite.setTextureRect(sf::IntRect(field[i][j] * 18, 0, 18, 18));
                    this->m_sprite.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                    window.draw(this->m_sprite);
                }
            }
        }
        this->m_sprite.setTextureRect(sf::IntRect(this->m_color * 18, 0, 18, 18));
        for (const auto point : this->figure)
        {
            this->m_sprite.setPosition(
                point.x * CELL_SIZE,
                point.y * CELL_SIZE);
            window.draw(this->m_sprite);
        }
    }
    void Tetromino::Rotate()
    {
        switch (this->m_type)
        {
        case Types::O:
            return;
        case Types::I:
            this->rotation_point = Point<float>(
                this->figure.at(1).x + 0.5f,
                this->figure.at(1).y + 0.5f);
            break;
        default:
            this->rotation_point = Point<float>(
                this->figure.at(0).x,
                this->figure.at(0).y);
            break;
        }
        auto state = this->figure;
        for (auto &point : this->figure)
        {
            auto x = point.x - this->rotation_point.x;
            auto y = point.y - this->rotation_point.y;
            point.x = std::ceil(this->rotation_point.x - y);
            point.y = std::ceil(this->rotation_point.y + x);
            if (field[point.y][point.x])
            {
                this->figure = state;
                break;
            }
        }
        for (auto point = std::begin(this->figure); point != std::end(this->figure); ++point)
        {
            if (point->x < 0)
            {
                this->MovementShape(1, 0);
                // for (auto &point_t : this->figure)
                // {
                //     point_t.x += DirectionMovements::RIGHT;
                // }
                point = std::begin(this->figure);
            }
            if (point->x >= WIDTH || field[point->y][point->x])
            {
                this->MovementShape(-1, 0);
                // for (auto &point_t : this->figure)
                // {
                //     point_t.x += DirectionMovements::LEFT;
                // }
                point = std::begin(this->figure);
            }
        }

        //for (size_t i{ 0 }; i < height / 2; ++i) {
        //	for (size_t j{ i }; j < width - i - 1; ++j) {
        //		Point temp = this->tetromino_points[i][j];
        //		this->tetromino_points[i][j] = this->tetromino_points[height - 1 - j][i];
        //		this->tetromino_points[height - 1 - j][i] = this->tetromino_points[height - 1 - i][height - 1 - j];
        //		this->tetromino_points[height - 1 - i][height - 1 - j] = this->tetromino_points[j][height - 1 - i];
        //		this->tetromino_points[j][height - 1 - i] = temp;
        //	}
        //}
    }
    void Tetromino::CleaningLine()
    {
        int16_t number_lines{0};
        for (auto row = std::rbegin(field); row != std::rend(field); ++row)
        {
            if (std::all_of(std::begin(*row), std::end(*row), [](const auto cell) {
                    return cell;
                }))
            {
                std::rotate(row, std::next(row), std::rend(field));
                field.at(0) = std::vector<int16_t>(WIDTH, 0);
                number_lines++;
            }
        }
        this->m_score += SCORING_CHART[number_lines];
        if (number_lines)
        {
            std::cout << this->m_score << std::endl;
            if (!(this->m_score % 500))
            {
                DELAYED_FALL -= 0.01f;
                std::cout << DELAYED_FALL << std::endl;
            }
        }
    }
}
