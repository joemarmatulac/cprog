#include <stdio.h>

int main(){
	int *numberInputPointer, numberInput;
	numberInputPointer = &numberInput;
	printf("Enter a number");
	scanf("%d", numberInputPointer);
	printf("Number entered is: %d", numberInput);
	return 0;
}
