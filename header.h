#ifndef _HEADER_H_
#define _HEADER_H_

#define leftWheel 3   // motor
#define rightWheel 2  // motor
#define sweeperPort 1 // motor
#define liftPort 3   // servo

#define lightPort 0   // infrared analog
#define topHatPort 2  // analog
#define touchPort 15  // analog

#define pinkVal 0
#define greenVal 1

//~~~~~~~~~~~~~~~~~~~~~~~~~~SETUP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup() {
	
	wait_for_light(lightPort);
	beep();

	shut_down_in(118);	
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~DECIDE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void decide() {
	
	printf("before loop \n");
	camera_update();

	while((get_object_count(pinkVal) == 0) && (get_object_count(greenVal) == 0)) {
		printf("In the null colour \n");
		mav(sweeperPort, 500); 
		msleep(200);
		camera_update();
	}

	printf("have we found a pom? \n");
	camera_update();
	if(get_object_count(pinkVal) > get_object_count(greenVal)) {
	printf("FOUND POM PINK \n");
		
		mav(rightWheel, -800);
		mav(leftWheel, -800);
		msleep(600);
		mav(rightWheel, 0);
		mav(leftWheel, 0);
		mav(sweeperPort, 1500);
		msleep(1000);
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
				
	} else if(get_object_count(greenVal) > get_object_count(pinkVal)) {
	printf("FOUND POM GREEN \n");
	
			mav(rightWheel, 800);
			mav(leftWheel, 800);
			msleep(600);
			mav(rightWheel, 0);
			mav(leftWheel, 0);
			mav(sweeperPort, 1500);
			msleep(1000);
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
			
		}
		camera_update();

}


/***************** camera must detect pom at position where a pom directly behind it is put in the same
****************** position after the first is dropped. Camera vision must be small and towards the end ****************** of the track **********************************************************************/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~SWEEPER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sweeper(int d) {    // d for direction, -1 out, 1 in
	mav(sweeperPort,(d * 1500));	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~LINE FOLLOWING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void turn_L() {
	motor(leftWheel,-70);
	motor(rightWheel,-45);  	
}
void turn_R() {
	motor(leftWheel,-45);
	motor(rightWheel,-70);
}
int isOnLine() {
	if (analog10(topHatPort) > 700) { // > 700 is ON THE LINE
		return 1;
	}
	return 0;
}

int linefollow() {
	printf("testing line following");
	while(digital(touchPort) == 0) {
		if (isOnLine() == 1) {
			mav(rightWheel, -500);
			mav(leftWheel, 500);
		} else {
				turn_R();
				turn_L();
		  }
		
	}
	return 0;
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void move(int speed, float seconds) {
		
	mav(leftWheel, -1*speed);
	mav(rightWheel, speed);
	msleep(seconds * 1000);
	mav(leftWheel, 0);
	mav(rightWheel, 0);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~TURN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void turn(float degree, int direction) { // degree is in 1,2,3,4 each one being a quarter turn. 
	                                    // direction is -1 or 1, positive is counterclockwise
	mav(rightWheel, 1000 * direction);
	mav(leftWheel, 1000 * direction);
	msleep(750 * degree);
	mav(rightWheel, 0);
	mav(leftWheel, 0);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~LIFT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lift() {
	enable_servos();
	set_servo_position(liftPort, 1500);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~NOTES~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* ***************NOTES TO MYSELF************** */
/*

Need to add line following
and touch sensor

~SORTING~
	For now: sweeper motors run outwards when nothing is detected and when something is, it decides what to do with it.
	- must look at the moment when a pom gets in sight to adjust how long/fast the sweeper motor should run to put it out without releasing the next one.
	- might need to use <> because some of the same coloured poms might be next next to eachother in the track
	
	
	IDEA:what if the camera tracked the order of the poms as the went into the track?
	then only regulate how they come out at the end...?
	- then we'd need to just have the sweeper function going inwards until it reaches the last pom 
*/
#endif
