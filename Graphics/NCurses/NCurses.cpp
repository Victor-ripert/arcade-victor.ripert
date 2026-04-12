#include "NCurses.hpp"

namespace arcade
{

    static int _nearestNcursesColor(int r, int g, int b)
    {
        return (r > 85 ? 1 : 0) | (g > 85 ? 2 : 0) | (b > 85 ? 4 : 0);
    }

    NCurses::NCurses(/* args */) : _window(nullptr), _isOpen(false) {}

    bool NCurses::isOpen() const {
        return _isOpen;
    }

    void NCurses::closeWindow() {
        if (_window && _window != stdscr)
            delwin(_window);
        endwin();
        _isOpen = false;
    }

    std::pair<int, int> NCurses::_makeSize(int w, int h) {
        return {w * _scale, h * _scale};
    }

    std::pair<int, int> NCurses::_makeSizeInt(int w, int h) {
        return {w * _scale, h * _scale};
    }

    void NCurses::openWindow(const std::string &title, Vector2i size) {
        (void)title;
        (void)size;
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);
        if (has_colors()) {
            start_color();
            for (int i = 0; i < 8; i++)
                init_pair(i + 1, i, COLOR_BLACK);
        }
        _window = stdscr;
        _isOpen = true;
    }

    Key makeKey(int ch) {
        switch (ch) {
            case KEY_UP:        return Key::Up;
            case KEY_DOWN:      return Key::Down;
            case KEY_LEFT:      return Key::Left;
            case KEY_RIGHT:     return Key::Right;
            case '\n':
            case KEY_ENTER:     return Key::Confirm;
            case 27:            return Key::Cancel;
            case '\t':          return Key::NextGraphics;
            case KEY_BACKSPACE:
            case 127:           return Key::PrevGraphics;
            case 'n': case 'N': return Key::NextGame;
            case 'p': case 'P': return Key::PrevGame;
            case 'r': case 'R': return Key::RestartGame;
            case 'm': case 'M': return Key::BackToMenu;
            case 'q': case 'Q': return Key::Quit;
            default:            return Key::Unknown;
        }
    }

    std::vector<Event> NCurses::pollEvents() {
        std::vector<Event> events;
        int ch;

        while ((ch = wgetch(_window)) != ERR) {
            if (ch == KEY_RESIZE)
                continue;
            Event e{EventType::KeyPressed, makeKey(ch)};
            if (e.key != Key::Unknown)
                events.push_back(e);
        }

        return events;
    }

    void NCurses::clear() {
        werase(_window);
    }

    int NCurses::_getColorPair(const Color &color) {
        int nc = _nearestNcursesColor(color.r, color.g, color.b);
        return nc + 1;
    }

    void NCurses::drawRectangle(const Entity &entity) {
        auto [x, y] = _makeSize(entity.position.x, entity.position.y);
        auto [w, h] = _makeSize(entity.size.x, entity.size.y);
        int pair = _getColorPair(entity.color);

        wattron(_window, COLOR_PAIR(pair));
        for (int row = y; row < y + h; row++) {
            for (int col = x; col < x + w; col++) {
                mvwaddch(_window, row, col, ' ' | A_REVERSE);
            }
        }
        wattroff(_window, COLOR_PAIR(pair));
    }

    void NCurses::drawText(const Entity &entity) {
        auto [x, y] = _makeSize(entity.position.x, entity.position.y);
        int pair = _getColorPair(entity.color);

        wattron(_window, COLOR_PAIR(pair));
        mvwprintw(_window, y, x, "%s", entity.text.c_str());
        wattroff(_window, COLOR_PAIR(pair));
    }

    void NCurses::drawEntity(const Entity &entity) {
        switch (entity.type) {
            case EntityType::Rectangle:
            case EntityType::Sprite:
                drawRectangle(entity);
                break;
            case EntityType::Text:
                drawText(entity);
                break;
            default:
                break;
        };
    }

    void NCurses::display() {
        wrefresh(_window);
    };

    NCurses::~NCurses() {
        if (_isOpen)
            closeWindow();
    }

} // namespace arcade