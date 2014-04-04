#ifndef _FILE_H_
#define _FILE_H_

#define leftWheel 3   // motor
#define rightWheel 2  // motor
#define sweeperPort 1 // motor
#define liftPort 2   // servo

#define lightPort 0   // infrared analog
#define topHatPort 1

#define pinkVal 0
#define greenVal 1

//~~~~~~~~~~~~~~~~~~~~~~~~~~SETUP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup() {
	
	enable_servos();

	//wait_for_light(lightPort);
	beep();

	shut_down_in(120);	
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~DECIDE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void decide() {
	
	camera_close();
	camera_open(LOW_RES);
	camera_update();

while((get_object_count(pinkVal) == 0) && (get_object_count(greenVal) == 0)) {

	mav(sweeperPort, 200); // test to see what speed and time will give best and continuous accuracy
	msleep(300);
	
	camera_update();
}

if(get_object_count(pinkVal) > get_object_count(greenVal)) {
	mav(rightWheel, -200);
	msleep(300);
	mav(rightWheel, 0);
	mav(sweeperPort, 300);
	msleep(300);
	mav(sweeperPort, 0);
	mav(rightWheel, 200);
	msleep(300);
} else if(get_object_count(pinkVal) < get_object_count(greenVal)) {
		mav(rightWheel, 200);
		msleep(300);
		mav(rightWheel, 0);
		mav(sweeperPort, 300);
		msleep(300);
		mav(sweeperPort, 0);
		mav(rightWheel, -200);
		msleep(300);
	}
}


/***************** camera must detect pom at position where a pom directly behind it is put in the same
****************** position after the first is dropped. Camera vision must be small and towards the end ****************** of the track **********************************************************************/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~SWEEPER~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void sweeper(int d,int t) {    // d for direction, -1 in, 1 out
		mav(sweeperPort,d*500);
		msleep(t*300);
		mav(sweeperPort,0);
} // for first collection, sweep continuous; for sorting, needs to only output one ball...

// need to know for how long will be sweeping

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
	if (analog10(topHatPort)>700) {
		return 1;
	}
	return 0;
}

void linefollow() {
	printf("test");
	while(digital(8)==0) {
		if (isOnLine()==0) {
			turn_R();
		}
		else {
 
			turn_L();
		}
	}

	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~MOVE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void move(int speed, int seconds) {
		
	mav(leftWheel, speed);
	mav(rightWheel, speed);
	msleep(seconds * 1000);
	mav(leftWheel, 0);
	mav(rightWheel, 0);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~TURN~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void turn(int degree, int direction) { // degree is in 1,2,3,4 each one being a quarter turn. 
	                                    // direction is -1 or 1, positive is counterclockwise
	mav(rightWheel, -800 * direction);
	mav(leftWheel, -800 * direction);
	msleep(750 * degree);
	mav(rightWheel, 0);
	mav(leftWheel, 0);

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~LIFT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void lift() {
	set_servo_position(liftPort, 1400);

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
