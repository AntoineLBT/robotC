/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/**
 * @file  pilot.h
 *
 * @brief  Pilot the robot
 *
 * @author Jerome Delatour
 * @date 17-04-2016
 * @version 1
 * @section License
 *
 * The MIT License
 *
 * Copyright (c) 2016, Jerome Delatour
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef PILOT_H
#define PILOT_H

#define NB_ETAT 2
#define NB_ENTREE


typedef enum {LEFT=0, RIGHT, FORWARD, BACKWARD} Direction;


typedef struct
{
    Direction dir;
    int power;
} VelocityVector;

typedef struct
{
    int speed;
    int collision;
    float luminosity;
} PilotState;

typedef enum{
    S_FORGET = 0,
    S_IDLE,
    S_RUNNING,
    S_P_E_1,
    S_P_E_2, 
    S_DEATH,
    NB_STATE
} State;

typedef enum {
    A_NOP = 0,
    A_SET_VELOCITY,
    A_MVT, 
    A_NOT_MVT,
    A_HAS_BUMPED,
    A_STOP
} TransitionAction;

typedef enum {
    E_CHEKC_VEL = 0,
    E_CHECK_VEL_FALSE,
    E_ELSE,
    E_CHECK_BUMP_FALSE,
    E_CHECK_BUMP_TRUE,
    E_STOP, 
    NB_EVENT
} Event;

typedef struct {
    State destinationState;
    TransitionAction action;
} Transition;

static Transition mySm [NB_STATE][NB_EVENT]={
    [S_IDLE][E_CHEKC_VEL] = {S_P_E_1, A_SET_VELOCITY},
    [S_P_E_1][E_CHECK_VEL_FALSE] = {S_IDLE, A_NOT_MVT},
    [S_P_E_1][E_ELSE] = {S_RUNNING, A_MVT},
    [S_RUNNING][E_CHEKC_VEL] = {S_P_E_2, A_HAS_BUMPED},
    [S_P_E_2][E_CHECK_BUMP_FALSE] = {S_RUNNING, A_NOP},
    [S_P_E_2][E_CHECK_BUMP_TRUE] = {S_IDLE, A_NOT_MVT},
    [S_IDLE][E_STOP] = {S_DEATH, A_STOP},
    [S_RUNNING][E_STOP] = {S_DEATH, A_STOP}
};

State myState = S_DEATH;
/**
 * Start Pilot
 *
 */
extern void Pilot_start();


/**
 * Stop Pilot
 *
 */
extern void Pilot_stop();


/**
 * initialize in memory the object Pilot
 */
extern void Pilot_new();


/**
 * destruct the object Pilot from memory
 */
extern void Pilot_free();

/**
 * setVelocity
 *
 * @brief description
 * @param vel
 */
extern void Pilot_setVelocity(VelocityVector vel);

/**
 * getState
 *
 * @brief description
 * @return PilotState
 */
extern PilotState Pilot_getState();

/**
 * check
 *
 * @brief description
 */
extern void Pilot_check();

/**
 * checkMAE
 *
 * @brief description
 */
extern void Pilot_checkMAE();


#endif /* PILOT_H */
