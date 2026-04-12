#pragma once

#include "../../Include/Arcade.hpp"
#include "../../Include/IGame.hpp"
#include <deque>

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
        Food,
        Unkown
    };

    class Nibbler : public IGame
    {
    private:
        std::vector<std::vector<CellType>> _map;
        std::vector<Entity> _entities;
        Vector2i _dir = {-1, 0};
        Vector2i _dir_wanted = {-1, 0};
        std::deque<Vector2i> _snake;
        CellType moveType(const int &y, const int &x);
        bool openCell(const int &y, const int &x);
        void updateSnake();
        void loadmap();
        void moveSnake(int newX, int newY);
        void feedSnake(int newX, int newY);
        bool handleWall();
        CellType getType(char &c);
        void nextLevel();
        void startMenu(const std::vector<Event> &events);
        void endMenu(const std::vector<Event> &events);
        Entity makeText(const std::string &text, Vector2i pos, Vector2i size);
        void updateEntities();
        int _food = 0;
        int _lvl = 0;
        float _move_timer = 0;
        float _move_at = 0.2;
        int _score = 0;
        bool _start = true;
        bool _end_game = false;
        bool _next_lvl = false;
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
extern "C" {
    arcade::IGame *createGame() {
        return new arcade::Nibbler();
    };
}


