#ifndef TIMER_H
#define TIMER_H

#include "../include/raylib/raylib.h"
#include <stdbool.h>
#include <string.h>

typedef struct {
  float Lifetime;
} Timer;

void StartTimer(Timer *timer, float lifetime);

void UpdateTimer(Timer *timer);

#endif // TIMER_H