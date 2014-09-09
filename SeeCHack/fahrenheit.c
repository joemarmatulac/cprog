#include <stdio.h>

int main(){
	int fahr, celsius;
	int lower, upper, stop;
	
	lower = 0;
	upper = 200;
	stop = 20;

	fahr = lower;

	while(fahr <= upper){
		celsius = 5 * (fahr - 32) / 9;
		printf("%d\t%d\n", fahr, celsius);
		fahr = fahr + stop;
	}

	return 0;
}
