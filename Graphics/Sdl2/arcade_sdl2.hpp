/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Arcade
*/

#ifndef ARACADE_SDL2_HPP
    #define ARACADE_SDL2_HPP


    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include "IGraphics.hpp"


namespace arcade {
    class SDL2 : public IGraphicLib
    {
    private:
        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;
        TTF_Font *_font = nullptr;
        bool _initialized = false;
        bool _ttfInitialized = false;
        int _scale = 30;

        SDL_Rect _makeRect(const Entity &entity) const;
    void drawRectangle(const Entity &entity);
        void drawText(const Entity &entity);

    public:
        SDL2();
        ~SDL2() override;

        void openWindow(const std::string &title, Vector2i size);
        bool isOpen() const override;
        void closeWindow();
        std::vector<Event> pollEvents() override;
        void clear() override;
        void drawEntity(const Entity &entity) override;
        void display() override;
    };
}

extern "C" {
    arcade::IGraphicLib *createDisplay();
}

#endif /* ARACADE_SDL2_HPP */