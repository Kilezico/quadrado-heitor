#include <raylib.h>
#include <raymath.h>

#include "utils.hpp"
#include "Heitor.hpp"

Heitor::Heitor(int x, int y) 
{
    pos = {(float)x, (float)y};
    pos_inicial = pos;
    // Carrega texturas
    tex = LoadTexture("resourses/images/heitor.png");
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle1.png"));
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle2.png"));
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle3.png"));
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle4.png"));
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle5.png"));
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle6.png"));
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle7.png"));
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle8.png"));
    idleTex.push_back(LoadTexture("resourses/images/idle/heitor-idle9.png"));
    
    runTex.push_back(LoadTexture("resourses/images/run/heitor-run1.png"));
    runTex.push_back(LoadTexture("resourses/images/run/heitor-run2.png"));
    runTex.push_back(LoadTexture("resourses/images/run/heitor-run3.png"));
    runTex.push_back(LoadTexture("resourses/images/run/heitor-run4.png"));
    runTex.push_back(LoadTexture("resourses/images/run/heitor-run5.png"));
    runTex.push_back(LoadTexture("resourses/images/run/heitor-run6.png"));
    runTex.push_back(LoadTexture("resourses/images/run/heitor-run7.png"));
    runTex.push_back(LoadTexture("resourses/images/run/heitor-run8.png"));
    
    texAtual = &tex;

    hitbox.width = (float)tex.width - 50;
    hitbox.height = (float)tex.height - 33;

    heitorState = RUN;

    morte_som = LoadSound("resourses/audio/morre.wav");
    pula_som = LoadSound("resourses/audio/jump.wav");
}

void Heitor::update()
{
    // Dependendo do estado atual:
    switch (heitorState)
    {
    case IDLE:
        idleCount++;
        if (idleCount >= (int)idleTex.size()*idleFrameSpeed) idleCount = 0;
        texAtual = &idleTex[floor(idleCount/idleFrameSpeed)];
        break;
    case RUN:
        runCount++;
        if (runCount >= (int)runTex.size()*runFrameSpeed) runCount = 0;
        texAtual = &runTex[floor(runCount/runFrameSpeed)];
        break;
    case JUMP:
        texAtual = &runTex[floor(runCount/runFrameSpeed)];        
        break;
    default: break;
    }

    if (morto) return;
    
    pos.x += vel.x;
    pos.y += vel.y;

    vel.y += G;

    if (pos.y > 380) { // Tocou no chão
        pos.y = 380;
        vel.y = 0;
        noChao = true;
        heitorState = running ? RUN : IDLE;
    }

    corre_vel += 0.003;
    if (corre_vel > 15) corre_vel = 15;
    runFrameSpeed = runFrameSpeed_ini / (corre_vel / corre_vel_ini);

    hitbox.x = pos.x + 25; // Ajustes feitos manualmente
    hitbox.y = pos.y + 28;
}

void Heitor::draw()
{
    DrawTextureV(*texAtual, pos, WHITE);
}

void Heitor::jump()
{
    if (noChao) {
        heitorState = JUMP;
        vel.y = -12;
        noChao = false;
        // Decide qual pulo usar  
        if (abs(0-runCount) >= abs(runCount-4*runFrameSpeed) &&
            abs(runCount - 4*runFrameSpeed) < abs(runCount - 8*runFrameSpeed))
            runCount = 4*runFrameSpeed;
        else runCount = 0;
        PlaySound(pula_som);
    }
}

void Heitor::run()
{
    heitorState = RUN;
    runCount = 0;
    running = true;
}

void Heitor::idle()
{
    // idleCount = 0;
    heitorState = IDLE;   
    running = false;
}

void Heitor::morre()
{
    corre_vel = 0;
    heitorState = DEAD;
    morto = true;
    PlaySound(morte_som);
}

void Heitor::desmorre()
{
    heitorState = RUN;
    morto = false;
}

void Heitor::reset()
{
    heitorState = RUN;
    pos = pos_inicial;
    vel = {0.0f, 0.0f};
    noChao = false;
    running = true;
    morto = false;
    corre_vel = corre_vel_ini;

    idleCount = 0;
    idleFrameSpeed = 5;
    runCount = 0;
    runFrameSpeed = runFrameSpeed_ini;
}