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
        _font.loadFromFile("Graphics/assets/ARCADE_I.TTF");
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

    sf::Vector2i SFML::_makeSizeInt(int w, int h) {
        return sf::Vector2i((w * _scale), (h * _scale));
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


    sf::Texture &SFML::_getTexture(const std::string &path)
    {
        auto it = _textures.find(path);
        if (it == _textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile(path)) {
                _textures[path] = sf::Texture();
            } else {
                texture.setSmooth(true);
                _textures[path] = std::move(texture);
            }
        }
        return _textures[path];
    }

    void SFML::drawSprite(const Entity &entity)
    {
        sf::Texture &texture = _getTexture(entity.spriteId);

        sf::Sprite sprite(texture);

        sprite.setTextureRect(sf::IntRect(
            {0, 0},
            {static_cast<int>(texture.getSize().x),
            static_cast<int>(texture.getSize().y)}
        ));

        sf::Vector2f texSize(texture.getSize());
        sprite.setScale({
            (entity.size.x * _scale) / texSize.x,
            (entity.size.y * _scale) / texSize.y
        });

        sprite.setPosition(_makeSize(entity.position.x, entity.position.y));
        sprite.setColor(sf::Color( entity.color.r, entity.color.g, entity.color.b, entity.color.a));

        _window.draw(sprite);
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

        float pixelH = entity.size.y * _scale * 0.7;
        text.setCharacterSize(pixelH);
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
            drawSprite(entity);
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
