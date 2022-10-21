#pragma once

#include <raylib.h>
#include <vector>


#include "utils.hpp"


class Heitor
{
    Vector2 pos, pos_inicial;
    Rectangle hitbox;

    Vector2 vel = {0.0f, 0.0f};
    bool noChao = false;
    bool running = true;
    bool morto = false;

    float corre_vel_ini = 4.5;
    float corre_vel = corre_vel_ini;

    Texture2D* texAtual;
    Texture2D tex;
    std::vector<Texture2D> idleTex;
    int idleCount = 0;
    int idleFrameSpeed = 5;
    std::vector<Texture2D> runTex;
    int runCount = 0;
    float runFrameSpeed_ini = 6;
    float runFrameSpeed = runFrameSpeed_ini;

    Sound morte_som;
    Sound pula_som;

    enum hState{IDLE, RUN, JUMP, DEAD} heitorState;

public:
    Heitor(int x, int y);
    Heitor() {};

    void draw();
    void update();

    void jump();
    void run();
    void idle();
    void morre();
    void desmorre();
    void reset();

    bool isMorto() { return morto; }
    Rectangle getHitbox() { return hitbox; }
    float getVel() { return corre_vel; }
};