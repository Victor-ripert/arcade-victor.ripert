#pragma once

#include "../Include/IGraphics.hpp"

#include <SFML/Graphics.hpp>

// public:
// virtual ~IGraphicLib() = default;
// virtual void openWindow(const std::string &title, Vector2i size) = 0;
// virtual void closeWindow() = 0;
// virtual bool isOpen() const = 0;
// virtual std::vector<Event> pollEvents() = 0;
// virtual void clear() = 0;
// virtual void drawEntity(const Entity &entity) = 0;
// virtual void display() = 0;
// };



namespace arcade {
    class SFML : public IGraphicLib
    {
    private:
        sf::RenderWindow _window;
        sf::Font _font;
        int _scale = 100;
        sf::Vector2f _makeSize(int w, int h);
        void drawRectangle(const Entity &entity);
        void drawText(const Entity &entity);
    public:
        void openWindow(const std::string &title, Vector2i size);
        bool isOpen() const;
        void closeWindow();
        std::vector<Event> pollEvents();
        void clear();
        void drawEntity(const Entity &entity);
        void display();
        SFML(/* args */);
        ~SFML();
    };
}

extern "C" {
    arcade::IGraphicLib *displayEntryPoint() {
        return new arcade::SFML();
    };
}