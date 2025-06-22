#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>

#define NUM_CASES 24

typedef struct {
    int value;
    bool in_play;
} CaseValue;

extern CaseValue case_values[NUM_CASES];
extern int playerCaseNumber;
extern int playerCaseValue;

#endif // GLOBALS_H
