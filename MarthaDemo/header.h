// Created on Wed April 16 2014

// Replace FILE with your file's name
#ifndef _FILE_H_
#define _FILE_H_

#define leftWheel 3   // motor
#define rightWheel 2  // motor
#define sweeperPort 1 // motor
#define liftPort 3   // servo

#define lightPort 0   // infrared analog
#define topHatPort 2  // analog
#define touchPort 15  // analog

#define pinkVal 0
#define greenVal 1

//~~~~~~~~~~~~~~~~~~~~~~~~~~DECIDE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void decide() {
	
	printf("Waiting for update... \n");
	camera_update();
	printf("Camera updated. \n");

	while((get_object_count(pinkVal) == 0) && (get_object_count(greenVal) == 0)) {
		printf("In the null colour \n");
		mav(sweeperPort, 500); 
		camera_update();
	}
	mav(sweeperPort, 0);

	printf("have we found a pom? \n");
	camera_update();
	if(get_object_count(pinkVal) > get_object_count(greenVal)) {
	printf("FOUND POM PINK \n");
		
		msleep(500);              
		mav(rightWheel, -800); 
		mav(leftWheel, -800);        
		msleep(600);        
		mav(rightWheel, 0);       
		mav(leftWheel, 0); 
		mav(sweeperPort, 1500);
		msleep(1900);
		mav(sweeperPort, 0);
		mav(rightWheel, 800); 
		mav(leftWheel, 800);     
		msleep(600);      
		mav(rightWheel, 0);
		mav(leftWheel, 0);

		mav(sweeperPort, -500);
		msleep(300);
		mav(sweeperPort, 0);
		
		msleep(800);
		camera_update();
		
	} else if(get_object_count(greenVal) > get_object_count(pinkVal)) {
	printf("FOUND POM GREEN \n");
	
			msleep(500);
			mav(rightWheel, 800);
			mav(leftWheel, 800);
			msleep(600);
			mav(rightWheel, 0);
			mav(leftWheel, 0);
			mav(sweeperPort, 1500);
			msleep(1900);
			mav(sweeperPort, 0);
			mav(rightWheel, -800);
			mav(leftWheel, -800);
			msleep(600);
			mav(rightWheel, 0);
			mav(leftWheel, 0);
		
			mav(sweeperPort, -500);
			msleep(300);
			mav(sweeperPort, 0);
		   
			msleep(800);
			camera_update();

		}
		camera_update();

}


/***************** camera must detect pom at position where a pom directly behind it is put in the same
****************** position after the first is dropped. Camera vision must be small and towards the end ****************** of the track **********************************************************************/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~GATHER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void gather() {
	int poms = 0;

	int i = 0;
	int p = 1000;
	
	while(i < p) {
		mav(leftWheel, -1*1000);
		mav(rightWheel, 1000);
		mav(sweeperPort, 1500);
		camera_update();
		
		if((get_object_count(pinkVal) || get_object_count(greenVal)) > 0) {
			poms++;
			printf("I have %d poms. \n", poms);	
		}
		
		
		
		
	i++;	
	}
	
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~SWEEPER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sweeper(int d) {    // d for direction, -1 out, 1 in
	mav(sweeperPort,(d * 1500));	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void move(int speed, float seconds) {
		
	mav(leftWheel, -1*speed);
	mav(rightWheel, speed);
	msleep(seconds * 1000);
	mav(leftWheel, 0);
	mav(rightWheel, 0);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~TURN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void turn(int direction, float seconds) {
		
	mav(leftWheel, direction*500);
	mav(rightWheel, direction*500);
	msleep(seconds * 1000);
	mav(leftWheel, 0);
	mav(rightWheel, 0);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~LIFT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lift() {
	enable_servos();
	set_servo_position(liftPort, 1500);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~SETUP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup() {
	beep();
	camera_open(LOW_RES);
}
#endif
