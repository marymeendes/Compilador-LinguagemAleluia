%{
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define YYSTYPE atributos

using namespace std;

struct atributos
{
	string rotulo; //nomes de alto nível (se houver) 
	string traducao; // valores e significados do token
	string conteudo; //conteudo do simbolo (valor)
	string temporaria; // variável de baixo nível associada
	string tipo; // tipo em alto nível
	string tipoTmp; // tipo da temporária associada
	string declaracaoTmp; //string de declaracao da temporária associada
};

typedef struct atributos Simbolo;

int yylex(void);
void yyerror(string);

vector<Simbolo> TabelaSimbolos;

string geraTemp(){
	static int count = 0;
	count++;
	return "TMP"+to_string(count);
}

void insereTabelaSimbolos(Simbolo *simbolo){

	TabelaSimbolos.push_back(*simbolo);
}

Simbolo* buscaTabelaSimbolos(string rotulo)
{
	Simbolo *aux;
	for (vector<Simbolo>::iterator it = TabelaSimbolos.begin(); it != TabelaSimbolos.end(); it++){
		if(it->rotulo == rotulo){
			aux->rotulo = it->rotulo;
			aux->traducao = it->traducao;
			aux->conteudo = it->conteudo;
			aux->temporaria = it->temporaria;
			aux->tipo = it->tipo;
			aux->tipoTmp = it->tipoTmp;
			aux->declaracaoTmp = it->declaracaoTmp;
			return aux;
		}
	}
	return NULL;
}


%}

%token TK_TIPO //para os tipos
%token TK_MAIN TK_ID //main e identificador
%token TK_FIM TK_ERROR //fim e erro
%token TK_CONVERTE //conversão pra float e int (EXPLÍCITA)
%token TK_SUM_SUB TK_MUL_DIV // soma e subtracao, multiplicacao e divisao
%token TK_REL TK_LOG //operadores lógicos e relacionais
%token TK_BOOLEAN TK_NUM TK_REAL TK_CHAR // valores: booleanos, inteiros, reais e caracteres

%start S

%left TK_LOG
%left '<' '>' LE GE EQ NE
%left TK_SUM_SUB
%left TK_MUL_DIV
%%

S 			: TK_TIPO TK_MAIN '(' ')' BLOCO
			{
				cout << "/*Compilador FOCA*/\n" << "#include <iostream>\n#include<string.h>\n#include<stdio.h>\nint main(void)\n{\n";
				string declaracao;
				for (vector<Simbolo>::iterator it = TabelaSimbolos.begin(); it != TabelaSimbolos.end(); it++){
					declaracao = it->declaracaoTmp;
					cout << declaracao;
				}

				cout << $5.traducao << "\treturn 0;\n}" << endl; 
			}
			;

BLOCO		: '{' COMANDOS '}'
			{
				$$.traducao = $2.traducao;
			}
			;

COMANDOS	: COMANDO COMANDOS
			{
				 $$.traducao = $1.traducao + "\n" + $2.traducao;
			}
			|
			{
				$$.traducao = "";
			}
			;

COMANDO 	: G ';' //expressão
			{
				$$ = $1;
			}
			| TK_TIPO TK_ID ';' //declaração
			{
				$$.traducao = "";
				Simbolo *aux;
				if((aux = buscaTabelaSimbolos($2.rotulo)) == NULL){ //variável não foi declarada antes
					Simbolo sim;
					sim.rotulo = $2.rotulo;
					sim.traducao = "";
					sim.conteudo = "none";
					sim.temporaria = geraTemp();
					sim.tipo = $1.rotulo;
					if($1.rotulo == "int" || $1.rotulo == "booleano")
						sim.tipoTmp = "int";
					else if($1.rotulo == "real")
						sim.tipoTmp = "float";
					else if($1.rotulo == "letra"){
						sim.tipoTmp = "char";
					}
					sim.declaracaoTmp = "\t" + sim.tipoTmp + " " + sim.temporaria + ";\n";
					insereTabelaSimbolos(&sim);
				}else{
					cout << "Variável " + $2.rotulo + " já foi declarada antes!";
					exit(1);
				}

			}
			| TK_ID '=' G ';' //atribuicao
			{	
				Simbolo *aux;
				if((aux = buscaTabelaSimbolos($1.rotulo)) != NULL){
					if(aux->tipoTmp == $3.tipoTmp && aux->tipo == $3.tipo){ //senão precisar de conversão
						$$.traducao = $3.traducao + "\t" + aux->temporaria + " = " + $3.temporaria + ";\n";
					}else if ($3.tipo == "booleano" && aux->tipo != "booleano"){
						cout << "Booleano só vai com booleano, bb.\n";
						exit(1);
					}else if(aux->tipoTmp == "float" && $3.tipoTmp =="int" || aux->tipoTmp == "int" && $3.tipoTmp == "float"){ //vai precisar de conversão
						Simbolo sim;
						string converteVar = geraTemp();
						sim.rotulo = "conversao";
						sim.traducao = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + $3.temporaria + ";\n";
						sim.conteudo = "none";
						sim.temporaria = converteVar;
						sim.tipo = aux->tipoTmp;
						sim.tipoTmp = aux->tipoTmp;
						sim.declaracaoTmp = "\t" + sim.tipo + " " + sim.temporaria + ";\n";
						insereTabelaSimbolos(&sim);

						$$.traducao = $3.traducao + sim.traducao + "\t" + aux->temporaria + " = " + sim.temporaria + ";\n";
					}
					else{
						cout << "Essa atribuicao não pode! \n";
						exit(1);
					}
				}

				$$.rotulo = "atrubuicao";
				$$.conteudo = "none";
				$$.temporaria = aux->temporaria;
				$$.tipo = aux->temporaria;
				$$.tipoTmp = $$.tipo;
				$$.declaracaoTmp = aux->declaracaoTmp;
			}
			;

G 			: TK_CONVERTE '(' G	')' //conversão explícita
			{
				Simbolo sim1, sim2;

				string converteVar = geraTemp();
				sim1.rotulo = "conversao";
				sim1.conteudo = "none";
				sim1.temporaria = converteVar;

				if($3.tipoTmp == "char"){ //só pq não pode entre char e outra coisa
					cout << "Operacao não suportada para tipo letra!\n";
					exit(1);
				}

				if($1.rotulo == "inteirao"){
					sim1.traducao = "\t" + converteVar + " = " + "(int)" + $3.temporaria + ";\n";
					sim1.tipo = "int";
					sim1.tipoTmp = "int";
					sim1.declaracaoTmp = "\tint " + sim1.temporaria + ";\n";
					sim2.tipo = "int";
					sim2.tipoTmp = "int";
						
				}else if($1.rotulo == "flutua"){
					sim1.traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
					sim1.tipo = "real";
					sim1.tipoTmp = "float";
					sim1.declaracaoTmp = "\tfloat " + sim1.temporaria + ";\n";
					sim2.tipo = "real";
					sim2.tipoTmp = "float";

				}
				insereTabelaSimbolos(&sim1);
				$$.traducao = $3.traducao + sim1.traducao;

				string opVar = geraTemp();
				sim2.rotulo = "operacao";
				sim2.temporaria = opVar;

				sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
				
				sim2.traducao = "\t" + sim2.temporaria + " = " + sim1.temporaria + ";\n";
				insereTabelaSimbolos(&sim2);
				$$.traducao = $$.traducao + sim2.traducao;
				$$.rotulo = sim2.rotulo;
				$$.conteudo = sim2.conteudo;
				$$.temporaria = sim2.temporaria;
				$$.tipo = sim2.tipo;
				$$.tipoTmp = sim2.tipoTmp;
				$$.declaracaoTmp = sim2.declaracaoTmp;

			}
			| G TK_LOG G //operações lógicas (só entre booleanos)
			{
				cout << $1.tipo;
				cout << $3.tipo;
				string remendo;
				if($2.rotulo == "ou"){
					remendo = "||";
				}
				else if($2.rotulo == "e"){
					remendo = "&&";
				}else{
					cout << "Simbolo logico nao reconhecido, bb.\n";
					exit(1);
				}
				if($1.tipo == "booleano" && $3.tipo == "booleano"){
					Simbolo sim;
					sim.rotulo = "operacao";
					sim.conteudo = "none";
					sim.temporaria = geraTemp();
					sim.tipo = "booleano";
					sim.tipoTmp = "int";
					sim.declaracaoTmp = "\t" + sim.tipoTmp + " " + sim.temporaria + ";\n";
					sim.traducao = "\t" + sim.temporaria + " = " + $1.temporaria + " " + remendo + " " + $3.temporaria + ";\n"; 
					insereTabelaSimbolos(&sim);

					$$.rotulo = sim.rotulo;
					$$.conteudo = sim.conteudo;
					$$.temporaria = sim.temporaria;
					$$.tipoTmp = sim.tipoTmp;
					$$.tipo = sim.tipo;
					$$.declaracaoTmp = sim.declaracaoTmp;
					$$.traducao = $1.traducao + $3.traducao + sim.traducao;
				}else{
					cout << "Operacao lógica so entre booleanos, bb.\n";
					exit(1);
				}	
			}
			| G TK_REL E //operações relacionais
			{
				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteu1 = false;
				$$.traducao = $1.traducao + $3.traducao;

				if($1.tipoTmp != $3.tipoTmp){
					converteu = true;
					string converteVar = geraTemp();
					sim1.rotulo = "conversao";
					sim1.conteudo = "none";
					sim1.temporaria = converteVar;

					if($1.tipoTmp == "char" || $3.tipoTmp == "char"){ //só pq não pode entre char e outra coisa
						cout << "Operacao não suportada entre letra e não-letra!\n";
						exit(1);
					}

					if($1.tipoTmp == "float"){
						converteu1 = true;
						sim1.traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
						sim1.tipo = $1.tipoTmp;
						sim1.tipoTmp = $1.tipoTmp;
						sim1.declaracaoTmp = "\t" + $1.tipoTmp + " " + sim1.temporaria + ";\n";
						
					}else if($3.tipoTmp == "float"){
						sim1.traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
						sim1.tipo = $3.tipoTmp;
						sim1.tipoTmp = $3.tipoTmp;
						sim1.declaracaoTmp = "\t" + $3.tipoTmp + " " + sim1.temporaria + ";\n";
					}
					insereTabelaSimbolos(&sim1);
					$$.traducao = $$.traducao + sim1.traducao;
				}

				string opVar = geraTemp();
				sim2.rotulo = "operacao";
				sim2.temporaria = opVar;
				if($1.tipoTmp == "float" || $3.tipoTmp == "float"){
					sim2.tipo = "real";
					sim2.tipoTmp = "float";
				}else{
					sim2.tipo = "int";
					sim2.tipoTmp = "int";
				}
				sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
				if(converteu){
					if(converteu1){
						sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + sim1.temporaria + ";\n";
					}
					else{
						sim2.traducao = "\t" + sim2.temporaria + " = " + sim1.temporaria + $2.rotulo + $3.temporaria + ";\n";
					}
				}else{
					sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + $3.temporaria + ";\n";
				}
				insereTabelaSimbolos(&sim2);

				$$.traducao = $$.traducao + sim2.traducao;
				$$.rotulo = sim2.rotulo;
				$$.conteudo = sim2.conteudo;
				$$.temporaria = sim2.temporaria;
				$$.tipoTmp = "int";
				$$.tipo = "booleano";
				$$.declaracaoTmp = sim2.declaracaoTmp;

			} 
			| E //expressão
			{
				$$.rotulo = $1.rotulo;
				$$.traducao = $1.traducao;
				$$.conteudo = $1.conteudo;
				$$.temporaria = $1.temporaria;
				$$.tipo = $1.tipo;
				$$.tipoTmp = $1.tipoTmp;
				$$.declaracaoTmp = $1.declaracaoTmp;
			}
			;		

E 			: E TK_SUM_SUB T //soma ou subtração
			{
				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteu1 = false;
				$$.traducao = $1.traducao + $3.traducao;

				if($1.tipoTmp != $3.tipoTmp){
					converteu = true;
					string converteVar = geraTemp();
					sim1.rotulo = "conversao";
					sim1.conteudo = "none";
					sim1.temporaria = converteVar;
					if($1.tipoTmp == "float"){
						converteu1 = true;
						sim1.traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
						sim1.tipo = $1.tipoTmp;
						sim1.tipoTmp = $1.tipoTmp;
						sim1.declaracaoTmp = "\t" + $1.tipoTmp + " " + sim1.temporaria + ";\n";
						
					}else if($3.tipoTmp == "float"){

						sim1.traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
						sim1.tipo = $3.tipoTmp;
						sim1.tipoTmp = $3.tipoTmp;
						sim1.declaracaoTmp = "\t" + $3.tipoTmp + " " + sim1.temporaria + ";\n";
					}
					insereTabelaSimbolos(&sim1);
					$$.traducao = $$.traducao + sim1.traducao;
				}

				string opVar = geraTemp();
				sim2.rotulo = "operacao";
				sim2.temporaria = opVar;
				if($1.tipoTmp == "float" || $3.tipoTmp == "float"){
					sim2.tipo = "real";
					sim2.tipoTmp = "float";
				}else{
					sim2.tipo = "int";
					sim2.tipoTmp = "int";
				}
				sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
				if(converteu){
					if(converteu1){
						sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + sim1.temporaria + ";\n";
					}
					else{
						sim2.traducao = "\t" + sim2.temporaria + " = " + sim1.temporaria + $2.rotulo + $3.temporaria + ";\n";
					}
				}else{
					sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + $3.temporaria + ";\n";
				}
				insereTabelaSimbolos(&sim2);

				$$.traducao = $$.traducao + sim2.traducao;
				$$.rotulo = sim2.rotulo;
				$$.conteudo = sim2.conteudo;
				$$.temporaria = sim2.temporaria;
				$$.tipo = sim2.tipo;
				$$.tipoTmp = sim2.tipoTmp;
				$$.declaracaoTmp = sim2.declaracaoTmp;
			}
			| T //expressão
			{
				$$.rotulo = $1.rotulo;
				$$.traducao = $1.traducao;
				$$.conteudo = $1.conteudo;
				$$.temporaria = $1.temporaria;
				$$.tipo = $1.tipo;
				$$.tipoTmp = $1.tipoTmp;
				$$.declaracaoTmp = $1.declaracaoTmp;
			}
			;

T 			: T TK_MUL_DIV F //multiplicação ou divisão
			{
				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteu1 = false;
				$$.traducao = $1.traducao + $3.traducao;

				if($1.tipoTmp != $3.tipoTmp){
					converteu = true;
					string converteVar = geraTemp();
					sim1.rotulo = "conversao";
					sim1.conteudo = "none";
					sim1.temporaria = converteVar;
					if($1.tipoTmp == "float"){
						converteu1 = true;
						sim1.traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
						sim1.tipo = $1.tipoTmp;
						sim1.tipoTmp = $1.tipoTmp;
						sim1.declaracaoTmp = "\t" + $1.tipoTmp + " " + sim1.temporaria + ";\n";
						
					}else if($3.tipoTmp == "float"){

						sim1.traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
						sim1.tipo = $3.tipoTmp;
						sim1.tipoTmp = $3.tipoTmp;
						sim1.declaracaoTmp = "\t" + $3.tipoTmp + " " + sim1.temporaria + ";\n";
					}
					insereTabelaSimbolos(&sim1);
					$$.traducao = $$.traducao + sim1.traducao;
				}

				string opVar = geraTemp();
				sim2.rotulo = "operacao";
				sim2.temporaria = opVar;
				if($1.tipoTmp == "float" || $3.tipoTmp == "float"){
					sim2.tipo = "real";
					sim2.tipoTmp = "float";
				}else{
					sim2.tipo = "int";
					sim2.tipoTmp = "int";
				}
				sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
				if(converteu){
					if(converteu1){
						sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + sim1.temporaria + ";\n";
					}
					else{
						sim2.traducao = "\t" + sim2.temporaria + " = " + sim1.temporaria + $2.rotulo + $3.temporaria + ";\n";
					}
				}else{
					sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + $3.temporaria + ";\n";
				}
				insereTabelaSimbolos(&sim2);

				$$.traducao = $$.traducao + sim2.traducao;
				$$.rotulo = sim2.rotulo;
				$$.conteudo = sim2.conteudo;
				$$.temporaria = sim2.temporaria;
				$$.tipo = sim2.tipo;
				$$.tipoTmp = sim2.tipoTmp;
				$$.declaracaoTmp = sim2.declaracaoTmp;
			}
			| F //expressão base
			{
				$$.rotulo = $1.rotulo;
				$$.traducao = $1.traducao;
				$$.conteudo = $1.conteudo;
				$$.temporaria = $1.temporaria;
				$$.tipo = $1.tipo;
				$$.tipoTmp = $1.tipoTmp;
				$$.declaracaoTmp = $1.declaracaoTmp;
			}
			;

F 			: TK_NUM //inteiros
			{
				Simbolo sim;
				$$.rotulo = "inteiro";
				sim.rotulo = $$.rotulo;
				$$.conteudo = $1.traducao;
				sim.conteudo = $$.conteudo;
				$$.temporaria = geraTemp();
				sim.temporaria = $$.temporaria;
				$$.tipo = "int";
				sim.tipo = $$.tipo;
				$$.tipoTmp = "int";
				sim.tipoTmp = $$.tipoTmp;
				$$.declaracaoTmp = "\t" + $$.tipoTmp + " " + $$.temporaria + ";\n";
				sim.declaracaoTmp = $$.declaracaoTmp;
				$$.traducao = "\t" + $$.temporaria + " = " + $$.conteudo + ";\n";
				sim.traducao = $$.traducao;
				insereTabelaSimbolos(&sim);
			}
			| TK_REAL //floats
			{
				Simbolo sim;
				$$.rotulo = "real";
				sim.rotulo = $$.rotulo;
				$$.conteudo = $1.traducao;
				sim.conteudo = $$.conteudo;
				$$.temporaria = geraTemp();
				sim.temporaria = $$.temporaria;
				$$.tipo = "real";
				sim.tipo = $$.tipo;
				$$.tipoTmp = "float";
				sim.tipoTmp = $$.tipoTmp;
				$$.declaracaoTmp = "\t" + $$.tipoTmp + " " + $$.temporaria + ";\n";
				sim.declaracaoTmp = $$.declaracaoTmp;
				$$.traducao = "\t" + $$.temporaria + " = " + $$.conteudo + ";\n";
				sim.traducao = $$.traducao;
				insereTabelaSimbolos(&sim);
			}
			| TK_CHAR //caracteres
			{
				Simbolo sim;
				$$.rotulo = "letra";
				sim.rotulo = $$.rotulo;
				$$.conteudo = $1.traducao;
				sim.conteudo = $$.conteudo;
				$$.temporaria = geraTemp();
				sim.temporaria = $$.temporaria;
				$$.tipo = "letra";
				sim.tipo = $$.tipo;
				$$.tipoTmp = "char";
				sim.tipoTmp = $$.tipoTmp;
				$$.declaracaoTmp = "\t" + $$.tipoTmp + " " + $$.temporaria + ";\n";
				sim.declaracaoTmp = $$.declaracaoTmp;
				$$.traducao = "\t" + $$.temporaria + " = " + $$.conteudo + ";\n";
				sim.traducao = $$.traducao;
				insereTabelaSimbolos(&sim);
			}
			| TK_BOOLEAN //booleanos
			{
				Simbolo sim;
				$$.rotulo = "booleano";
				sim.rotulo = $$.rotulo;

				if($1.traducao == "true"){
					$1.traducao = "1";
				}else{
					$1.traducao = "0";
				}

				$$.conteudo = $1.traducao;
				sim.conteudo = $$.conteudo;
				$$.temporaria = geraTemp();
				sim.temporaria = $$.temporaria;
				$$.tipo = "booleano";
				sim.tipo = $$.tipo;
				$$.tipoTmp = "int";
				sim.tipoTmp = $$.tipoTmp;
				$$.declaracaoTmp = "\t" + $$.tipoTmp + " " + $$.temporaria + ";\n";
				sim.declaracaoTmp = $$.declaracaoTmp;
				$$.traducao = "\t" + $$.temporaria + " = " + $$.conteudo + ";\n";
				sim.traducao = $$.traducao;
				insereTabelaSimbolos(&sim);
			}
			| TK_ID //nomes (identificadores)
			{	
				Simbolo *aux;
				if((aux = buscaTabelaSimbolos($1.rotulo)) != NULL){ //nome de variável existe
					$$.rotulo = $1.rotulo;
					$$.traducao = aux->traducao;
					$$.conteudo = aux->conteudo;
					$$.temporaria = aux->temporaria;
					$$.tipo = aux->tipo;
					$$.tipoTmp = aux->tipoTmp;
					$$.declaracaoTmp = aux->declaracaoTmp;
				}else{
					cout << "Identificador sem pai! D:\n";
					exit(1);
				}

				$$.rotulo = $1.rotulo;
				$$.traducao = $1.traducao;
				$$.conteudo = $1.conteudo;
				$$.temporaria = $1.temporaria;
				$$.tipo = $1.tipo;
				$$.tipoTmp = $1.tipoTmp;
				$$.declaracaoTmp = $1.declaracaoTmp;
			}
			;

%%

#include "lex.yy.c"

int yyparse();

int main( int argc, char* argv[] )
{
	yyparse();

	return 0;
}

void yyerror( string MSG )
{
	cout << MSG << endl;
	exit (0);
}				
