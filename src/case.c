#include "../include/case.h"
#include "../include/globals.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Case *case_new(int number, int value, int x, int y) {
  Case *c = malloc(sizeof(Case));
  if (!c)
    return NULL;
  c->number = number;
  c->value = value;
  c->rect = (Rectangle){x, y, CASE_WIDTH, CASE_HEIGHT};
  // c->x = x;
  // c->y = y;
  c->position = (Vector2){x, y};
  // c->w = CASE_WIDTH;  // width of the case
  // c->h = CASE_HEIGHT; // height of the case
  c->interactable = true;
  c->selected = false;
  c->hovered = false;
  c->picked = false;
  c->opened = false;
  c->visible = true;
  // c->move_t = 500; // Default move time (can be used for animations)
  //  c->end_loc = (Vector2){200, 60}; // Default end location
  c->txt_pos = (Vector2){x + 8, y + 6};

  return c;
}

// Case get_case(int xPos, int yPos, int value)
// {
//     Case c = {
//         .rect = (Rectangle){xPos, yPos, 64, 64},
//         .number = 5,
//         .value = value,
//         .position = (Vector2){xPos, yPos},
//         .x = 3,
//         .y = 2,
//         .w = 64,
//         .h = 64,
//         .hovered = false,
//         .picked = false,
//         .visible = true,
//         .opened = false,
//         .txt_pos = (Vector2){108, 108},
//         .move_t = 30,
//         .end_loc = (Vector2){200, 200}};
//     return c;
// }

// Function to check if mouse is hovering over the case
// bool is_colliding(int m_x, int m_y, Case *box) {
//   if (m_x < box->x + box->w && m_x > box->x && m_y < box->y + box->h &&
//       m_y > box->y) {
//     return true;
//   }
//   return false;
// }

// Update function to detect hover
void UpdateCase(Case *c, Vector2 mousePos) {
  c->hovered = CheckCollisionPointRec(mousePos, c->rect);
}

// Handle case click
void OnCaseClick(Case *c) {
  // if (playerCaseNumber == 0)
  if (playerCase == NULL) {
    // TODO: Set player's case here.
    // playerCase = c;
    return;
  } else {
    if (!c->picked && !c->selected) {
      OpenCase(c);
    }
  }
}

// Draw the case using Raylib
void DrawCase(Case *c) {
  if (c->visible) {
    // Draw the case with hover effect
    // Color current_col = c->hovered ? c->hover_col : c->col;
    if (c->selected) {
      DrawRectangleLinesEx(
          (Rectangle){c->position.x, c->position.y, CASE_WIDTH, CASE_HEIGHT}, 3,
          TEXT_BLUE);
      // Draw the number inside the case
      DrawText(TextFormat("%d", c->number), (int)c->txt_pos.x,
               (int)c->txt_pos.y, 30, TEXT_BLUE);
    } else {
      DrawRectangleLinesEx(
          (Rectangle){c->position.x, c->position.y, CASE_WIDTH, CASE_HEIGHT}, 3,
          c->hovered ? HOVER_COLOR : DEFAULT_COLOR);
      // Draw the number inside the case
      DrawText(TextFormat("%d", c->number), (int)c->txt_pos.x,
               (int)c->txt_pos.y, 30, c->hovered ? OFF_WHITE : DEFAULT_COLOR);
    }
  }
}

void OpenCase(Case *c) {
  if (!c->selected) {
    UpdateCaseDisplay(c->number, c->value);
    // TraceLog(LOG_DEBUG, TextFormat("Case %d was clicked! Value: %d",
    // c->number, c->value));
    c->interactable = false;
    c->hovered = false;
    c->opened = true;
    c->selected = false;
    c->picked = true;
    case_values[c->value_index].in_play = false;
    c->visible = false;
  }
}

void UpdateCaseDisplay(int case_num, int case_val) {
  opened_case_num = case_num;
  opened_case_value = case_val;
}