#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
	printf("Testing \n");
	
	setup();
	
	printf("Hello World! \n I'm Martha and you're about to get rekt. \n");
	
	printf("To the poms! \n");
	move(1500,2);
	system("clear");
	
	printf("Munch munch munch... \n");
	turn(1,1);           // swing around to gather poms
	sweeper(-1,10);
	system("clear");
	
	printf("To the poms! \n");
	move(800,5);
	system("clear");
	
	printf("Munch munch munch... \n");
	turn(2,-1);           // swing around to gather poms
	sweeper(-1,10);
	system("clear");
	
	printf("To the line! \n");
	move(800,5);
	system("clear");
	
	lift();
	move(100,1);
	
	system("clear");
	printf("Sorting... \n");
	
	decide();
	decide();
	decide();
	decide();    // eight times because eight poms
	decide();
	decide();
	decide();
	decide();
	
	system("clear");
	printf("Backing up... \n");
	move(-500,1);       // back up to avoid vertical projection of bins
	
	return 0;
}
