#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	
	char *a;
	a = (char *)malloc(3*sizeof(char));

	char *b;
	b = (char *)malloc(4*sizeof(char));

	char *c;
	c = (char *)malloc(6*sizeof(char));

	a = strcpy(a, "oi");
	b = strcpy(b, "ola");
	c = strcat(a, b);

	printf("%s\n", c);	

	return 0;
}