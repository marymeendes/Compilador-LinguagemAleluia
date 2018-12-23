%{
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

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

// struct bloco
// {
// 	int idBloco; //identificador do bloco
// 	//int idBlocoPai; //identificador do bloco pai
// 	vector<Simbolo> *ambiente; //ambiente de referenciamento
// };

typedef struct bloco Bloco;

int yylex(void);
void yyerror(string);

// vector<Simbolo> TabelaSimbolos;

vector<vector<Simbolo> > PilhaBlocos;

// int geraIdBloco(){
// 	static int id = 0;
// 	return id++;
// }

string geraTemp(){
	static int count = 0;
	count++;
	return "TMP"+to_string(count);
}

void insereTabelaSimbolos(vector<Simbolo> &tabela, Simbolo simbolo){

	tabela.push_back(simbolo);
}

void subirInfoPrimitiva(Simbolo *s, Simbolo aux, string rotulo, string traducao, string temp, string tipo, string tipoTmp){
	s->rotulo = rotulo;
	aux.rotulo = s->rotulo;
	s->conteudo = traducao;
	aux.conteudo = s->conteudo;
	s->temporaria = temp;
	aux.temporaria = s->temporaria;
	s->tipo = tipo;
	aux.tipo = s->tipo;
	s->tipoTmp = tipoTmp;
	aux.tipoTmp = s->tipoTmp;
	s->declaracaoTmp = "\t" + s->tipoTmp + " " + s->temporaria + ";\n";
	aux.declaracaoTmp = s->declaracaoTmp;
	s->traducao = "\t" + s->temporaria + " = " + s->conteudo + ";\n";
	aux.traducao = s->traducao;
	insereTabelaSimbolos((PilhaBlocos.back()), aux);
}

void preencheSimbolo(Simbolo aux, string rotulo, string traducao, string conteudo, string temp, string tipo, string tipoTmp, string declaracao){
	aux.rotulo = rotulo;
	aux.traducao = traducao;
	aux.conteudo = conteudo;
	aux.temporaria = temp;
	aux.tipo = tipo;
	aux.tipoTmp = tipoTmp;
	aux.declaracaoTmp = declaracao;
	insereTabelaSimbolos((PilhaBlocos.back()), aux);
}	

void empilhaPilhaBlocos(vector<Simbolo> bloco){
	PilhaBlocos.push_back(bloco);
}

void desempilhaPilhaBlocos(){
	PilhaBlocos.pop_back();
}

Simbolo* buscaPilhaBlocos(string rotulo)
{
	Simbolo *aux;
	for (int i = PilhaBlocos.size()-1; i >= 0; i--){
		for(int j = PilhaBlocos.at(i).size()-1; j >= 0; j--){
			if(PilhaBlocos.at(i).at(j).rotulo == rotulo){
				return &PilhaBlocos.at(i).at(j);
			}
		}
	}
	return NULL;
}

void printaPilhaBlocos()
{
	for (int i = PilhaBlocos.size()-1; i >= 0; i--){
		for(int j = PilhaBlocos.at(i).size()-1; j >= 0; j--){
			printf("\n----%s[%d][%d]----\n", PilhaBlocos.at(i).at(j).rotulo.c_str(), i, j);
		}
	}
}

// Bloco* buscaPilhaBlocosPorID(int id){
// 	for(vector<Bloco *>::iterator it = PilhaBlocos.end(); it != PilhaBlocos.begin(); it++){
// 		if((*it)->idBloco == id){
// 			return *it;
// 		}
// 	}

// 	return NULL;
// }

// Simbolo* buscaPilhaBlocos(string rotulo){
// 	Simbolo *s;
// 	cout << PilhaBlocos.size();

// 	//catando
// 	for(int i = PilhaBlocos.size()-1; i >= 0; i--){
// 		if((s = buscaTabelaSimbolos(PilhaBlocos, rotulo)) != NULL){ //achei
// 			cout << "oi";
// 			return s;
// 		}
// 	}
	
// 	return NULL;
// }


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
				cout << $5.traducao << "\treturn 0;\n}" << endl; 
			
			}
			;

BLOCO		: X '{' COMANDOS BLOCO '}'
			{
				//processo de fechamento do bloco é aqui
				cout << "estive aqui no fechamento.";
				string declaracoes = "";
				for (int i = PilhaBlocos.size()-1; i >= 0; i--){
					for(int j = PilhaBlocos.at(i).size()-1; j >= 0; j--){

						declaracoes = declaracoes + PilhaBlocos.at(i).at(j).declaracaoTmp;
							
					}
				}
				$$.traducao = "\t{" + declaracoes + $3.traducao + $4.traducao + "\t}";
				cout << "e antes do desempilha tbm.\n";
				desempilhaPilhaBlocos();
				cout << "e depois do desempilha tbm.\n";
			}
			|
			{
				$$.traducao = "";
			}
			;

X			: //identificado um bloco:
			{
				vector<Simbolo> bloco;

				cout << "estive aqui no empilhamento\n";

				empilhaPilhaBlocos(bloco);

				cout << "estive aqui no empilhamento2\n";

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
				Simbolo *aux, sim;
				
				if((aux = buscaPilhaBlocos($2.rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string temporaria = geraTemp();
					if($1.rotulo == "int" || $1.rotulo == "booleano")
						tipoTmp = "int";
					else if($1.rotulo == "real")
						tipoTmp = "float";
					else if($1.rotulo == "letra"){
						tipoTmp = "char";
					}
					declaracaoTmp = "\t" + tipoTmp + " " + temporaria + ";\n";
					preencheSimbolo(sim, $2.rotulo, "", "none", temporaria, $1.rotulo, tipoTmp, declaracaoTmp);
					printaPilhaBlocos();
					printf("\n++++++++++++++++\n");
				}else{
					cout << "Variável " + $2.rotulo + " já foi declarada antes!";
					exit(1);
				}

			}
			| TK_ID '=' G ';' //atribuicao
			{	
				Simbolo *aux, sim;
				if((aux = buscaPilhaBlocos($1.rotulo)) != NULL){
					if(aux->tipoTmp == $3.tipoTmp && aux->tipo == $3.tipo){ //senão precisar de conversão
						$$.traducao = $3.traducao + "\t" + aux->temporaria + " = " + $3.temporaria + ";\n";
					}else if(aux->tipoTmp == "float" && $3.tipoTmp =="int" || aux->tipoTmp == "int" && $3.tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + $3.temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						preencheSimbolo(sim, "conversao", traducao, "none", converteVar, aux->tipoTmp, aux->tipoTmp, declaracaoTmp);

						$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + converteVar + ";\n";
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
				string traducao;
				string declaracaoTmp;

				if($3.tipoTmp == "char"){ //só pq não pode entre char e outra coisa
					cout << "Operacao não suportada para tipo letra!\n";
					exit(1);
				}

				if($1.rotulo == "inteirao"){
					traducao = "\t" + converteVar + " = " + "(int)" + $3.temporaria + ";\n";
					declaracaoTmp = "\tint " + converteVar + ";\n";
					preencheSimbolo(sim1, "conversao", traducao, "none", converteVar, "int", "int", declaracaoTmp);
					sim2.tipo = "int";
					sim2.tipoTmp = "int";
						
				}else if($1.rotulo == "flutua"){
					traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
					declaracaoTmp = "\tfloat " + converteVar + ";\n";
					preencheSimbolo(sim1, "conversao", traducao, "none", converteVar, "real", "float", declaracaoTmp);
					sim2.tipo = "real";
					sim2.tipoTmp = "float";

				}
				$$.traducao = $3.traducao + traducao;

				string opVar = geraTemp();
				sim2.rotulo = "operacao";
				sim2.temporaria = opVar;

				sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
				
				sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + ";\n";

				insereTabelaSimbolos((PilhaBlocos.back()), sim2);

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
				Simbolo sim;
				string op;
				if($2.rotulo == "ou"){
					op = "||";
				}
				else{
					op = "&&";
				}
				if($1.tipo == "booleano" && $3.tipo == "booleano"){
					$$.temporaria = geraTemp();
					$$.declaracaoTmp = "\tint " + $$.temporaria + ";\n";
					string traducao = "\t" + $$.temporaria + " = " + $1.temporaria + " " + op + " " + $3.temporaria + ";\n"; 
					preencheSimbolo(sim, "operacao", traducao, "none", $$.temporaria, "booleano", "int", $$.declaracaoTmp);

					$$.rotulo = "operacao";
					$$.conteudo = "none";
					$$.tipoTmp = "int";
					$$.tipo = "booleano";
					$$.traducao = $1.traducao + $3.traducao + traducao;
				}else{
					cout << "Operacao lógica so entre booleanos, bb.\n";
					exit(1);
				}	
			}
			| G TK_REL E //operações relacionais
			{
			
				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteuOp2 = false; //var aux para saber qual operando foi convertido, nesse caso ela aciona na conversão do 2º operando
				string converteVar = "none";
				$$.traducao = $1.traducao + $3.traducao;

				if($1.tipoTmp != $3.tipoTmp){ //conversão

					if($1.tipoTmp == "char" || $3.tipoTmp == "char"){ //só pq não pode entre char e outra coisa
						cout << "Operacao não suportada entre letra e não-letra!\n";
						exit(1);
					}

					converteu = true;
					converteVar = geraTemp();
					string traducao, declaracaoTmp;

					if($1.tipoTmp == "float"){
						converteuOp2 = true;
						traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
						declaracaoTmp = "\t" + $1.tipoTmp + " " + converteVar + ";\n";
						preencheSimbolo(sim1, "conversao", traducao, "none", converteVar, $1.tipoTmp, $1.tipoTmp, declaracaoTmp);
						
					}else if($3.tipoTmp == "float"){

						traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
						declaracaoTmp = "\t" + $3.tipoTmp + " " + converteVar + ";\n";
						preencheSimbolo(sim1, "conversao", traducao, "none", converteVar, $3.tipoTmp, $3.tipoTmp, declaracaoTmp);
					}

					$$.traducao = $$.traducao + traducao;
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
					if(converteuOp2){
						sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + converteVar + ";\n";
					}
					else{
						sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + $2.rotulo + $3.temporaria + ";\n";
					}
				}else{
					sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + $3.temporaria + ";\n";
				}

				insereTabelaSimbolos((PilhaBlocos.back()), sim2);

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
				bool converteuOp2 = false; //var aux para saber qual operando foi convertido, nesse caso ela aciona na conversão do 2º operando
				string converteVar = "none";
				$$.traducao = $1.traducao + $3.traducao;

				if($1.tipoTmp != $3.tipoTmp){ //conversão
					converteu = true;
					converteVar = geraTemp();
					string traducao, declaracaoTmp;
					if($1.tipoTmp == "float"){
						converteuOp2 = true;
						traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
						declaracaoTmp = "\t" + $1.tipoTmp + " " + converteVar + ";\n";
						preencheSimbolo(sim1, "conversao", traducao, "none", converteVar, $1.tipoTmp, $1.tipoTmp, declaracaoTmp);
						
					}else if($3.tipoTmp == "float"){

						traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
						declaracaoTmp = "\t" + $3.tipoTmp + " " + converteVar + ";\n";
						preencheSimbolo(sim1, "conversao", traducao, "none", converteVar, $3.tipoTmp, $3.tipoTmp, declaracaoTmp);
					}

					$$.traducao = $$.traducao + traducao;
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
					if(converteuOp2){
						sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + converteVar + ";\n";
					}
					else{
						sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + $2.rotulo + $3.temporaria + ";\n";
					}
				}else{
					sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + $3.temporaria + ";\n";
				}
				insereTabelaSimbolos((PilhaBlocos.back()), sim2);

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
				bool converteuOp2 = false; //var aux para saber qual operando foi convertido, nesse caso ela aciona na conversão do 2º operando
				string converteVar = "none";
				$$.traducao = $1.traducao + $3.traducao;

				if($1.tipoTmp != $3.tipoTmp){ //conversão
					converteu = true;
					converteVar = geraTemp();
					string traducao, declaracaoTmp;
					if($1.tipoTmp == "float"){
						converteuOp2 = true;
						traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
						declaracaoTmp = "\t" + $1.tipoTmp + " " + converteVar + ";\n";
						preencheSimbolo(sim1, "conversao", traducao, "none", converteVar, $1.tipoTmp, $1.tipoTmp, declaracaoTmp);
						
					}else if($3.tipoTmp == "float"){

						traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
						declaracaoTmp = "\t" + $3.tipoTmp + " " + converteVar + ";\n";
						preencheSimbolo(sim1, "conversao", traducao, "none", converteVar, $3.tipoTmp, $3.tipoTmp, declaracaoTmp);
					}

					$$.traducao = $$.traducao + traducao;
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
					if(converteuOp2){
						sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + converteVar + ";\n";
					}
					else{
						sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + $2.rotulo + $3.temporaria + ";\n";
					}
				}else{
					sim2.traducao = "\t" + sim2.temporaria + " = " + $1.temporaria + $2.rotulo + $3.temporaria + ";\n";
				}
				insereTabelaSimbolos((PilhaBlocos.back()), sim2);

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
				subirInfoPrimitiva(&$$, sim, "inteiro", $1.traducao, geraTemp(), "int", "int");
			}
			| TK_REAL //floats
			{
				Simbolo sim;
				subirInfoPrimitiva(&$$, sim, "real", $1.traducao, geraTemp(), "real", "float");
			}
			| TK_CHAR //caracteres
			{
				Simbolo sim;
				subirInfoPrimitiva(&$$, sim, "letra", $1.traducao, geraTemp(), "letra", "char");
			}
			| TK_BOOLEAN //booleanos
			{
				if($1.traducao == "falso"){
					$1.traducao = "0";
				}else{
					$1.traducao = "1";
				}
				Simbolo sim;
				subirInfoPrimitiva(&$$, sim, "booleano", $1.traducao, geraTemp(), "booleano", "int");
			}
			| TK_ID //nomes (identificadores)
			{	
				Simbolo *aux;
				if((aux = buscaPilhaBlocos($1.rotulo)) != NULL){ //nome de variável existe
					$$.rotulo = $1.rotulo;
					$$.traducao = aux->traducao;
					$$.conteudo = aux->conteudo;
					$$.temporaria = aux->temporaria;
					$$.tipo = aux->tipo;
					$$.tipoTmp = aux->tipoTmp;
					$$.declaracaoTmp = aux->declaracaoTmp;
				}else{
					yyerror("Identificador sem pai! D:");
				}
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
