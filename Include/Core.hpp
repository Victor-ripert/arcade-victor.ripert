#pragma once

#include "IGame.hpp"
#include "IGraphics.hpp"

#include <memory>
#include <string>

class Core
{
private:
    std::unique_ptr<IGame> _game;
    std::unique_ptr<IGraphics> _graphics;
    Input_s _input;
    bool _open;
public:
    Core(const char* graphics_path);

    void run();
    
    ~Core();
};