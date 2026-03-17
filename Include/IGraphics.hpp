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
}Input_s;

class IGraphics
{
private:

public:
    virtual Input_s getInput() = 0;
    virtual void clear();
    virtual void display();
    virtual ~IGraphics() = default;
};

