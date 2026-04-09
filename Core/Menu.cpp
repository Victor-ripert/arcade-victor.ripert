#include "../Include/Menu.hpp"

// struct Entity {
//     EntityType type = EntityType::Rectangle;
//     Vector2i position {0, 0};
//     Vector2i size {1, 1};
//     Color color {255, 255, 255, 255};
//     std::string text;
//     std::string spriteId;
// };

namespace arcade {

    Entity Menu::makeText(const std::string &text, int y) {
        Entity new_entity;
        new_entity.color = WHITE;
        new_entity.text = text;
        new_entity.position = {1, y};
        new_entity.size = {18, 1};
        new_entity.type = EntityType::Text;
        return new_entity;
    }

    Entity Menu::makeBG(int y) {
        Entity new_entity;
        new_entity.color = BLACK;
        new_entity.text = "background";
        new_entity.position = {1, y};
        new_entity.size = {18, 1};
        new_entity.type = EntityType::Rectangle;
        return new_entity;
    }

    void Menu::updateEntities() {
        for (size_t i = 0; i < _entities_game.size(); i++) {
            Entity &ent = _entities_game[i];
            if (ent.text == "Games")
                continue;
            if (ent.text == "background" && (i - 1) / 2 == (size_t)_game_idx) {
                    ent.color = arcade::RED;
            } else if (ent.text == "background") {
                    ent.color = arcade::GREY;
                }
        }
        for (size_t i = 0; i < _entities_display.size(); i++) {
            Entity &ent = _entities_display[i];
            if (ent.text == "Displays")
                continue;
            if (ent.text == "background" && (i - 1) / 2 == (size_t)_display_idx) {
                ent.color = arcade::RED;
            } else if (ent.text == "background") {
                ent.color = arcade::GREY;
            }
        }
    };
    const std::vector<Entity> &Menu::getEntities() const {
        if (_section == 0)
            return _entities_game;
        if (_section == 1)
            return _entities_display;
        return _entities_save;
    }

    void Menu::update(double deltaTime, const std::vector<Event> &events) {
        (void) deltaTime;
        for (const auto &event : events) {
            if (event.type != EventType::KeyPressed)
                continue;
            switch (event.key)
            {
            case  Key::Confirm:
                _section = (_section + 1) % 3;
                if (_section == 2)
                    _switchRequested = true;
                break;
            case Key::Up:
                if (_section == 0 && !_games.empty())
                    _game_idx = (_game_idx + 1) % (int)_games.size();
                if (_section == 1 && !_displays.empty())
                    _display_idx = (_display_idx + 1) % (int)_displays.size();
                break;
            case Key::Down:
                if (_section == 0 && !_games.empty())
                    _game_idx = (_game_idx - 1 + (int)_games.size()) % (int)_games.size();
                if (_section == 1 && !_displays.empty())
                    _display_idx = (_display_idx - 1 + (int)_displays.size()) % (int)_displays.size();
                break;
                break;
            default:
                break;
            }
        }
        updateEntities();
    };

    Menu::Menu() {
        std::filesystem::path lib_path = "./lib";
        for (const auto& entry : std::filesystem::directory_iterator(lib_path)) {
            if (entry.path().extension() != ".so")
                continue;

            std::string path = entry.path().string();
            std::cout << path << std::endl;
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle)
                continue;
            if (dlsym(handle, "gameEntryPoint"))
                _games.push_back(path);
            else if (dlsym(handle, "displayEntryPoint"))
                _displays.push_back(path);
            dlclose(handle);
        }
        _entities_game.push_back(makeText("Games", 0));
        int heading_offset = 1;
        for (size_t i = 0; i < _games.size(); i ++) {
            _entities_game.push_back(makeBG(i + heading_offset));
            _entities_game.push_back(makeText(_games[i], i + heading_offset));
        }

        _entities_display.push_back(makeText("Displays", 0));
        heading_offset = 1;
        for (size_t i = 0; i < _displays.size(); i++) {
            _entities_display.push_back(makeBG(i + heading_offset));
            _entities_display.push_back(makeText(_displays[i], i + heading_offset));
        }

        _entities_save.push_back(makeText("SAVE", 0));
    };

    Menu::~Menu() {

    };

    std::string Menu::getNextGame() {
        if (_games.empty()) return "";
        return _games[_game_idx];
    };
    std::string Menu::getNextGraphic() {
        if (_displays.empty()) return "";
        return _displays[_display_idx];
    };
};


// extern "C" {
//     IClass *entryPoint() {
//         std::cout << "crested foo" << std::endl;
//         return new foo();
//     };
// }
