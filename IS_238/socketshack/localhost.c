#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char name[256] = "";
char buffer[256] = "";

void client(char *buffer){
	printf("%s", buffer);
	fgets(buffer, 256, stdin);
}

int main(int argc, char *argv[]){
	int year, age;

	sprintf(buffer, "Please enter your name: ");
	client(buffer);
	strcpy(name, buffer);
	sprintf(buffer, "Hi %sPlease enter your year of birth: ", name);
	client(buffer);
	year = atoi(buffer);
	age = 2014 - year;
	sprintf(buffer, "You approximate age is %d. \nEnter q to quit: ", age);
	client(buffer);
	return (0);
}
