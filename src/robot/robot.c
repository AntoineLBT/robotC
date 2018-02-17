/* -*- mode: c; c-basic-offset: 4; indent-tabs-mode: nil -*- */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "/home/antoine/github/robotC/src/robot/robot.h"
#include "/home/antoine/github/infox_prose-x86_64-v0.3/include/infox/prose/prose.h"

#define LEFT_MOTOR MD
#define RIGHT_MOTOR MA
#define LIGHT_SENSOR S1
#define FRONT_BUMPER S3
#define FLOOR_SENSOR S2

static Robot *robot;
// a completer
void Robot_new(){
    /* Allocate memory for robot */
  robot = (Robot *) malloc(sizeof(Robot));

  /* Open motors and sensors */
  robot->mD = Motor_open(LEFT_MOTOR);
  robot->mG = Motor_open(RIGHT_MOTOR);
  robot->contact_sensor = ContactSensor_open(FRONT_BUMPER);
  robot->light_sensor = LightSensor_open(LIGHT_SENSOR);

  /* Opening verification */
  if(robot->mD == NULL)
  {
	  PProseError("Erreur dans la création de l'instance left_motor");
  }
  if(robot->mG == NULL)
  {
 	  PProseError("Erreur dans la création de l'instance right_motor");
  }
  if(robot->contact_sensor == NULL)
  {
	  PProseError("Erreur dans la création de l'instance contact_sensor");
  }
  if(robot->light_sensor == NULL)
  {
	  PProseError("Erreur dans la création de l'instance light_sensor");
  }
}
void Robot_start(){
#ifdef INTOX
	/* Initialisation pour l'utilisation du simulateur Intox. */
	if (ProSE_Intox_init("127.0.0.1", 12345) == -1) {
		PProseError("Problème d'initialisation du simulateur Intox");
		return EXIT_FAILURE;
	}
#endif
}
void Robot_stop(){
    Robot_setWheelsVelocity(robot, ROBOT_CMD_STOP, ROBOT_CMD_STOP);
#ifdef INTOX
	ProSE_Intox_close();
#endif

	return EXIT_SUCCESS;
}

void Robot_free(){
    Robot_destructor(robot);
}

int Robot_getRobotSpeed(){

}
SensorState Robot_getSensorState(){

}
void Robot_setWheelsVelocity(Robot * robot, int mr, int ml){
    if(Motor_setCmd(robot->mD, mr)){
        PProseError("error command right motor");
    }
    if(Motor_setCmd(robot->mG, ml)){
        PProseError("error commande left motor");
    }
}

Robot * robot(){
        Robot * this;
        this = (Robot *)malloc(sizeof(Robot));
    }

    this->mD = Motor_open(MD);
    if(this->MD==NULL){
        PProseError("Error during initialization of right motor");
    }
    this->mG = Motor_open(MG);
    if(this->MG==NULL){
        PProseError("Error during initialization of left motor");
    }
    return this;

void Robot_destructor(Robot * robot){
    Motor_close(robot->mD);
    Motor_close(robot->mG);

    free(robot);
}

