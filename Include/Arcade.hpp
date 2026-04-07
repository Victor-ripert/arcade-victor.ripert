#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace arcade {
    enum class Key {
        Unknown = 0,
        Up, Down, Left, Right,
        Confirm, Cancel,
        NextGraphics, PrevGraphics,
        NextGame, PrevGame,
        RestartGame, BackToMenu, Quit
    };

    enum class EventType {
        None = 0,
        KeyPressed, KeyReleased, Closed
    };

    struct Event {
        EventType type = EventType::None;
        Key key = Key::Unknown;
    };

    struct Vector2i {
        int x = 0;
        int y = 0;
    };

    struct Color {
        std::uint8_t r = 0;
        std::uint8_t g = 0;
        std::uint8_t b = 0;
        std::uint8_t a = 255;
    };

    enum class EntityType {
        Rectangle,
        Text,
        Sprite
    };

    struct Entity {
        EntityType type = EntityType::Rectangle;
        Vector2i position {0, 0};
        Vector2i size {1, 1};
        Color color {255, 255, 255, 255};
        std::string text;
        std::string spriteId;
    };
}