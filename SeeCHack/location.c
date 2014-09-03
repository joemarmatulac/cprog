#include <stdio.h>

	void locate(int *lat, int *lon){
		*lat = *lat - 1;
		*lon = *lon - 1;
	}	
	
	int main(){
		int latitude = 10, longitude = 9;
		locate(&latitude, &longitude);
		printf("Current location [%i, %i]", latitude, longitude);
		return 0;
	}
