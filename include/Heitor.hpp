#pragma once

#include <raylib.h>
#include <vector>


#include "utils.hpp"


class Heitor
{
    Vector2 pos;
    Rectangle hitbox;

    Vector2 vel = {0.0f, 0.0f};
    bool noChao = false;
    bool running = true;

    Texture2D* texAtual;
    Texture2D tex;
    std::vector<Texture2D> idleTex;
    int idleCount = 0;
    int idleFrameSpeed = 5;
    std::vector<Texture2D> runTex;
    int runCount = 0;
    int runFrameSpeed = 4;

    enum hState{IDLE, RUN, JUMP} heitorState;

public:
    Heitor(int x, int y);
    Heitor() {};

    void draw();
    void update();

    void jump();
    void run();
    void idle();

    Rectangle getHitbox() { return hitbox; }
};