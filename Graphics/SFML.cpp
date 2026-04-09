#include "SFML.hpp"
#include <optional>



// enum class Key {
//     Unknown = 0,
//     Up, Down, Left, Right,
//     Confirm, Cancel,
//     NextGraphics, PrevGraphics,
//     NextGame, PrevGame,
//     RestartGame, BackToMenu, Quit
// };

// enum class EventType {
//     None = 0,
//     KeyPressed, KeyReleased, Closed
// };

// struct Event {
//     EventType type = EventType::None;
//     Key key = Key::Unknown;
// };



namespace arcade
{
    SFML::SFML(/* args */) {
        _font.loadFromFile("Graphics/ARCADE_I.TTF");
    }
    bool SFML::isOpen() const {
        return _window.isOpen();
    }
    void SFML::closeWindow() {
        _window.close();
    }
    sf::Vector2f SFML::_makeSize(int w, int h) {
        return sf::Vector2f(
            static_cast<float>(w * _scale),
            static_cast<float>(h * _scale)
        );
    }

    void SFML::openWindow(const std::string &title, Vector2i size) {
        _window.create(sf::VideoMode(size.x * _scale, size.y * _scale),title);
    }

    Key makeKey(sf::Keyboard::Key sfKey) {
        switch (sfKey) {
            case sf::Keyboard::Up:     return Key::Up;
            case sf::Keyboard::Down:   return Key::Down;
            case sf::Keyboard::Left:   return Key::Left;
            case sf::Keyboard::Right:  return Key::Right;
            case sf::Keyboard::Return: return Key::Confirm;
            case sf::Keyboard::Escape: return Key::Cancel;
            case sf::Keyboard::Tab:    return Key::NextGraphics;
            case sf::Keyboard::BackSpace: return Key::PrevGraphics;
            case sf::Keyboard::N:      return Key::NextGame;
            case sf::Keyboard::P:      return Key::PrevGame;
            case sf::Keyboard::R:      return Key::RestartGame;
            case sf::Keyboard::M:      return Key::BackToMenu;
            case sf::Keyboard::Q:      return Key::Quit;
            default:                   return Key::Unknown;
        }
    }

    Event makeEvent(const sf::Event &sfEvent) {
        switch (sfEvent.type) {
            case sf::Event::Closed:
                return Event{EventType::Closed, Key::Unknown};
            case sf::Event::KeyPressed:
                return Event{EventType::KeyPressed, makeKey(sfEvent.key.code)};
            case sf::Event::KeyReleased:
                return Event{EventType::KeyReleased, makeKey(sfEvent.key.code)};
            default:
                return Event{};
        }
    }

    std::vector<Event> SFML::pollEvents() {
        std::vector<Event> events;
        sf::Event sfEvent;

        while (_window.pollEvent(sfEvent)) {
            Event e = makeEvent(sfEvent);
            if (e.type != EventType::None)
                events.push_back(e);
        }
        return events;
    }

    void SFML::clear() {
        _window.clear();
    };

    void SFML::drawRectangle(const Entity &entity) {
        sf::RectangleShape rectangle(_makeSize(entity.size.x, entity.size.y));
        rectangle.setFillColor(sf::Color(entity.color.r, entity.color.g, entity.color.b, entity.color.a));
        rectangle.setPosition(_makeSize(entity.position.x, entity.position.y));
        _window.draw(rectangle);
    }
    void SFML::drawText(const Entity &entity) {
        sf::Text text;
        text.setFont(_font);
        text.setString(entity.text);
        text.setFillColor(sf::Color(
            entity.color.r,
            entity.color.g,
            entity.color.b,
            entity.color.a
        ));

        int pixelH = entity.size.y * _scale;
        text.setCharacterSize(std::max(1, pixelH));
        text.setPosition(
            static_cast<float>(entity.position.x * _scale),
            static_cast<float>(entity.position.y * _scale)
        );
        _window.draw(text);
    }

    void SFML::drawEntity(const Entity &entity) {
        switch (entity.type)
        {
        case EntityType::Rectangle:
            drawRectangle(entity);
            break;
        case EntityType::Text:
            drawText(entity);
            break;
        case EntityType::Sprite:
            /* code */
            break;
        default:
            break;
        }
    };

    void SFML::display() {
        _window.display();
    };

    SFML::~SFML() {
        if (_window.isOpen())
        _window.close();
    }
} // namespace arcade
