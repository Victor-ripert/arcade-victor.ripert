#pragma once

#include "../../Include/Arcade.hpp"
#include "../../Include/IGame.hpp"
#include <deque>

// virtual ~IGame() = default;
// virtual void reset() = 0;
// virtual void update(double deltaTime, const std::vector<Event> &events) = 0;
// virtual const std::vector<Entity> &getEntities() const = 0;
// virtual std::string getName() const = 0;
// virtual int getScore() const = 0;
// virtual bool isOver() const = 0;

namespace arcade {
    enum class CellType {
        Nothing,
        Wall,
        Body,
        Head,
        Food
    };
    struct Pos {
        int x;
        int y;
    };
    class Nibbler : public IGame
    {
    private:
        std::vector<std::vector<CellType>> _map;
        std::deque<Pos> _snake;
        void moveSnake(Event &Event);
        void loadmap();
        int _lvl = 0;
        int _score;
        int _max_x = 30;
        int _max_y = 30;
    public:
        void update(double deltaTime, const std::vector<Event> &events);
        void reset();
        const std::vector<Entity> &getEntities() const;
        std::string getName() const;
        int getScore() const;
        // bool isOver();
        bool isOver() const;
        Nibbler();
        ~Nibbler() = default;
    };

}

