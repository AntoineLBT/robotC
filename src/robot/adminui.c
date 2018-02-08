/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// a completer
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>
#include "pilot.h"

#define PRINTMENU printf("z : avancer\ns : reculer\nq : gauche\nd : droite\n  : s'arrêter\na : log\ne : effacer log\nx : quitter\n");

void AdminUI_new();
void AdminUI_start();
void AdminUI_stop();
void AdminUI_free();
char captureChoice();

void AdminUI_new() {
    printf("Programme robot V1 : CTRL+C pour quitter\n");
    PRINTMENU;
    Pilot_new();
}

void AdminUI_start() {
    char userChoice = ' ';
    while(userChoice != 'x'){
        userChoice = captureChoice();
    }
    Pilot_start();
}

void AdminUI_stop() {
    Pilot_stop();
}

void AdminUI_free() {
    Pilot_free();
}

char captureChoice(){
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

    /*This is your part:
    I choose 'e' to end input. Notice that EOF is also turned off
    in the non-canonical mode*/
    //while((c=getchar())!= '')
        c = getchar();
        putchar(c);

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    switch (c) {
        case 'z':
            printf("avancer\n");
            break;
        case 's':
            printf("reculer\n");
            break;
        case 'q':
            printf("gauche\n");
            break;
        case 'd':
            printf("droite\n");
            break;
        case 'a':
            printf("asklog()\n");
            break;
        case 'e':
            printf("clearlog()\n");
            break;
        case 'x':
            printf("quitter\n");
            break;
        default:
            printf("touche non reconnu\n");
            break;
    }

    return c;
}
