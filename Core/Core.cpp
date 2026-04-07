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
                _inMenu = true;
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


    void Core::_handleMenuSwitch() {
        if (!_menu.switchReq())
            return;

        _gameLoader.load(_menu.getNextGame().c_str());
        _game = _gameLoader.getInstance("gameEntryPoint");

        _graphicsLoader.load(_menu.getNextGraphic().c_str());
        _graphics = _graphicsLoader.getInstance("displayEntryPoint");

        _menu.switchOff();
        _inMenu = false;
    }

    void Core::run() {
        double deltaTime = 0;
        while (_open) {
            _events = _graphics->pollEvents();
            _graphics->clear();
            if (_CheckInputs())
                continue;

            if (_inMenu) {
                _menu.update(deltaTime, _events);
                _handleMenuSwitch();
                for (auto &ent : _menu.getEntities())
                    _graphics->drawEntity(ent);
            } else {
                _game->update(deltaTime, _events);
                if (_game->isOver())
                    _inMenu = true;
                for (auto &ent : _game->getEntities())
                    _graphics->drawEntity(ent);
            }
            _graphics->display();
        }
    }
}