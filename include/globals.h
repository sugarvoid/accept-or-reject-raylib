#ifndef GLOBALS_H
#define GLOBALS_H

#include "../include/case.h"
#include <stdbool.h>

#define NUM_CASES 24

#define TEXT_BLUE (Color){41, 173, 255, 255}
#define TEXT_GRAY (Color){95, 87, 79, 255}

typedef struct {
  int value;
  bool in_play;
} CaseValue;

extern CaseValue case_values[NUM_CASES];
extern Case *playerCase;
extern Case *pickedCase;
extern int playerCaseNumber;
extern int playerCaseValue;

#endif // GLOBALS_H
