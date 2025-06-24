
#include "../include/timer.h"

void StartTimer(Timer *timer, float lifetime) {
  if (timer != NULL) {
    timer->Lifetime = lifetime;
  }
}

void UpdateTimer(Timer *timer) {
  if (timer != NULL && timer->Lifetime > 0) {
    timer->Lifetime -= GetFrameTime();
  }
}

bool IsTimerDone(Timer *timer) {
  if (timer != NULL) {
    return timer->Lifetime <= 0;
  }
  return false;
}