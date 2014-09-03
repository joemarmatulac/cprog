#include <stdio.h>
#include "fish.h"

void catalog(fish f){
	printf("%s is a, %s with %i teeth. He is %i\n", f.name, f.species, f.teeth, f.age);
}

int main(){
	fish f = {"Fishtail", "Piranha", 69, 4};
	catalog(f);
	return 0;
}
