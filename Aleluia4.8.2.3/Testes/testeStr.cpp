#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(void){

	char *ch; //aloca 1º byte e incrementa
	char *data; //onde ficara o texto final
	int tam; //tamanho entrada 
	int k; //booleano verificador da entrada
	int flag; //negador do verificador - para a condicional
	int incremento; //incremento da entrada
	char enter; //p/ verficar se a entrada do usuário foi um enter "\n"

	ch = (char*)malloc(sizeof(char));
	data = NULL;
	tam = 1;
	incremento = 1;
	enter = '\n';
	
	inicio:
	cin >> std::noskipws;
	cin >> *ch;
	k = *ch != enter;
	flag = !k;
	if(flag) goto fim;
	
	data = (char*)realloc(data, (tam)*sizeof(char));
	data = strcat(data, ch);
	tam = tam + incremento;
	goto inicio;

	fim:
	data = (char*)realloc(data, (tam)*sizeof(char));
	data = strcat(data, "\0");

	cin >> std::skipws;

	cout << tam << data;

	return 0;
}

