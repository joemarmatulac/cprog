#include <stdio.h>
#include "summation.h"
#include "subtractor.h"

int main(){
	float sum = summation(1.2, 1.3);
	printf("\n\nSum is: %f\n\n", sum);

	float diff = sub(1.5, 1.3);
	printf("\n\nDifferncet is: %f\n\n", diff);
}

float summation(float addent1, float addent2){
	return addent1 + addent2;
}
