#include "Nibbler.hpp"
#include <fstream>
#include <iostream>

namespace arcade {
    CellType Nibbler::getType(char &c) {
        std::cout << c;
        switch (c)
        {
        case '#': return CellType::Wall;
        case '>': return CellType::Head;
        case 'o': return CellType::Body;
        case ' ': return CellType::Nothing;
        case 'f': _food ++; return CellType::Food;
        default:
        return CellType::Nothing;
        }
    }

    void Nibbler::loadmap() {
        std::string path = "./assets/level_" + std::to_string(_lvl) + ".lvl";
        std::fstream level(path);
        if (!level) {
            std::cout << "cant find level" << std::endl;
            return;
        }
        _map.assign(_max_y, std::vector<CellType>(_max_x, CellType::Nothing));
        std::string line;
        int y = 0;
        while (std::getline(level, line) && y < _max_y) {
            for (int x = 0; x < (int)line.size() && x < _max_x; x++) {
                char c = line.at(x);
                if (c == '>' || c == 'o') {
                    _snake.push_back({x, y});
                    _map[y][x] = CellType::Nothing;
                } else {
                    _map[y][x] = getType(c);
                }
            }
            std::cout << std::endl;
            y++;
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
        _snake.push_front(Vector2i{newX, newY});
        _snake.pop_back();
    }

    void Nibbler::feedSnake(int newX, int newY) {
        _score += 1;
        _food -= 1;
        if (_food == 0)
            _next_lvl = true;
        _snake.push_front(Vector2i{newX, newY});
    }

    void Nibbler::updateSnake() {
        Vector2i head = _snake.front();
        int checkX = head.x + _dir_wanted.x;
        int checky = head.y + _dir_wanted.y;
        if (openCell(checky, checkX)) {
            _dir = _dir_wanted;
        }
        int newX = head.x + _dir.x;
        int newY = head.y + _dir.y;
        switch (moveType(newY, newX))
        {
        case CellType::Wall: return;
        case CellType::Nothing: moveSnake(newX, newY); return;
        case CellType::Food: feedSnake(newX, newY); return;
        case CellType::Body: _end_game = true; return;
        }
    }

    void arcade::Nibbler::update(double deltaTime, const std::vector<Event> &events)
    {
        if (_end_game) {
            //end of game score;
            //play again;
            return;
        }
        for (auto &event : events) {
            if (event.type != EventType::KeyPressed)
                continue;;
            switch (event.key)
            {
            case Key::Up : if (_dir.y != 1) _dir = {0, -1}; break;
            case Key::Down : if (_dir.y != -1) _dir = {0, 1}; break;
            case Key::Right : if (_dir.x != 1) _dir = {-1, 0}; break;
            case Key::Left : if (_dir.x != -1) _dir = {1, 0}; break;
            }
        }
        _move_timer += deltaTime;
        if (_move_timer >= _move_at) {
            updateSnake();
            _move_timer = 0;
        }
    }

    const std::vector<Entity> &Nibbler::getEntities() const
    {
        // return _entities;
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