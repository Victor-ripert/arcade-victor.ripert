#include "../Include/Core.hpp"
#include "../Include/IGame.hpp"
#include "../Include/IGraphics.hpp"
#include "../Include/DLLoader.hpp"


Core::Core(const char *path): _open(true) {
    _graphicsLoader.load(path);
}

bool Core::_CheckInputs() {
    switch (_input.cmd)
    {
    case Command::Esc:
        //swap menu
        break;
    case Command::Quit:
        _open = false;
        return true;
    default:
        break;
    }
    return false;
}

void Core::run() {
    while (_open) {
        _input = _graphics->getInput();
        _graphics->clear();
        //func to check input for quit, or swap game
        if (_CheckInputs()) {
            continue;
        }
        _game->updateGame(_input);
        _game->draw(_graphics.get());
        _graphics->display();
    }
}