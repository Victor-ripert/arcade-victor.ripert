#include "../Include/Core.hpp"
#include "../Include/IGame.hpp"
#include "../Include/IGraphics.hpp"
#include "../Include/DLLoader.hpp"


Core::Core(const char *path) {
    _graphicsLoader.load(path);
}
void Core::run() {
    while (_open) {
        _input = _graphics->getInput();
        _graphics->clear();
        //func to check input for quit, or swap game
        _game->updateGame(_input);
        _game->draw(_graphics.get());
        _graphics->display();
    }
}