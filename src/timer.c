
#include "../include/timer.h"
#include <stdbool.h>
#include <stdlib.h>

Timer *CreateTimer() {
  Timer *t = calloc(1, sizeof(Timer));
  if (!t)
    return NULL;
  return t;
}

void StartTimer(Timer *timer, float lifetime) {
  if (timer != NULL) {
    timer->TimeLeft = lifetime;
    timer->IsDone = false;
    timer->IsRunning = true;
  }
}

void UpdateTimer(Timer *timer) {
  if (timer != NULL && timer->TimeLeft > 0 && timer->IsRunning) {
    timer->TimeLeft -= GetFrameTime();
    if (timer->TimeLeft <= 0) {
      timer->IsRunning = false;
      timer->IsDone = true;
    }
  }
}