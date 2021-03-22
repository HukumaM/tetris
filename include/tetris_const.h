#pragma once
#include "point.h"

namespace Tetris
{
//
#define DEBUG
#define HEIGHT_WINDOW 720.f
#define WIDTH_WINDOW 360.f
#define CELL_SIZE WIDTH_WINDOW / 10
#define SCALE CELL_SIZE / 18

#define HEIGHT 20
#define WIDTH 10

    //tetronimo types
    enum Types
    {
        I,
        S,
        Z,
        L,
        J,
        T,
        O
    };

    static float DELAYED_FALL = 0.3f;
    static const float DELAYED_FALL_PRESS_DOWN = 0.01f;
    static const float DELAYED_ROTATE = 0.1f;

    enum State
    {
        IDLE,
        ROTATE,
        ACCELERATED_FALL,
        NORMAL_FALL,
        MOVE_LEFT,
        MOVE_RIGHT
    };
    //
    enum DirectionMovements
    {
        LEFT = -1,
        FALL = 0,
        RIGHT = 1
    };

    const int SCORING_CHART[5] = {0, 100, 300, 500, 800};

    static const std::vector<std::vector<Point<int16_t>>> figures{
        {{3, 0}, {4, 0}, {5, 0}, {6, 0}}, // I
        {{4, 1}, {4, 0}, {5, 0}, {3, 1}}, // S
        {{4, 1}, {3, 0}, {4, 0}, {5, 1}}, // Z
        {{4, 1}, {5, 0}, {3, 1}, {5, 1}}, // L
        {{4, 1}, {3, 0}, {3, 1}, {5, 1}}, // J
        {{4, 1}, {4, 0}, {3, 1}, {5, 1}}, // T
        {{3, 1}, {3, 0}, {4, 0}, {4, 1}}  // O
        // {{0, 1}, {1, 1}, {2, 1}, {3, 1}}, // I
        // {{1, 2}, {1, 1}, {2, 1}, {0, 2}}, // S
        // {{1, 2}, {0, 1}, {1, 1}, {2, 2}}, // Z
        // {{1, 2}, {2, 1}, {0, 2}, {2, 2}}, // L
        // {{1, 2}, {0, 1}, {0, 2}, {2, 2}}, // J
        // {{1, 2}, {1, 1}, {0, 2}, {2, 2}}, // T
        // {{0, 2}, {0, 1}, {1, 1}, {1, 2}}  // O
    };
    static std::vector<std::vector<int16_t>> field(std::vector<std::vector<int16_t>>(HEIGHT, std::vector<int16_t>(WIDTH)));
}
