#pragma once

enum class Command {
    Up,
    Down,
    Left,
    Right,
    Quit,
    Esc
};

typedef struct Input_t
{
    Command cmd;
    int mouseX;
    int mouseY;
} Input_s;

class Entity {
    private:
    std::string _sprite;
    int _x;
    int _y;
    bool _visible;
    public:
    Entity(std::string sprite, int x, int y, bool visible = true) : _sprite(sprite), _x(x), _y(y), _visible(visible) {};
    int getX(){return _x;};
    int getY(){return _y;};
    std::string getSprite(){return _sprite;};
    bool isVisible() {return _visible;};
    //need to add sets
};


class IGraphics
{
private:

public:
    virtual Input_s getInput() = 0;
    virtual void clear();
    virtual void render();
    virtual void display();
    virtual ~IGraphics() = default;
};

