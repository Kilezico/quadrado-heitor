#pragma once
#include "utils.hpp"

namespace title
{
    void init();
    void update();
    void draw();
    void reset();

    gameState changeState();
};

namespace game
{
    void init();
    void draw();
    void update();
    void reset();

    gameState changeState();
};