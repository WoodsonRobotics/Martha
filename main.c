#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
	
	printf("Connected. \n");
	
	setup(); // Beep and set timer
	
	printf("Hello World! \n I'm Martha and you're about to get rekt. \n");
	
	sweeper(-1);   // Turn on sweeper to start picking up poms
	move(750, 7);
	move(-750, 1);
	
	turn(1.368,-1);  // First 45 degree angle turn to poms
	printf("Munch munch munch... \n");
	
	move(1500, 1.4);
	lift();
	move(800, 1); 
	
	system("clear");
	printf("Sorting... \n");
	
	camera_open(LOW_RES);
	
	int i;
	for(i = 0; i < 3; i++) {
		decide();
		printf("pom %d \n", i);	
	}
	
	move(-500,5);       // back up to avoid vertical projection of bins
	
	system("clear");
	printf("Backing up... \n");
	
	return 0;
}
