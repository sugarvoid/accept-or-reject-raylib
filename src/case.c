#include "../include/case.h"
#include <stdlib.h>

Case *case_new(int number, int value, int x, int y)
{
    Case *c = (Case *)malloc(sizeof(Case));
    c->number = number;
    c->value = value;
    c->rect = (Rectangle){x, y, 90, 50};
    // c->rect = (RectObject){x, y, 100, 60};
    c->x = x;
    c->y = y;
    c->w = 90; // width of the case
    c->h = 50; // height of the case
    c->hovered = false;
    c->picked = false;
    c->opened = false;
    c->visible = true;
    c->move_t = 500;                 // Default move time (can be used for animations)
    c->end_loc = (Vector2){200, 60}; // Default end location
    c->txt_pos = (Vector2){x + 8, y + 6};

    return c;
}

// Function to check if mouse is hovering over the case
bool is_colliding(int m_x, int m_y, Case *box)
{
    if (m_x < box->x + box->w && m_x > box->x &&
        m_y < box->y + box->h && m_y > box->y)
    {
        return true;
    }
    return false;
}

// Update function to detect hover
void case_update(Case *c, Vector2 mousePos)
{
    c->hovered = CheckCollisionPointRec(mousePos, c->rect);
}

// Handle case click
void case_was_clicked(Case *c)
{
    if (!c->picked)
    {
        c->picked = true;
        c->opened = true;
        // Add your custom game logic here (e.g., handle next round, hide case, etc.)
        TraceLog(LOG_DEBUG, TextFormat("Case %d was clicked! Value: %d\n", c->number, c->value));
        // If necessary, hide the case
        c->visible = false;
    }
}

// Draw the case using Raylib
void case_draw(Case *c)
{
    if (c->visible)
    {
        // Draw the case with hover effect
        // Color current_col = c->hovered ? c->hover_col : c->col;
        DrawRectangle(c->x, c->y, c->w, c->h, c->hovered ? DEFAULT_COLOR : HOVER_COLOR);
        // Draw the number inside the case
        DrawText(TextFormat("%d", c->number), (int)c->txt_pos.x, (int)c->txt_pos.y, 30, c->hovered ? RAYWHITE : DEFAULT_COLOR);
    }
}
