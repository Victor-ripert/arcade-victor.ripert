#include "../Include/Core.hpp"
#include "../Include/IGame.hpp"
#include "../Include/IGraphics.hpp"
#include "../Include/DLLoader.hpp"

namespace arcade {

    Core::Core(const char *path) : _game(nullptr), _graphics(nullptr) {
        _graphicsLoader.load(path);
        _graphics = _graphicsLoader.getInstance("createDisplay");
        _graphics->openWindow("Arcade", {32, 32});
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
            case Key::RestartGame:
                _game->reset();
                break;
            case Key::NextGame:
                _menu.nextGame();
                break;
            case Key::PrevGame:
                _menu.prevGame();
                break;
            case Key::NextGraphics:
                _menu.nextGraphic();
                break;
            case Key::PrevGraphics:
                _menu.prevGraphic();
                break;
            default:
                break;
            }
        }
        return false;
    }


    void Core::_handleMenuSwitch() {
        if (!_menu.switchReq())
            return;
        std::string nextGame = _menu.getNextGame();
        std::string nextGraphic = _menu.getNextGraphic();
        if (_graphics)
            _graphics->closeWindow();
        _game.reset();
        _graphics.reset();
        _menu.setSection(0);
        if (!nextGame.empty()) {
            _gameLoader.load(nextGame.c_str());
            _game = _gameLoader.getInstance("createGame");
        }
        if (!nextGraphic.empty()) {
            _graphicsLoader.load(nextGraphic.c_str());
            _graphics = _graphicsLoader.getInstance("createDisplay");
        }
        if (!_graphics || !_game) {
            _menu.switchOff();
            if (_graphics)
                _graphics->openWindow("Arcade", Vector2i{32, 32});
            return;
        }
        _graphics->openWindow(_game->getName(), Vector2i{32, 32});
        _menu.switchOff();
        _inMenu = false;
    }

    void Core::run() {
        while (_open) {
            auto now = std::chrono::steady_clock::now();
            double deltaTime = std::chrono::duration<double>(now - _lastTime).count();
            _lastTime = now;
            _events = _graphics->pollEvents();
            _graphics->clear();
            if (_CheckInputs())
                continue;
            _handleMenuSwitch();
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

    Core::~Core() {
        if (_graphics)
            _graphics->closeWindow();
        _game.reset();
        _graphics.reset();
    }
}