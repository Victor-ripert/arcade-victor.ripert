#include "../Include/Core.hpp"
#include "../Include/IGame.hpp"
#include "../Include/IGraphics.hpp"
#include "../Include/DLLoader.hpp"

namespace arcade {

    Core::Core(const char *path): _open(true) {
        _graphicsLoader.load(path);
    }

    bool Core::_CheckInputs() {
        for (auto &event : _events) {
            switch (event.key)
            {
            case Key::BackToMenu:
                //swap menu
                break;
            case Key::Quit:
                _open = false;
                return true;
            default:
                break;
            }
        }
        return false;
    }

    void Core::run() {
        double deltaTime;
        while (_open) {
            _events = _graphics->pollEvents();
            _graphics->clear();
            if (_CheckInputs()) {
                continue;
            }
            _game->update(deltaTime, _events);
            _graphics->display();
        }
    }
}