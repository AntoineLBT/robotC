/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// a completer
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include "adminui.h"
#include "pilot.h"

#define PRINTMENU printf("z : avancer\ns : reculer\nq : gauche\nd : droite\n  : s'arrêter\na : log\ne : effacer log\nx : quitter\n");


static char captureChoice();
static void askMvt(Direction dir);
static void ask4Log();
static void askClearLog();
static void quit();
static void eraseLog();
static void display();

void AdminUI_new() {
    printf("Programme robot V1 : CTRL+C pour quitter\n");
    Pilot_new();
}

void AdminUI_start() {
    Pilot_start();
    char userChoice = ' ';
    while(userChoice != 'x'){
        display();
        userChoice = captureChoice();
    }
}

void AdminUI_stop() {
    //Pilot_stop();
}

void AdminUI_free() {
    //Pilot_free();
}

static char captureChoice(){
    char c;
    static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    //This is your part:
        c = getchar();
        putchar(c);

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    switch (c) {
        case 'z':
            askMvt(FORWARD);
            break;
        case 's':
            askMvt(BACKWARD);
            break;
        case 'q':
            askMvt(LEFT);
            break;
        case 'd':
            askMvt(RIGHT);
            break;
        case 'a':
            ask4Log();
            break;
        case 'e':
            askClearLog();
            break;
        case 'x':
            quit();
            break;
        default:
            printf("touche non reconnu\n");
            break;
    }

    return c;
}
static VelocityVector vel;

static void askMvt(Direction dir){
    switch(dir){
        case FORWARD:
            vel.dir = FORWARD;
            if(vel.power == 100){
                vel.power = 100;
            } else {
                vel.power += 5;
            }
            break;
        case BACKWARD:
            vel.dir = BACKWARD;
            if(vel.power == -100){
                vel.power = -100;
            } else {
                vel.power -= 5;
            }
            break;
        case LEFT:
            vel.dir = LEFT;
            break;
        case RIGHT: 
            vel.dir = RIGHT;
            break;
        default:
            break;
    }
    printf("power : %d\n", vel.power);
    Pilot_setVelocity(vel);
}

static void ask4Log(){
    Pilot_check();
}

static void askClearLog(){
    eraseLog();
}

static void quit(){
    printf("Au revoir");
    Pilot_stop();
}

static void eraseLog(){
    printf("erase log");
}

static void display(){
    PRINTMENU;
}

