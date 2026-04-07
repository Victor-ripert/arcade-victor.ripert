#pragma once

#include "IGame.hpp"
#include "IGraphics.hpp"
#include "DLLoader.hpp"
#include "Arcade.hpp"
#include <memory>
#include <string>


namespace arcade {
class Core {
private:
    std::unique_ptr<IGame> _game;
    std::unique_ptr<IGraphicLib> _graphics;
    DLLoader<IGraphicLib> _graphicsLoader;
    DLLoader<IGame> _gameLoader;
    std::vector<Event> _events;
    bool _open;
    bool _CheckInputs();
public:
    Core(const char* graphics_path);

    void run();
    ~Core();
};
}

