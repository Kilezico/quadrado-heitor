#include <raylib.h>
#include <vector>

#include "Telas.hpp"
#include "utils.hpp"
#include "Heitor.hpp"

#include <iostream>
#include <string>
#include <cmath>

namespace game
{
    int nuvemCount = 3;
    Objeto nuvens[3];
    std::vector<Objeto> grama;

    int vel = 5;

    Heitor heitor;

    bool isPaused = false;
    bool changeToTitle = false;

    int pontuacao = 0;
    std::string pontTxt;
    Vector2 pontSize;
    
    void init()
    {
        // Inicia nuvens
        for (int i=0; i<nuvemCount; i++) {
            nuvens[i] = Objeto(LoadTexture("resourses/images/nuvem2.png"),
                (Vector2){0.0f + i*400.0f, (float)GetRandomValue(50, 100)});
        } 
        
        // Inicia grama
        for (int i=0; i<GetScreenWidth()+64; i += 64) {
            grama.push_back(Objeto(LoadTexture("resourses/images/grama.png"),
                (Vector2){(float)i, (float)GetScreenHeight()-64}));
        }

        heitor = Heitor(100, 380);
    }

    void update()
    {   
        if (!isPaused) {
            // Nuvens
            for (int i=0; i<nuvemCount; i++) {
                nuvens[i].pos.x -= vel + 2;

                if (nuvens[i].pos.x < -nuvens[i].tex.width)
                    nuvens[i].pos.x = 1200 - nuvens[i].tex.width;
            }
            // Grama
            for (int i=0; i<(int)grama.size(); i++) {
                grama[i].pos.x -= vel;

                if (grama[i].pos.x <= -64) grama[i].pos.x += grama.size() * 64;
            }
            // Heitor
            heitor.update();

            if (IsKeyPressed(KEY_SPACE)) heitor.jump();

            pontuacao += vel;
            pontTxt = std::to_string(pontuacao/100);
            pontSize = MeasureTextEx(getFont(), pontTxt.c_str(), 40, 0);
        }
        if (IsKeyPressed(KEY_ESCAPE)) isPaused = !isPaused;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) changeToTitle = true;
    }

    void draw()
    {   
        // Céu
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SKYBLUE);

        // Nuvens
        for (int i=0; i<nuvemCount; i++) {
            nuvens[i].draw();
        }
        // Grama
        for (Objeto gram: grama) {
            gram.draw();
        }

        heitor.draw();

        // DrawTextEx(getFont(), pontTxt.c_str(), {GetScreenWidth()-pontSize.x-10, 10}, 40, 0, WHITE);
        DrawTextLines(getFont(), pontTxt.c_str(), {GetScreenWidth()-(pontSize.x/2.0f)-5, pontSize.y/2.0f+5},
            0, 40, 0, WHITE, BLACK, 4);

        if (isPaused) { // Pra desenhar as coisas da tela de pausa
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 50});
            DrawTextCenter(getFont(), "PAUSADO",
                {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, 0, 30, 5, BLACK);
        }
    }

    gameState changeState()
    {
        if (changeToTitle) {
            changeToTitle = false;
            return TITLE;
        }

        return GAME;
    }
};