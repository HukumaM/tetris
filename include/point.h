#pragma once 

namespace Tetris
{
    template <typename T>
    class Point
    {
    public:
        T x, y;
        Point(T x_ = T(), T y_ = T()) : x(x_), y(y_) {}
    };
}