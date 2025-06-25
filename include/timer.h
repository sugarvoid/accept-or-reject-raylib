#ifndef TIMER_H
#define TIMER_H

#include "../include/raylib/raylib.h"
#include <stdbool.h>
#include <string.h>

typedef struct {
  float TimeLeft;
  bool IsRunning;
  bool IsDone;
} Timer;

Timer *CreateTimer();
void StartTimer(Timer *timer, float lifetime);
void UpdateTimer(Timer *timer);

#endif // TIMER_H