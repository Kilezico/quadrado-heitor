#include "Telas.hpp"

#include <raylib.h>
#include <vector>
#include <cmath>

#include "utils.hpp"
#include "Heitor.hpp"

namespace title
{
    std::vector<Objeto> grama;
    Objeto nuvens[3];
    std::vector<Butao> butoes;
    Heitor heitor;

    int vel = 0;
    
    int delta = 0;

    bool changeToGame = false;
    bool exitGame = false;

    void init()
    {
        // Inicia nuvens
        for (int i=0; i<3; i++) {
            nuvens[i] = Objeto(LoadTexture("resourses/images/nuvem2.png"),
                (Vector2){0.0f + i*400.0f, (float)GetRandomValue(50, 100)});
        } 
        
        // Inicia grama
        for (int i=0; i<GetScreenWidth()+64; i += 64) {
            grama.push_back(Objeto(LoadTexture("resourses/images/grama.png"),
                (Vector2){(float)i, (float)GetScreenHeight()-64}));
        }

        butoes.push_back(Butao({555.0f, 300.0f, 250.0f, 50.0f}, "Jogar"));
        butoes.push_back(Butao({555.0f, 370.0f, 250.0f, 50.0f}, "Sair"));
    

        heitor = Heitor(50, 380);
        heitor.idle();   
    }

    void update()
    {
        // Nuvens
        for (int i=0; i<3; i++) {
            nuvens[i].pos.x -= vel + 2;

            if (nuvens[i].pos.x < -nuvens[i].tex.width)
                nuvens[i].pos.x = 1200 - nuvens[i].tex.width;
        }
        
        for (int i=0; i<(int) butoes.size(); i++) {
            butoes[i].update();
        }

        if (butoes[0].wasClicked()) changeToGame = true;
        if (butoes[1].wasClicked()) exitGame = true;
        
        // Heitor
        heitor.update();   
        
        delta++;
    }

    void draw()
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), SKYBLUE);

        // Nuvens
        for (int i=0; i<3; i++) {
            nuvens[i].draw();
        }
        // Grama
        for (Objeto gram: grama) {
            gram.draw();
        }

        for (Butao butao: butoes) {
            butao.draw();
        }

        heitor.draw();
        
        // DrawTextExCenter(getFont(), "O Quadrado Heitor", {(float)GetScreenWidth()/2, 70}, 50, 5, {255, 0, 0, 255});
        DrawTextLines(getFont(), "O Quadrado Heitor",
            {GetScreenWidth()/2.0f, 70}, sin(delta/35.0f)*3, 50, 5, {255, 0, 0, 255}, BLACK, 4);
        if (getPontAnts() > 0) {
            std::string pont_txt = "Pontuação: " + std::to_string(getPontAnts());
            DrawTextEx(getFont(), pont_txt.c_str(), 
                {60.0f, 210.0f}, 23, 3, BLACK);
        }

    }

    gameState changeState()
    {   
        if (changeToGame) {
            changeToGame = false;
            return GAME;
        } else if (exitGame) {
            exitGame = false;
            return EXIT;
        }

        return TITLE;
    }
};