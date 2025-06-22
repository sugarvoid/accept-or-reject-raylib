#include "../include/button.h"
#include <stdlib.h>
#include "../include/rect_object.h"

//TODO: Replace x and y with Vector2
Button *button_new(char *text, int x, int y, void (*callback)(), Color col)
{
    Button *btn = malloc(sizeof(Button));
    if (!btn)
    {
        return NULL;
    }
    btn->text = text;
    btn->x = x;
    btn->y = y;
    btn->w = 150;
    btn->h = 50;
    btn->rect = (RectObject){x, y, 150, 50};
    btn->callback = callback;
    btn->col = col;
    btn->is_hovered = false;
    btn->txt_col = BLACK;
    btn->textSize = MeasureTextEx(GetFontDefault(), btn->text, 20, 1);
    btn->textPosition = (Vector2){btn->x + (btn->w - btn->textSize.x) / 2, btn->y + (btn->h - btn->textSize.y) / 2};
    return btn;
}

void button_update(Button *b, Vector2 mousePos)
{
    b->is_hovered = is_mouse_colliding(mousePos, &b->rect);
}

void button_was_clicked(Button *btn)
{
    if (btn->callback)
    {
        btn->callback();
        TraceLog(LOG_INFO, "button clicked");
    }
}

void button_draw(Button *btn)
{

    DrawRectangle(btn->x, btn->y, btn->w, btn->h, btn->is_hovered ? GRAY : btn->col);

    // if (btn->is_hovered) {
    //     DrawRectangle(btn->x, btn->y, btn->w, btn->h, GRAY);
    // } else {
    //     DrawRectangle(btn->x, btn->y, btn->w, btn->h, btn->col);
    // }

    DrawTextEx(GetFontDefault(), btn->text, btn->textPosition, 20, 1, btn->txt_col);
}
