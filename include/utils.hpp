#pragma once

#include <raylib.h>
#include <string>
#include <iostream>

#define G 0.4


typedef enum {
    TITLE, GAME, EXIT
} gameState;

enum gamingState {
    PAUSE, GAMING, END
};

class Objeto
{
public:
    Texture2D tex;
    Vector2 pos;
    Rectangle hitbox;
    Objeto();
    Objeto(Texture2D texture, Vector2 pos);

    void draw();
    void quit();
};

class Butao
{
    Rectangle caixa;
    Rectangle caixaMenor;
    std::string txt;

    bool pressed = false;
    bool clicked = false;
public:
    Butao() {};
    Butao(Rectangle caixa, std::string texto);

    void draw();
    void update();

    bool wasClicked();
};

Font getFont();
Font* getFontPtr();

void DrawTextExCenter(Font font, const char* txt, Vector2 position, float fontSize, float spacing, Color tint);
void DrawTextCenter(Font font, const char* txt, Vector2 position, float rotation, float fontSize, float spacing, Color tint);
void DrawTextLines(Font font, const char* txt, Vector2 position, float rotation, float fontSize, float spacing, Color tint, Color outline, float outlineSize);
Vector2 GetRectangleCenter(Rectangle rect);