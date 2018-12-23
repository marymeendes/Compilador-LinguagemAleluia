/*Compilador ALELUIA*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char * TMP1;
	int TMP2;
	char * TMP3;
	char * TMP4;
	int TMP5;
	char * TMP6;
	char * TMP7;
	int TMP8;
	char * TMP9;

	TMP2 = 12;
	TMP3 = (char *) malloc(TMP2 * sizeof(char));
	TMP3 = strcpy(TMP3, "oi, manitos");
	TMP1 = TMP3;


	TMP5 = 18;
	TMP6 = (char *) malloc(TMP5 * sizeof(char));
	TMP6 = strcpy(TMP6, "hey, ho, let's go");
	TMP4 = TMP6;


	TMP8 = 29;
	TMP9 = (char *) malloc(TMP8 * sizeof(char));
	TMP9 = strcat(TMP1, TMP4);
	TMP7 = TMP9;

	return 0;
}
