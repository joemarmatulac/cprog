#include <stdio.h>

int main(){
	int *pointerX, x;
	x = 10;
	pointerX = &x;

	printf("\n\nAssign 10 = x \n\n");

	printf("Value of x: %d \n", x);
	printf("Address of x: %p \n", &x);
	printf("PointerX is pointing to: %p \n", pointerX); 
	printf("PointerX is pointing to: %p value is %d \n", pointerX, *pointerX); 

	printf("\n\nAssign 11 = x \n\n");

	x = 11;
	printf("Current value of x is: %d \n", x);
	printf("PointerX is pointing to: %p value is %d \n", pointerX, *pointerX); 

	*pointerX = 10;
	printf("%d", x);
	printf("%p", pointerX);
	return 0;
}
