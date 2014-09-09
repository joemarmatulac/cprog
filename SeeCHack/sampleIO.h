/*
 *  sampleIO.h
 *  
 *
 *  Created by Latin on 9/8/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>

int main(){
	int c;
	
	printf("Enter anything:\n");
	while ((c == getchar()) != EOF) {
		putchar(c);
	}
	
	return 0;
	
}

