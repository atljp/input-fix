#include "shared.h"

#define MAX_PLAYERS 2

void patchToOneButtonVertControl();
void patchInput();

void __cdecl set_actuators(int port, uint16_t left, uint16_t right);
