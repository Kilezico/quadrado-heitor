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

    std::vector<Objeto> obstaculos;
    Texture2D pedra;
    int obstaculos_delta = 120;

    int vel = 5;

    Heitor heitor;

    bool isPaused = false;
    bool changeToTitle = false;
    bool first_music = true;

    int pontuacao = 0;
    std::string pontTxt;
    Vector2 pontSize;

    Music musica;
    
    void init()
    {
        // Inicia sons
        musica = LoadMusicStream("resourses/audio/musica.wav");
        PlayMusicStream(musica);
    
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

        // Carrega texturas dos obstáculos
        pedra = LoadTexture("resourses/images/pedra.png");
        
        heitor = Heitor(100, 380);
    }

    void update()
    { 
        if (first_music) {
            PlayMusicStream(musica);
            first_music = false;
        }
        UpdateMusicStream(musica);
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
            // Obstaculos
            for (int i=(int)obstaculos.size()-1; i>=0; i--) {
                obstaculos[i].pos.x -= vel;
                if (obstaculos[i].pos.x <= -obstaculos[i].tex.width) obstaculos.erase(obstaculos.begin()+i);
                // Atualiza a hitbox
                obstaculos[i].hitbox.x = obstaculos[i].pos.x + 15;
                obstaculos[i].hitbox.y = obstaculos[i].pos.y + 20;
                obstaculos[i].hitbox.width = obstaculos[i].tex.width - 30;
                // Colisão entre Heitor e Caixas
                if (CheckCollisionRecs(heitor.getHitbox(), obstaculos[i].hitbox)) {
                    heitor.morre();
                }
            }
            
            obstaculos_delta -= vel;
            if (obstaculos_delta <= 0) {
                obstaculos_delta = GetRandomValue(500, 1000);
                obstaculos.push_back(Objeto(pedra, {(float)GetScreenWidth(), (float)GetScreenHeight()-160}));
            }
            // Heitor
            heitor.update();
            if (IsKeyPressed(KEY_SPACE)) heitor.jump();
            if (heitor.isMorto()) {
                vel = 0;
                PauseMusicStream(musica);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    changeToTitle = true;
                    reset();
                }
            }

            // Pontuação
            pontuacao += vel;
            pontTxt = std::to_string(pontuacao/100);
            pontSize = MeasureTextEx(getFont(), pontTxt.c_str(), 40, 0);
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            isPaused = !isPaused;

            if (isPaused) PauseMusicStream(musica);
            else ResumeMusicStream(musica);
        }
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
        // Obstáculos
        for (Objeto obstaculo: obstaculos) {
            obstaculo.draw();
            DrawRectangleLinesEx(obstaculo.hitbox, 1, RED);
        }


        heitor.draw();
        DrawRectangleLinesEx(heitor.getHitbox(),  2, RED);

        // DrawTextEx(getFont(), pontTxt.c_str(), {GetScreenWidth()-pontSize.x-10, 10}, 40, 0, WHITE);
        DrawTextLines(getFont(), pontTxt.c_str(), {GetScreenWidth()-(pontSize.x/2.0f)-5, pontSize.y/2.0f+5},
            0, 40, 0, WHITE, BLACK, 4);

        if (isPaused) { // Pra desenhar as coisas da tela de pausa
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 50});
            DrawTextLines(getFont(), "PAUSADO",
                {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, 0, 30, 5, BLACK, WHITE, 1);    
            // DrawTextCenter(getFont(), "PAUSADO",
                // {(float)GetScreenWidth()/2, (float)GetScreenHeight()/2}, 0, 30, 5, BLACK);
        }
    }

    void reset()
    {
        // musiques
        StopMusicStream(musica);
        first_music = true; // Pra quando voltar de novo, ser a primeira iteração

        heitor.desmorre();
    
        obstaculos.clear();
        obstaculos_delta = 500;

        vel = 5;
        isPaused = false;
        pontuacao = 0;
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