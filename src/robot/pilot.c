/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// a completer
#include <stdlib.h>
#include <stdio.h>
#include "pilot.h"
#include "robot.h"

static void sendMvt(VelocityVector vector);
static void Pilot_run(Event event);
static int hasBumped();
static void Pilot_performAction(TransitionAction transitionAction);
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

static void sendMvt(VelocityVector vector){

}


static int hasBumped(){
    return 0;
}

static void Pilot_run(Event anEvent)
{
    TransitionAction anAction;
    State aState;
    anAction = mySm[myState][anEvent].action;
    aState = mySm[myState][anEvent].destinationState;
    if (aState != S_FORGET){
        myState=aState;
        Pilot_performAction(anAction); 
    }
}

static void Pilot_performAction(TransitionAction transitionAction){
    
}
