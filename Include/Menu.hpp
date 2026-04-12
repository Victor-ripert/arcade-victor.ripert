#pragma once

#include "../Include/IGame.hpp"
#include "../Include/Arcade.hpp"
#include <dlfcn.h>
#include <filesystem>
#include <vector>
#include <iostream>

namespace arcade {
    const Color RED = {255, 0, 0, 255};
    const Color GREEN = {0, 255, 0, 255};
    const Color BLUE = {0, 0, 255, 255};
    const Color WHITE = {255, 255, 255, 255};
    const Color BLACK = {0, 0, 0, 255};
    const Color YELLOW = {255, 255, 0, 255};
    const Color CYAN = {0, 255, 255, 255};
    const Color MAGENTA = {255, 0, 255, 255};
    const Color ORANGE = {255, 165, 0, 255};
    const Color GREY = {128, 128, 128, 255};
    const Color NONE = {0, 0, 0, 0};
}


namespace arcade {
    class Menu {
        private:
            int _section = 0;
            std::vector<Entity> _entities_game;
            std::vector<Entity> _entities_display;
            std::vector<Entity> _entities_save;
            std::vector<std::string> _games;
            std::vector<std::string> _displays;
            bool _switchRequested = false;
            int _game_idx = 0;
            int _display_idx = 0;
            std::string userName;
            std::string _nextGame;
            std::string _nextGraphic;
            Entity makeText(const std::string &text, int y);
            void updateEntities();
            Entity makeBG(int y);
        public:
            const std::vector<Entity> &getEntities() const;
            void update(double deltaTime, const std::vector<Event> &events);
            bool switchReq() {return _switchRequested;};
            void switchOff() {_switchRequested = false;};
            std::string getNextGame();
            std::string getNextGraphic();
            void setSection(int x) {_section = x;};
            Menu();
            ~Menu();
    };
}

