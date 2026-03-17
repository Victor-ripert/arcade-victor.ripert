#pragma once

#include "IGraphics.hpp"

class IGame
{
public:
    virtual void updateGame(Input_s) = 0;
    virtual void draw(IGraphics *) = 0;
    virtual ~IGame() = default;
};
