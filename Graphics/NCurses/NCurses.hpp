#pragma once

#include "../Include/IGraphics.hpp"

#include <ncurses.h>
#include <unordered_map>

namespace arcade {
class NCurses : public IGraphicLib {

private:
    WINDOW *_window;
    bool _isOpen;
    int _scale = 1;
    std::pair<int, int> _makeSize(int w, int h);
    std::pair<int, int> _makeSizeInt(int w, int h);
    void drawRectangle(const Entity &entity);
    void drawText(const Entity &entity);
    int _getColorPair(const Color &color);

public:
    void openWindow(const std::string &title, Vector2i size);
    bool isOpen() const;
    void closeWindow();
    std::vector<Event> pollEvents();
    void clear();
    void drawEntity(const Entity &entity);
    void display();
    NCurses(/* args */);
    ~NCurses();
};

extern "C" {
    arcade::IGraphicLib *createDisplay() {
        return new arcade::NCurses();
    };
}

} // namespace arcade
