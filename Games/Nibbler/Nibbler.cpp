#include "Nibbler.hpp"
#include <fstream>
#include <iostream>

namespace arcade {
    CellType Nibbler::getType(char &c) {
        // std::cout << c;
        switch (c)
        {
        case '#': return CellType::Wall;
        case 'o': return CellType::Body;
        case ' ': return CellType::Nothing;
        case 'f': _food ++; return CellType::Food;
        default:
        return CellType::Nothing;
        }
    }

    void Nibbler::loadmap() {
        std::string path = "./Games/Nibbler/assets/level_" + std::to_string(_lvl) + ".lvl";
        std::fstream level(path);
        if (!level) {
            std::cout << "cant find level" << std::endl;
            return;
        }
        _map.assign(_max_y, std::vector<CellType>(_max_x, CellType::Nothing));
        _snake.clear();
        _food = 0;
    
        std::string line;
        int y = 0;
        while (std::getline(level, line) && y < _max_y) {
            for (int x = 0; x < (int)line.size() && x < _max_x; x++) {
                char c = line.at(x);
                if (c == 'o') _snake.push_back({x, y});
                else _map[y][x] = getType(c);
            }
            y++;
        }

        for (size_t i = 0; i < _snake.size(); i++) {
            auto &cell = _snake[i];
            _map[cell.y][cell.x] =  CellType::Body;
        }
    }

    Nibbler::Nibbler() {
        loadmap();
    }


    void Nibbler::reset() {
        _lvl = 0;
        _end_game = false;
        _next_lvl = false;
        loadmap();
    }

    void Nibbler::nextLevel() {
        _food = 0;
        _snake.clear();
        _map.clear();
        loadmap();
    }

    CellType Nibbler::moveType(const int &y, const int &x) {
        if(y > _max_y || x > _max_x)
            return CellType::Unkown;
        return _map[y][x];
    }

    bool Nibbler::openCell(const int &y, const int &x) {
        if(y > _max_y || x > _max_x)
            return false;
        switch (_map[y][x])
        {
        case CellType::Nothing: return true;
        case CellType::Food : return true;
        default:
            return false;
        }
    }

    void Nibbler::moveSnake(int newX, int newY) {
        _map[_snake.back().y][_snake.back().x] = CellType::Nothing;
        _snake.pop_back();
        _snake.push_front({newX, newY});
        _map[newY][newX] = CellType::Body;
    }

    void Nibbler::feedSnake(int newX, int newY) {
        _score += 1;
        _food -= 1;
        if (_food == 0) {
            _lvl += 1;
            if (_lvl == 5)
                _end_game = true;
            _next_lvl = true;
        }
        _snake.push_front({newX, newY});
        _map[newY][newX] = CellType::Body;
    }

    bool Nibbler::handleWall() {
        Vector2i head = _snake.front();
        bool check1 = false;
        bool check2 = false;
        Vector2i temp;
        if (_dir.x == 0) {
            if (openCell(head.y, head.x + 1)) {
                temp = {1, 0};
                check1 = true;
            }
            if (openCell(head.y, head.x - 1)) {
                temp = {-1, 0};
                check2 = true;
            }
        } else {
            if (openCell(head.y + 1, head.x)) {
                temp = {0, 1};
                check1 = true;
            }
            if (openCell(head.y - 1, head.x)) {
                temp = {0, -1};
                check2 = true;
            }
        }
        if (check1 ^ check2) {
            _dir = temp;
            _dir_wanted = temp;
            return true;
        }
        return false;
    }

    void Nibbler::updateSnake() {
        if (_snake.empty())
            return;
        Vector2i head = _snake.front();
        int checkX = head.x + _dir_wanted.x;
        int checkY = head.y + _dir_wanted.y;
        if (openCell(checkY, checkX))
            _dir = _dir_wanted;
        int newX = head.x + _dir.x;
        int newY = head.y + _dir.y;
        switch (moveType(newY, newX)) {
            case CellType::Wall:
            if (handleWall()) {
                updateSnake();
            }
            return;
            case CellType::Nothing: moveSnake(newX, newY); return;
            case CellType::Food: feedSnake(newX, newY); return;
            case CellType::Body: _end_game = true; return;
            default: return;
        }
    }

    Entity Nibbler::makeText(const std::string &text, Vector2i pos, Vector2i size) {
        Entity e;
        e.type = EntityType::Text;
        e.text = text;
        e.position = pos;
        e.size = size;
        e.color = {255, 255, 255, 255};
        return e;
    }

    void Nibbler::startMenu(const std::vector<Event> &events) {
        for (auto &event : events) {
            if (event.type != EventType::KeyPressed) continue;
            if (event.key == Key::Confirm) {
                _start = false;
                loadmap();
            }
        }
        _entities.clear();
        _entities.push_back(makeText("NIBBLER", {6, 8}, {2, 3}));
        _entities.push_back(makeText("Press ENTER to play", {6, 16}, {1, 1}));
    }

    void Nibbler::endMenu(const std::vector<Event> &events) {
        for (auto &event : events) {
            if (event.type != EventType::KeyPressed)
                continue;
            if (event.key == Key::Confirm) {
                _end_game = false;
                _start = true;
                _score = 0;
                _lvl = 0;
            }
        }
        _entities.clear();
        _entities.push_back(makeText("GAME OVER", {6, 8}, {2, 2}));
        _entities.push_back(makeText("Score: " + std::to_string(_score), {6, 13}, {1, 1}));
        _entities.push_back(makeText("Press ENTER to retry", {6, 18}, {1, 1}));
    }

    void Nibbler::updateEntities() {
        _entities.clear();
        _entities.push_back(makeText("NIBBLER", {1, 0}, {1, 1}));
        _entities.push_back(makeText("Score: " + std::to_string(_score), {15, 0}, {1, 1}));
        for (int y = 0; y < _max_y; y++) {
            for (int x = 0; x < _max_x; x++) {
                if (_map[y][x] == CellType::Nothing)
                    continue;

                Entity e;
                e.position = {x + 1, y + 1};
                e.size = {1, 1};
                e.type = EntityType::Rectangle;

                switch (_map[y][x]) {
                    case CellType::Wall: e.color = arcade::GREY ; break;
                    case CellType::Food: e.color = arcade::RED ; break;
                    case CellType::Body: e.color = arcade::GREEN ; break;
                    // case CellType::Head: e.color = {0, 255, 0, 255}; break;
                    default: continue;
                }
                _entities.push_back(e);
            }
        }
    }


    void Nibbler::update(double deltaTime, const std::vector<Event> &events) {
        if (_start) { startMenu(events); return; }
        if (_end_game) { endMenu(events); return; }

        if (_next_lvl) {
            nextLevel();
            _next_lvl = false;
        }

        for (auto &event : events) {
            if (event.type != EventType::KeyPressed) continue;
            switch (event.key) {
                case Key::Up: if (_dir.y != 1)  _dir_wanted = {0, -1}; break;
                case Key::Down: if (_dir.y != -1) _dir_wanted = {0,  1}; break;
                case Key::Right: if (_dir.x != -1) _dir_wanted = {1,  0}; break;
                case Key::Left: if (_dir.x != 1)  _dir_wanted = {-1, 0}; break;
                default: break;
            }
        }

        _move_timer += deltaTime;
        if (_move_timer >= _move_at) {
            updateSnake();
            // std::cout << _move_timer << std::endl;
            _move_timer = 0;
        }
        updateEntities();
    }

    const std::vector<Entity> &Nibbler::getEntities() const
    {
        return _entities;
    }

    std::string Nibbler::getName() const
    {
        return "Nibbler";
    }

    int Nibbler::getScore() const
    {
        return _score;
    }

    bool Nibbler::isOver() const
    {
        return false;
    }
};