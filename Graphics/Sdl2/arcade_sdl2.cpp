/*
** EPITECH PROJECT, 2026
** Victor.ripert@epitech.eu
** File description:
** Arcade SDL2 backend
*/

#include "arcade_sdl2.hpp"

#include <algorithm>

namespace {
    arcade::Key makeKey(SDL_Keycode keyCode)
    {
        switch (keyCode) {
            case SDLK_UP: return arcade::Key::Up;
            case SDLK_DOWN: return arcade::Key::Down;
            case SDLK_LEFT: return arcade::Key::Left;
            case SDLK_RIGHT: return arcade::Key::Right;
            case SDLK_RETURN:
            case SDLK_KP_ENTER: return arcade::Key::Confirm;
            case SDLK_ESCAPE: return arcade::Key::Cancel;
            case SDLK_TAB: return arcade::Key::NextGraphics;
            case SDLK_BACKSPACE: return arcade::Key::PrevGraphics;
            case SDLK_n: return arcade::Key::NextGame;
            case SDLK_p: return arcade::Key::PrevGame;
            case SDLK_r: return arcade::Key::RestartGame;
            case SDLK_m: return arcade::Key::BackToMenu;
            case SDLK_q: return arcade::Key::Quit;
            default: return arcade::Key::Unknown;
        }
    }

    arcade::Event makeEvent(const SDL_Event &event)
    {
        switch (event.type) {
            case SDL_QUIT:
                return {arcade::EventType::Closed, arcade::Key::Unknown};
            case SDL_KEYDOWN:
                return {arcade::EventType::KeyPressed, makeKey(event.key.keysym.sym)};
            case SDL_KEYUP:
                return {arcade::EventType::KeyReleased, makeKey(event.key.keysym.sym)};
            default:
                return {};
        }
    }
}

namespace arcade {
    SDL2::SDL2() = default;

    SDL2::~SDL2()
    {
        closeWindow();
    }

    void SDL2::openWindow(const std::string &title, Vector2i size)
    {
        if (!_initialized) {
            if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                return;
            }
            _initialized = true;
        }

        if (!_ttfInitialized) {
            if (TTF_Init() != 0) {
                SDL_Quit();
                _initialized = false;
                return;
            }
            _ttfInitialized = true;
        }

        if (_window != nullptr) {
            closeWindow();
            if (!_initialized) {
                if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                    return;
                }
                _initialized = true;
            }
        }

        _window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            size.x * _scale,
            size.y * _scale,
            SDL_WINDOW_SHOWN
        );
        if (_window == nullptr) {
            SDL_Quit();
            _initialized = false;
            return;
        }

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (_renderer == nullptr) {
            SDL_DestroyWindow(_window);
            _window = nullptr;
            SDL_Quit();
            _initialized = false;
            if (_ttfInitialized) {
                TTF_Quit();
                _ttfInitialized = false;
            }
            return;
        }

        if (_font != nullptr) {
            TTF_CloseFont(_font);
            _font = nullptr;
        }
        _font = TTF_OpenFont("Graphics/assets/ARCADE_I.TTF", 24);
        if (_font == nullptr) {
            closeWindow();
        }
    }

    bool SDL2::isOpen() const
    {
        return _window != nullptr && _renderer != nullptr;
    }

    void SDL2::closeWindow()
    {
        if (_font != nullptr) {
            TTF_CloseFont(_font);
            _font = nullptr;
        }
        if (_renderer != nullptr) {
            SDL_DestroyRenderer(_renderer);
            _renderer = nullptr;
        }
        if (_window != nullptr) {
            SDL_DestroyWindow(_window);
            _window = nullptr;
        }
        if (_initialized) {
            SDL_Quit();
            _initialized = false;
        }
        if (_ttfInitialized) {
            TTF_Quit();
            _ttfInitialized = false;
        }
    }

    std::vector<Event> SDL2::pollEvents()
    {
        std::vector<Event> events;
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            Event converted = makeEvent(event);
            if (converted.type != EventType::None) {
                events.push_back(converted);
            }
        }
        return events;
    }

    void SDL2::clear()
    {
        if (_renderer == nullptr) {
            return;
        }
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
    }

    SDL_Rect SDL2::_makeRect(const Entity &entity) const
    {
        return SDL_Rect {
            entity.position.x * _scale,
            entity.position.y * _scale,
            entity.size.x * _scale,
            entity.size.y * _scale
        };
    }

    void SDL2::drawRectangle(const Entity &entity)
    {
        if (_renderer == nullptr) {
            return;
        }

        const SDL_Rect rect = _makeRect(entity);
        SDL_SetRenderDrawColor(_renderer, entity.color.r, entity.color.g, entity.color.b, entity.color.a);
        SDL_RenderFillRect(_renderer, &rect);
    }

    void SDL2::drawText(const Entity &entity)
    {
        if (_renderer == nullptr || _font == nullptr || entity.text.empty()) {
            return;
        }

        const int pixelHeight = static_cast<int>(entity.size.y * _scale * 0.7f);
        TTF_SetFontSize(_font, pixelHeight);

        SDL_Color color {
            entity.color.r,
            entity.color.g,
            entity.color.b,
            entity.color.a
        };
        SDL_Surface *surface = TTF_RenderUTF8_Blended(_font, entity.text.c_str(), color);
        if (surface == nullptr) {
            return;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        if (texture == nullptr) {
            SDL_FreeSurface(surface);
            return;
        }

        SDL_Rect dst {
            entity.position.x * _scale,
            entity.position.y * _scale,
            surface->w,
            surface->h
        };

        SDL_FreeSurface(surface);
        SDL_RenderCopy(_renderer, texture, nullptr, &dst);
        SDL_DestroyTexture(texture);
    }

    void SDL2::drawEntity(const Entity &entity)
    {
        switch (entity.type) {
            case EntityType::Rectangle:
                drawRectangle(entity);
                break;
            case EntityType::Text:
                drawText(entity);
                break;
            case EntityType::Sprite:
            default:
                break;
        }
    }

    void SDL2::display()
    {
        if (_renderer != nullptr) {
            SDL_RenderPresent(_renderer);
        }
    }
}

extern "C" arcade::IGraphicLib *createDisplay()
{
    return new arcade::SDL2();
}
