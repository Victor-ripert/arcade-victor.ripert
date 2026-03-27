#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "Arcade.hpp"

namespace arcade {

    class IGame {
    public:
        virtual ~IGame() = default;
        virtual void reset() = 0;
        virtual void update(double deltaTime, const std::vector<Event> &events) = 0;
        virtual const std::vector<Entity> &getEntities() const = 0;
        virtual std::string getName() const = 0;
        virtual int getScore() const = 0;
        virtual bool isOver() const = 0;
    };

}
