#include "header.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
	int i;
	
	setup();
	
		mav(sweeperPort, -1500);
		move(600, 7);

		turn(1, 1.7);
	
		move(1000, 1.1);
		
		for(i = 0; i < 5; i++) {
			printf("pom number %d \n", i+1);
			decide();
			camera_update();
		}
			
	printf("DONE. \n");
		
	return 0;
}
