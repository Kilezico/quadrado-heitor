#pragma once
#include "utils.hpp"

namespace title
{
    void init();
    void update();
    void draw();
    
    gameState changeState();
};

namespace game
{
    void init();
    void draw();
    void update();

    gameState changeState();
};