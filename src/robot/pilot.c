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

static void Pilot_run(Event anEvent){
    TransitionAction anAction;
    State aState;
    anAction = mySm[myState][anEvent].action;
    aState = mySm[myState][anEvent].destinationState;
    if(aState != S_FORGET){
        Pilot_performAction(anAction);
        myState = aState;
    }
}

static void Pilot_performAction(TransitionAction anAction){
    switch(anAction){
        case A_NOP:
            break;
        case A_HAS_BUMPED:
            has_bumped();
            break;
        case A_MVT:
            sendMvt(vel);
            break;
        case A_NOT_MVT:
            not_sendMvt(vel);
            break;
        case A_SET_VELOCITY:
            Pilot_setVelocity(vel);
            break;
        case A_STOP:
            Pilot_stop();
            Pilot_free();
            break;
        default:
            printf("Action inconnue\n");
            break;
    }
}
