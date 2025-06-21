#include "../include/button.h"
#include <stdlib.h>
#include "../include/rect_object.h"

// Function to create a new button
Button* button_new(char* text, int x, int y, void (*callback)(), Color col) {
    Button* btn = (Button*)malloc(sizeof(Button));
    btn->text = text;
    btn->x = x;
    btn->y = y;
    btn->w = 150; // Button width (customize as needed)
    btn->h = 50;  // Button height (customize as needed)
    btn->rect = (RectObject){x,y,150,50};
    btn->callback = callback;
    btn->col = col;
    btn->is_hovered = false;
    btn->txt_col = BLACK; // Text color (default to black)
    return btn;
}

// Function to check if the mouse is hovering over the button
// bool is_colliding(int m_x, int m_y, Button* box) {
//     if (m_x < box->x + box->w && m_x > box->x &&
//         m_y < box->y + box->h && m_y > box->y) {
//         return true;
//     }
//     return false;
// }


// Function to update the button (check if mouse is hovering)
void button_update(Button* b, Vector2 mousePos) {
    //Vector2 mousePos = GetMousePosition();
    b->is_hovered = is_mouse_colliding( mousePos, &b->rect);
}

// Function to handle button click
void button_was_clicked(Button* btn) {
    if (btn->callback) {
        btn->callback();  // Call the callback function
        TraceLog(LOG_INFO, "button clicked");
    }
}

// Function to draw the button (using Raylib drawing functions)
void button_draw(Button* btn) {
    if (btn->is_hovered) {
        // Change the button color when hovered (for visual effect)
        DrawRectangle(btn->x, btn->y, btn->w, btn->h, GRAY);
    } else {
        // Draw the button with its normal color
        DrawRectangle(btn->x, btn->y, btn->w, btn->h, btn->col);
    }

    // Draw the button text
    Vector2 textSize = MeasureTextEx(GetFontDefault(), btn->text, 20, 1);
    Vector2 textPosition = { btn->x + (btn->w - textSize.x) / 2, btn->y + (btn->h - textSize.y) / 2 };
    DrawTextEx(GetFontDefault(), btn->text, textPosition, 20, 1, btn->txt_col);
}
