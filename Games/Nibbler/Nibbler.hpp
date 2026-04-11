#pragma once

#include "../../Include/Arcade.hpp"
#include "../../Include/IGame.hpp"

// virtual ~IGame() = default;
// virtual void reset() = 0;
// virtual void update(double deltaTime, const std::vector<Event> &events) = 0;
// virtual const std::vector<Entity> &getEntities() const = 0;
// virtual std::string getName() const = 0;
// virtual int getScore() const = 0;
// virtual bool isOver() const = 0;

namespace arcade {
    class Nibbler : public IGame
    {
    private:
        
    public:
        Nibbler(/* args */);
        ~Nibbler();
    };
    
    Nibbler::Nibbler(/* args */)
    {
    }
    
    Nibbler::~Nibbler()
    {
    }
    

}

