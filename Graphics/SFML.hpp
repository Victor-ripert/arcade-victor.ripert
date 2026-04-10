#pragma once

#include "../Include/IGraphics.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>



namespace arcade {
    class SFML : public IGraphicLib
    {
    private:
        sf::RenderWindow _window;
        sf::Font _font;
        int _scale = 50;
        sf::Vector2f _makeSize(int w, int h);
        sf::Vector2i _makeSizeInt(int w, int h);
        void drawRectangle(const Entity &entity);
        void drawText(const Entity &entity);
        void drawSprite(const Entity &entity);
        std::unordered_map<std::string, sf::Texture> _textures;
        sf::Texture &_getTexture(const std::string &path);
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