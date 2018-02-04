/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// a completer
#include <stdlib.h>
#include <stdio.h>
#include "pilot.h"


void Pilot_free();
void Pilot_start();
void Pilot_new();
void Pilot_stop();
void Pilot_setVelocity();
void Pilot_check();
void Pilot_checkMAE();
PilotState Pilot_getState();
