#include "Nibbler.hpp"
#include <fstream>
#include <iostream>

namespace arcade {
    CellType getType(char &c) {
        std::cout << c;
        switch (c)
        {
        case '#': return CellType::Wall;
        case '>': return CellType::Head;
        case 'o': return CellType::Body;
        case ' ': return CellType::Nothing;
        case 'f': return CellType::Food;
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
                _map[y][x] = getType(line.at(x));
            }
            std::cout << std::endl;
            y++;
        }
    }

    Nibbler::Nibbler() {
        loadmap();
    }


    void Nibbler::reset() {}

    void moveSnake(Event &Event) {

    }

    void arcade::Nibbler::update(double deltaTime, const std::vector<Event> &events)
    {
        (void)deltaTime;
        (void)events;
    }

    const std::vector<Entity> &arcade::Nibbler::getEntities() const
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