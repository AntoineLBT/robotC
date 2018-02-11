/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// a completer
#include <stdlib.h>
#include <stdio.h>
#include "pilot.h"
#include "robot.h"

//static void sendMvt(VelocityVector);
PilotState p1;

void Pilot_new(){
    Robot_new();
}

void Pilot_start(){
    Robot_start();
}

void Pilot_stop(){
    Robot_stop();
}

void Pilot_free(){
    Robot_free();
}

void Pilot_setVelocity(VelocityVector vel){

}
PilotState Pilot_getState(){
    return p1;
}
void Pilot_check(){

}

/*static void sendMvt(VelocityVector){
    printf("\n");
}*/

static Etat tableEtat [NB_ETAT][NB_ENTREE]={{}}
