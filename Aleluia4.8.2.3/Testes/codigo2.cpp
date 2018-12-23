/*Compilador ALELUIA*/
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int main(void)
{
	char * TMP1;
	int TMP2;
	char * TMP3;
	int TMP4;
	char * TMP5;
	int TMP6;
	char * TMP7;

	TMP2 = 11;
	TMP3 = (char *) malloc(TMP2 * sizeof(char));
	TMP3 = strcpy(TMP3, "oi, mundo!");
	TMP1 = TMP3;

	TMP4 = 3;
	TMP5 = (char *) malloc(TMP4 * sizeof(char));
	TMP5 = strcpy(TMP5, "oi");
	TMP6 = 13;
	TMP7 = (char *) malloc(TMP6 * sizeof(char));
	TMP7 = strcat(TMP1, TMP5);
	TMP1 = TMP7;

	cout << TMP1 << endl;

	return 0;
}
