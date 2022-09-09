#include <raylib.h>
#include <iostream>
#include <vector>

#include "Telas.hpp"

const int screenWidth = 800;
const int screenHeight = 600;

gameState gameScreen;

void update();
void draw();
void changeGameState();

int main()
{    
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "O Quadrado Heitor");
    InitAudioDevice();

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    
    gameScreen = TITLE;

    title::init();
    game::init();


    bool running = true;
    while(!WindowShouldClose() && running) {
 
        update(); // Atualiza 
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw(); // Desenha

        EndDrawing();

        changeGameState(); // Atualiza o estado atual

        if (gameScreen == EXIT) running = false;
    }

    if (IsWindowFullscreen()) ToggleFullscreen();

    CloseAudioDevice();
    CloseWindow();

    delete getFontPtr();

    return 0;
}

void update()
{
    if (IsKeyPressed(KEY_F)) ToggleFullscreen();

    switch (gameScreen)
    {
    case TITLE:
        title::update();
        break;
    case GAME:
        game::update();
        break;
    default: break;
    }
}

void changeGameState()
{
    switch (gameScreen)
    {
    case TITLE:
        gameScreen = title::changeState();
        break;
    case GAME:
        gameScreen = game::changeState();
        break;
    default: break;
    }
}

void draw()
{
    
    switch (gameScreen)
    {
    case TITLE:
        title::draw();
        break;
    case GAME:
        game::draw();
        break;
    default: break;
    }
}