#pragma once

#include <string>
#include <vector>
#include "Arcade.hpp"

namespace arcade {
    class IGraphicLib {
    public:
        virtual ~IGraphicLib() = default;
        virtual void openWindow(const std::string &title, Vector2i size) = 0;
        virtual void closeWindow() = 0;
        virtual bool isOpen() const = 0;
        virtual std::vector<Event> pollEvents() = 0;
        virtual void clear() = 0;
        virtual void drawEntity(const Entity &entity) = 0;
        virtual void display() = 0;
    };
}

