#include "../include/player.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void PlayerPickCase(Player *p, Case *c) {
  if (p == NULL || c == NULL) {
    // handle error
    TraceLog(LOG_ERROR, "Something was null");
  }
  if (p->CaseNum == 0) {
    c->selected = true;
    c->hovered = false;
    c->interactable = false;
    p->CaseNum = c->number;
    p->CaseVaule = c->value;

  } else {
    OpenCase(c);
  }
}
