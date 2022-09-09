#include <raylib.h>
#include "utils.hpp"
#include <math.h>
#include <iostream>
#include <string>
// Objeto
Objeto::Objeto() {}
Objeto::Objeto(Texture2D tex, Vector2 pos)
    : tex(tex), pos(pos)
{
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    hitbox.width = (float) tex.width;
    hitbox.height = (float) tex.height;
}


void Objeto::draw()
{
    DrawTextureV(tex, pos, WHITE);
}

void Objeto::quit()
{
    UnloadTexture(tex);
}


Butao::Butao(Rectangle rect, std::string texto) 
    : caixa(rect), txt(texto)
{
    int margem = 5;
    caixaMenor.x = caixa.x + margem;
    caixaMenor.y = caixa.y + margem;
    caixaMenor.width = caixa.width - 2*margem;
    caixaMenor.height = caixa.height - 2*margem;
}

void Butao::draw()
{
    DrawRectangleRec(caixa, RED);
    DrawRectangleRec(caixaMenor, YELLOW);
    if (pressed) DrawRectangleRec(caixaMenor, (Color){0, 0, 0, 70});
    DrawTextCenter(getFont(), txt.c_str(), GetRectangleCenter(caixa), 0, 25, 5, RED);
}

void Butao::update()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), caixa)) {
        pressed = true;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), caixa) && pressed) clicked = true;
        pressed = false;
    }
}

bool Butao::wasClicked()
{
    if (clicked) {
        clicked = false;
        return true;
    } else 
        return false;
}

// Fonte do POU
Font* FONTE;

Font getFont()
{
    if (FONTE == nullptr) FONTE = new Font(LoadFontEx("resourses/Pou.ttf", 100, 0, 250)); 

    return *FONTE;
}

Font* getFontPtr() { return FONTE; }

void DrawTextExCenter(Font font, const char* txt, Vector2 position, float fontSize, float spacing, Color tint)
{
    Vector2 txtSize = MeasureTextEx(font, txt, fontSize, spacing);
    position.x = position.x - txtSize.x/2;
    position.y = position.y - txtSize.y/2;
    DrawTextEx(font, txt, position, fontSize, spacing, tint);
}

void DrawTextCenter(Font font, const char* txt, Vector2 position, float rotation, float fontSize, float spacing, Color tint)
{
    Vector2 txtSize = MeasureTextEx(font, txt, fontSize, spacing);
    DrawTextPro(font, txt, position, {txtSize.x/2.0f, txtSize.y/2.0f}, rotation, fontSize, spacing, tint);
}

void DrawTextLines(Font font, const char* txt, Vector2 position, float rotation, float fontSize, float spacing, Color tint, Color outline, float outlineSize)
{
    Vector2 txtSize = MeasureTextEx(font, txt, fontSize, spacing);

    for (float angle = 0.0f; angle < 2*PI; angle+=PI/8) {
        Vector2 outlinePos = {position.x + (cos(angle) * outlineSize), position.y + (sin(angle) * outlineSize)};
        DrawTextPro(font, txt, outlinePos, {txtSize.x/2.0f, txtSize.y/2.0f},  rotation, fontSize, spacing, outline);
    }

    DrawTextPro(font, txt, position, {txtSize.x/2.0f, txtSize.y/2.0f},  rotation, fontSize, spacing, tint);
}

Vector2 GetRectangleCenter(Rectangle rect)
{
    return {rect.x + rect.width/2, rect.y + rect.height/2};
}