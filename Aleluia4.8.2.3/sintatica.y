/*Esta foi  versão final do trabalho entregue dia 12/12/2018 
Grupo: Mariana Mendes, Beatriz Silva e Bárbara Ayres*/

/*Nesta versão falta: switch, além de dar free nas strings (proveniente da Spring 2), funções e matrizes multidimensionais e inicialização de matrizes*/
/*E temos matrizes, operadores unários e compostos e inicialização de variáveis e reporte de erros com informação da linha*/

%{
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

#define YYSTYPE atributos

using namespace std;
int num_linhas = 1;

struct atributos
{
	string rotulo; //nomes de alto nível (se houver)
	string traducao; // valores e significados do token
	string conteudo; //conteudo do simbolo (valor)
	string temporaria; // variável de baixo nível associada
	string tipo; // tipo em alto nível
	string tipoTmp; // tipo da temporária associada
	string declaracaoTmp; //string de declaracao da temporária associada
	int verificadorInicializacao = 0; //verificador de não inicialização de variável
	string tempLinhas; //reservado para matrizes
	string tempColunas; //reservado para matrizes
};

typedef struct atributos Simbolo;

struct bound
{
	string continuar; //nomes de alto nível (se houver)
	string continuar2;
	string quebrar; // valores e significados do token
	int gambiarra;
};

typedef struct bound Laco;

struct se
{
	string inicio; //nomes de alto nível (se houver)
	string fim;
};

typedef struct se Cond;

struct cadeia
{
	string nomeVar;
	int tam;
	string tempTam;
	string tempNome;
};
typedef struct cadeia Cadeia;

int yylex(void);
void yyerror(string);

vector<Laco> PilhaLaco;
vector<Cond> PilhaIf;
vector<Cadeia> TabelaCadeias;
vector<Simbolo> VarGlobais;
vector<vector<Simbolo> > PilhaBlocos;
vector<string> VariaveisPossiveis;
string declaracoes = "";
string declaracoesGlobais = "";
string apresentacao = "";
string inicio = "";

vector<string> AlvoSwitch;


string geraTemp(){
	static int count = 0;
	count++;
	return "TMP"+to_string(count);
}

string geraBloco(){
	static int countBia = 0;
	countBia++;
	return "broquinho"+to_string(countBia);
}

void insereTabelaSimbolos(vector<Simbolo> &tabela, Simbolo *simbolo){

	tabela.push_back(*simbolo);
}

void subirInfoPrimitiva(Simbolo *s, Simbolo aux, string rotulo, string traducao, string temp, string tipo, string tipoTmp){
	s->rotulo = rotulo;
	s->conteudo = traducao;
	s->temporaria = temp;
	s->tipo = tipo;
	s->tipoTmp = tipoTmp;
	s->declaracaoTmp = "\t" + s->tipoTmp + " " + s->temporaria + ";\n";
	declaracoes.append(s->declaracaoTmp);
	s->traducao = "\t" + s->temporaria + " = " + s->conteudo + ";\n";
	insereTabelaSimbolos((PilhaBlocos.back()), s);
}

void preencheSimbolo(Simbolo *aux, string rotulo, string traducao, string conteudo, string temp, string tipo, string tipoTmp, string declaracao){
	aux->rotulo = rotulo;
	aux->traducao = traducao;
	aux->conteudo = conteudo;
	aux->temporaria = temp;
	aux->tipo = tipo;
	aux->tipoTmp = tipoTmp;
	aux->declaracaoTmp = declaracao;
	insereTabelaSimbolos((PilhaBlocos.back()), aux);
}

void preencheSimboloMatriz(Simbolo *aux, string rotulo, string traducao, string conteudo, string temp, string tipo, string tipoTmp, string declaracao, string tempLin, string tempCol){
	aux->rotulo = rotulo;
	aux->traducao = traducao;
	aux->conteudo = conteudo;
	aux->temporaria = temp;
	aux->tipo = tipo;
	aux->tipoTmp = tipoTmp;
	aux->declaracaoTmp = declaracao;
	aux->tempLinhas = tempLin;
	aux->tempColunas = tempCol;
	insereTabelaSimbolos((PilhaBlocos.back()), aux);
}

void empilhaPilhaBlocos(vector<Simbolo> bloco){
	PilhaBlocos.push_back(bloco);
}

void empilhaLaco(Laco laco){
	PilhaLaco.push_back(laco);
}

void empilhaIf(Cond cond){
	PilhaIf.push_back(cond);
}

void desempilhaPilhaBlocos(){
	PilhaBlocos.pop_back();
}

void desempilhaLaco(){
	PilhaLaco.pop_back();
}

void desempilhaIf(){
	PilhaIf.pop_back();
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

Simbolo* buscaBlocoAtual(string rotulo)
{
	Simbolo *aux;
	for (int i = PilhaBlocos.back().size()-1; i >= 0; i--){
		if(PilhaBlocos.back().at(i).rotulo == rotulo){
			return &PilhaBlocos.back().at(i);
		}
	}
	return NULL;
}

void printaPilhaBlocos()
{
	for (int i = PilhaBlocos.size()-1; i >= 0; i--){
		for(int j = PilhaBlocos.at(i).size()-1; j >= 0; j--){
			printf("\n----%s[%d][%d]----\n", PilhaBlocos.at(i).at(j).rotulo.c_str(), i, j);
			printf("\n----%s[%d][%d]----\n", PilhaBlocos.at(i).at(j).tipoTmp.c_str(), i, j);
			printf("\n----%s[%d][%d]----\n", PilhaBlocos.at(i).at(j).temporaria.c_str(), i, j);
			printf("\n----%s[%d][%d]----\n", PilhaBlocos.at(i).at(j).conteudo.c_str(), i, j);
		}
	}
}

void insereVetorGlobais(Simbolo simbolo){
	VarGlobais.push_back(simbolo);
}

Simbolo* buscaVetorGlobais(string rotulo){
	Simbolo* aux;
	for(vector<Simbolo>::iterator it = VarGlobais.begin(); it != VarGlobais.end(); it++){
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

void preencheGlobal(Simbolo aux, string rotulo, string traducao, string conteudo, string temp, string tipo, string tipoTmp, string declaracao){
	aux.rotulo = rotulo;
	aux.traducao = traducao;
	aux.conteudo = conteudo;
	aux.temporaria = temp;
	aux.tipo = tipo;
	aux.tipoTmp = tipoTmp;
	aux.declaracaoTmp = declaracao;
	insereVetorGlobais(aux);
}

void insereTabelaCadeias(Cadeia s){
	TabelaCadeias.push_back(s);
}

void subirInfoString(Simbolo *s, Simbolo aux, string rotulo, string traducao, string temp, string tipo, string tipoTmp, string tempTam, string tam){
	s->rotulo = rotulo;
	s->conteudo = traducao;
	s->temporaria = temp;
	s->tipo = tipo;
	s->tipoTmp = tipoTmp;
	s->declaracaoTmp = "\t" + s->tipoTmp + " " + s->temporaria + ";\n";
	declaracoes.append(s->declaracaoTmp);
	s->traducao = "\t" + tempTam + " = " + tam + ";\n" + "\t" + s->temporaria + " = " + "(char *) malloc(" + tempTam + " * sizeof(char));\n" + "\t" + s->temporaria + " = strcpy(" + s->temporaria + ", " + s->conteudo + ");\n";
	insereTabelaSimbolos((PilhaBlocos.back()), s);

}

void buscaInfoCadeia(Cadeia *aux, string temp){
	for(vector<Cadeia>::iterator it = TabelaCadeias.begin(); it != TabelaCadeias.end(); it++){
		if(it->tempNome == temp){
			aux->nomeVar = it->nomeVar;
			aux->tam = it->tam;
			aux->tempTam = it->tempTam;
			aux->tempNome = it->tempNome;
		}
	}
}

%}

%token TK_TIPO //para os tipos
%token TK_MAIN TK_ID //main e identificador
%token TK_FIM TK_ERROR //fim e erro
%token TK_CONVERTE //conversão pra float e int (EXPLÍCITA)
%token TK_SUM_SUB TK_MUL_DIV // soma e subtracao, multiplicacao e divisao
%token TK_REL TK_LOG //operadores lógicos e relacionais
%token TK_BOOLEAN TK_NUM TK_REAL TK_CHAR TK_CADEIA// valores: booleanos, inteiros, reais e caracteres
%token TK_IF TK_ELIF TK_ELSE TK_WHILE TK_FOR TK_DO TK_SWITCH TK_OP_SWITCH//começo do if, else, etc
%token TK_CONT TK_BREAK
%token TK_OUT //saída
%token TK_IN //entrada
%token TK_COMP TK_UNA //operadores compostos

%start S

%left TK_LOG
%left '<' '>' LE GE EQ NE
%left TK_SUM_SUB
%left TK_MUL_DIV
%%

S			: A
			{
				cout << "\n" + apresentacao << "\n" + declaracoesGlobais + "\n" << inicio << endl;
			}

A 			: TK_TIPO TK_ID ';' A //declaração de variável global
			{
				Simbolo *aux, sim;

				if((aux = buscaVetorGlobais($2.rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string temporaria = geraTemp();
					if($1.rotulo == "int" || $1.rotulo == "booleano")
						tipoTmp = "int";
					else if($1.rotulo == "real")
						tipoTmp = "float";
					else if($1.rotulo == "letra")
						tipoTmp = "char";
					else if($1.rotulo == "cadeia")
						tipoTmp = "char *";

					declaracaoTmp = tipoTmp + " " + temporaria + ";\n";

					preencheGlobal(sim, $2.rotulo, "", "none", temporaria, $1.rotulo, tipoTmp, declaracaoTmp);

					declaracoesGlobais.append(declaracaoTmp);

				}else{
					cout << "Variável global " + $2.rotulo + " já foi declarada antes!";
					exit(1);
				}
			}
			| TK_MAIN '(' ')' BLOCO
			{
				apresentacao.append("/*Compilador ALELUIA*/\n#include <iostream>\n#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n\nusing namespace std;\n");
				inicio.append("int main(void)\n{\n" + declaracoes + "\n" + $4.traducao + "\treturn 0;\n}");
			}
			;

BLOCO		: X '{' COMANDOS '}'
			{
				//processo de fechamento do bloco é aqui
				//cout << "estive aqui no fechamento.";
				$$.traducao = $3.traducao;
				//cout << "e antes do desempilha tbm.\n";
				if(VariaveisPossiveis.size() > 0){
					cout << "Variáveis ";
					for(int i = 0; i < VariaveisPossiveis.size(); i++){
						cout << VariaveisPossiveis.at(i) << ", ";
					}
					cout << "não foram declaradas!!!\n";
				}
				desempilhaPilhaBlocos();
				//cout << "e depois do desempilha tbm.\n";
			}
			;

ELIF 		: TK_ELIF '(' G ')' BLOCO ELIF
 			{
				Simbolo sim;
 				string temporaria3	= geraTemp();
				string tipoTmp3 = "int";
				string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
				string atribuicao3 = "\t" + temporaria3 + " = " + "!" + $3.temporaria + ";\n";
				preencheSimbolo(&sim, "teste", atribuicao3, "none", temporaria3, "booleano", tipoTmp3, declaracaoTmp3);
 				string aux1, fim, aux3;
 				declaracoes.append(declaracaoTmp3);
 				if(PilhaIf.empty())
 				{
 					cout << "isso aqui não pode.\n";
 					exit(1);
 				}
 				else if(PilhaIf.back().fim == "")
 				{
 					PilhaIf.back().fim = geraBloco();

 				}


 				fim = "goto " + PilhaIf.back().fim + ";";
 				aux3 = PilhaIf.back().fim + ":";

 				aux1 = geraBloco();
 				//aux2 = geraBloco();
 				$$.traducao = $3.traducao + atribuicao3 + "\tif(" + temporaria3 + ") goto "+ aux1 + ";\n" + $5.traducao +"\t"+ fim +"\n\t"+ aux1 + ":\n" + $6.traducao + "\n";
 				//cout << "entrei no if.\n";

 			}

			| TK_ELSE BLOCO
 			{
 				$$.traducao = $2.traducao;
 			}
 			|
 			{
 				$$.traducao = "";
 			}
 			;

DECLARACAO 	: TK_ID '=' G //atribuicao
			{
				Simbolo *aux, sim;
				if((aux = buscaPilhaBlocos($1.rotulo)) != NULL){
					if(aux->tipoTmp == $3.tipoTmp && aux->tipo == $3.tipo){ //senão precisar de conversão
						$$.traducao = $3.traducao + "\t" + aux->temporaria + " = " + $3.temporaria + ";\n";

						if($3.tipo == "cadeia"){
						  	Cadeia cad;
						  	buscaInfoCadeia(&cad, $3.temporaria);
						  	cad.tempNome = aux->temporaria;
						  	insereTabelaCadeias(cad);
						}

					}else if(aux->tipoTmp == "float" && $3.tipoTmp =="int" || aux->tipoTmp == "int" && $3.tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + $3.temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						declaracoes.append(declaracaoTmp);
						preencheSimbolo(&sim, "conversao", traducao, "none", converteVar, aux->tipoTmp, aux->tipoTmp, declaracaoTmp);

						$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + converteVar + ";\n";
					}
					else{
						cout << "Essa atribuicao não pode! \n";
						exit(1);
					}
				}

				// if($3.tipoTmp == "cadeia"){ //se passou na verificação e é string, adiciono na cadeia da lista, o nome da variável que recebeu a string
				//  	Cadeia cad;
				//  	cout << "opa\n";
				//  	buscaInfoCadeia(&cad, $3.temporaria);
				//  	if(cad == NULL)
				//  		cout << "deu ruimzão\n";
				//  	cout << "oi\n";
				//  	cad.nomeVar = $1.rotulo;
				// }

				$$.rotulo = "atribuicao";
				$$.conteudo = "none";
				$$.temporaria = aux->temporaria;
				$$.tipo = aux->temporaria;
				$$.tipoTmp = $$.tipo;
				$$.declaracaoTmp = aux->declaracaoTmp;
			}
			;

X			: //identificado um bloco:
			{
				vector<Simbolo> bloco;
				empilhaPilhaBlocos(bloco);
			}
			;

Z			: //identificado um bloco:
			{
				Laco aux;
				aux.continuar = "";
				aux.continuar2 = "";
				aux.quebrar = "";
				empilhaLaco(aux);
			}
			;

N			: //identificado um bloco:
			{
				Cond aux;
				aux.inicio = "";
				aux.fim = "";
				empilhaIf(aux);
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
				$$.rotulo = $1.rotulo;
				$$.traducao = $1.traducao;
				$$.conteudo = $1.conteudo;
				$$.temporaria = $1.temporaria;
				$$.tipo = $1.tipo;
				$$.tipoTmp = $1.tipoTmp;
				$$.declaracaoTmp = $1.declaracaoTmp;
				$$.verificadorInicializacao = $1.verificadorInicializacao;
			}
			| TK_TIPO TK_ID '[' E ',' E ']' ';' //matrizes:declaração
			{
				if($1.rotulo == "cadeia" || $1.rotulo == "booleano"){
					yyerror("Desculpe: Tipo não suportado para matrizes!\n");
				}
				if($4.tipo != "int" || $6.tipo != "int"){
					yyerror("Limites para o tamanho da matriz não suportados!\n");
				}

				Simbolo *aux, sim;
				if((aux = buscaBlocoAtual($2.rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string traducao;
					string temporaria = geraTemp();
					if($1.rotulo == "int")
						tipoTmp = "int";
					else if($1.rotulo == "real")
						tipoTmp = "float";
					else if($1.rotulo == "letra")
						tipoTmp = "char";

					declaracaoTmp = "\t" + tipoTmp + " " + temporaria + ";\n";
					declaracoes.append(declaracaoTmp);
					traducao = "\t" + temporaria + " = " + "("+ tipoTmp +"*)malloc(" + $4.temporaria +"*"+ $6.temporaria +"*sizeof("+ tipoTmp +"));\n";
					preencheSimboloMatriz(&sim, $2.rotulo, traducao, "none", temporaria, $1.rotulo, tipoTmp, declaracaoTmp, $4.temporaria, $6.temporaria);
				}else{
					yyerror("Variável " + $2.rotulo + " já foi declarada antes!\n");
				}

				$$.traducao = $4.traducao + $6.traducao + sim.traducao;
			}
			| TK_ID '[' E ',' E ']' '=' G ';' //atribuição de valor a item da matriz
			{
				if($8.tipo == "cadeia" || $8.tipo == "booleano"){
					yyerror("Desculpe: Tipo de dado não suportado para matrizes!\n");
				}

				Simbolo *aux, sim;
				string buffer;
				if((aux = buscaPilhaBlocos($1.rotulo)) != NULL){ //se a variável existe
					buffer = aux->temporaria;
					string multiplica, soma;
					multiplica = geraTemp();
					soma = geraTemp();
					string declaracaoMultiplica = "\tint " + multiplica + ";\n";
					declaracoes.append(declaracaoMultiplica);
					string declaracaoSoma = "\tint " + soma + ";\n";
					declaracoes.append(declaracaoSoma);

					string tradMultiplica;
					string tradSoma;

					if(aux->tipoTmp == $8.tipoTmp && aux->tipo == $8.tipo){ //senão precisar de conversão
						tradMultiplica = "\t" + multiplica + " = " + $3.temporaria +"*"+ aux->tempColunas + ";\n";
						tradSoma = "\t" + soma + " = " + multiplica + "+" + $5.temporaria + ";\n";

						$$.traducao = $8.traducao + $3.traducao + $5.traducao + tradMultiplica + tradSoma + "\t" + aux->temporaria +"["+ soma +"]" + " = " + $8.temporaria + ";\n";
						if($3.tipo == "cadeia"){
						  	Cadeia cad;
						  	buscaInfoCadeia(&cad, $3.temporaria);
						  	cad.tempNome = aux->temporaria;
						  	insereTabelaCadeias(cad);
						}
						buffer = aux->temporaria;

					}else if(aux->tipoTmp == "float" && $8.tipoTmp == "int" || aux->tipoTmp == "int" && $8.tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + $8.temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						declaracoes.append(declaracaoTmp);

						tradMultiplica = "\t" + multiplica + " = " + $3.temporaria +"*"+ aux->tempColunas + ";\n";
						tradSoma = "\t" + soma + " = " + multiplica + "+" + $5.temporaria + ";\n";

						$$.traducao = $8.traducao + $3.traducao + $5.traducao + tradMultiplica + tradSoma + traducao + "\t" + aux->temporaria +"["+ soma +"]" + " = " + converteVar + ";\n";
						buffer = aux->temporaria; // pq some
						preencheSimbolo(&sim, "conversao", traducao, "none", converteVar, aux->tipo, aux->tipoTmp, declaracaoTmp);
					}
					else{
						yyerror("Essa atribuicao não pode! \n");
					}
					preencheSimbolo(&sim, "contaIndice", tradMultiplica, "none", multiplica, "int", "int", declaracaoMultiplica);
					preencheSimbolo(&sim, "contaIndice", tradSoma, "none", soma, "int", "int", declaracaoSoma);
				}else{
					yyerror("Matriz não declarada!!!");
				}

				aux->temporaria = buffer;

				$$.rotulo = "atribuicao";
				$$.conteudo = "none";
				$$.temporaria = aux->temporaria;
				$$.tipo = aux->tipo;
				$$.tipoTmp = aux->tipoTmp;
				$$.declaracaoTmp = aux->declaracaoTmp;
			}
			| TK_TIPO TK_ID ';' //declaração
			{
				$$.traducao = "";
				Simbolo *aux, sim;

				if((aux = buscaBlocoAtual($2.rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string temporaria = geraTemp();
					if($1.rotulo == "int" || $1.rotulo == "booleano")
						tipoTmp = "int";
					else if($1.rotulo == "real")
						tipoTmp = "float";
					else if($1.rotulo == "letra")
						tipoTmp = "char";
					else if($1.rotulo == "cadeia")
						tipoTmp = "char *";

					declaracaoTmp = "\t" + tipoTmp + " " + temporaria + ";\n";
					declaracoes.append(declaracaoTmp);
					preencheSimbolo(&sim, $2.rotulo, "", "none", temporaria, $1.rotulo, tipoTmp, declaracaoTmp);
				}else{
					yyerror("Variável " + $2.rotulo + " já foi declarada antes!\n");
				}

			}
			| TK_ID '=' G ';' //atribuicao
			{
				Simbolo *aux, sim;
				string buffer;
				if((aux = buscaPilhaBlocos($1.rotulo)) != NULL){
					buffer = aux->temporaria;
					if(aux->tipoTmp == $3.tipoTmp && aux->tipo == $3.tipo){ //senão precisar de conversão
						$$.traducao = $3.traducao + "\t" + aux->temporaria + " = " + $3.temporaria + ";\n";
						aux->conteudo = $3.conteudo;
						if($3.tipo == "cadeia"){
						  	Cadeia cad;
						  	buscaInfoCadeia(&cad, $3.temporaria);
						  	cad.tempNome = aux->temporaria;
						  	insereTabelaCadeias(cad);
						}
						buffer = aux->temporaria;

					}else if(aux->tipoTmp == "float" && $3.tipoTmp == "int" || aux->tipoTmp == "int" && $3.tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + $3.temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						declaracoes.append(declaracaoTmp);

						$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + converteVar + ";\n";
						buffer = aux->temporaria; // pq some dps da linha 521
						aux->conteudo = $3.conteudo;
						preencheSimbolo(&sim, "conversao", traducao, "none", converteVar, aux->tipo, aux->tipoTmp, declaracaoTmp);
					}
					else{
						yyerror("Essa atribuicao não pode! \n");
					}
				}else{
					yyerror("Variável não declarada!\n");
				}

				aux->temporaria = buffer;

				$$.rotulo = "atribuicao";
				$$.conteudo = "none";
				$$.temporaria = aux->temporaria;
				$$.tipo = aux->tipo;
				$$.tipoTmp = aux->tipoTmp;
				$$.declaracaoTmp = aux->declaracaoTmp;
			}
			| TK_TIPO TK_ID '=' G ';' //inicialização de variável
			{
				$$.traducao = "";
				Simbolo *aux, sim;

				if((aux = buscaBlocoAtual($2.rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string temporaria = geraTemp();
					if($1.rotulo == "int" || $1.rotulo == "booleano")
						tipoTmp = "int";
					else if($1.rotulo == "real")
						tipoTmp = "float";
					else if($1.rotulo == "letra")
						tipoTmp = "char";
					else if($1.rotulo == "cadeia")
						tipoTmp = "char *";

					declaracaoTmp = "\t" + tipoTmp + " " + temporaria + ";\n";
					declaracoes.append(declaracaoTmp);
					preencheSimbolo(&sim, $2.rotulo, "", "none", temporaria, $1.rotulo, tipoTmp, declaracaoTmp);

					if($4.verificadorInicializacao == 1){
						VariaveisPossiveis.pop_back(); //desempilha o rotulo de TK_ID
						cout << "Atenção: Operação com variável não inicializada!\n"; //libera warning
					}

					///parte da atribuição
					if(sim.tipoTmp == $4.tipoTmp && sim.tipo == $4.tipo){ //senão precisar de conversão
						$$.traducao = $$.traducao + $4.traducao + "\t" + sim.temporaria + " = " + $4.temporaria + ";\n";

						if($4.tipo == "cadeia"){
						  	Cadeia cad;
						  	buscaInfoCadeia(&cad, $4.temporaria);
						  	cad.tempNome = sim.temporaria;
						  	insereTabelaCadeias(cad);
						}

					}else if(sim.tipoTmp == "float" && $4.tipoTmp == "int" || sim.tipoTmp == "int" && $4.tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + sim.tipoTmp + ")" + $4.temporaria + ";\n";
						string declaracaoTmp = "\t" + sim.tipoTmp + " " + converteVar + ";\n";
						declaracoes.append(declaracaoTmp);
						preencheSimbolo(&sim, "conversao", traducao, "none", converteVar, sim.tipoTmp, sim.tipoTmp, declaracaoTmp);

						$$.traducao = $$.traducao + $4.traducao + traducao + "\t" + temporaria + " = " + converteVar + ";\n";
					}
					else{
						yyerror("Essa atribuicao não pode! \n");
					}

					$$.rotulo = "atribuicao";
					$$.conteudo = "none";
					$$.temporaria = sim.temporaria;
					$$.tipo = sim.temporaria;
					$$.tipoTmp = $$.tipo;
					$$.declaracaoTmp = sim.declaracaoTmp;

				}else{
					yyerror("Variável " + $2.rotulo + " já foi declarada antes!\n");
				}
			}
			| TK_ID TK_UNA ';' //unários
			{
				Simbolo *aux;
				if((aux = buscaPilhaBlocos($1.rotulo)) != NULL){
					string gambiarra = aux->temporaria;
					// cout << gambiarra + "aqui\n";
					// printaPilhaBlocos();

					if(aux->tipo == "cadeia" || aux->tipo == "letra")
					{
						yyerror("Essa atribuicao não pode! \n");
					}
					else
					{
						//caso a variavél não esteja inicializada D:
						if(aux->conteudo == "none"){
							cout << "Atenção: Incrementando variável não inicializada!\n";
							$$.traducao = "\t" + aux->temporaria + " = 1;\n";
						}
						string composto = geraTemp();
						string unario = geraTemp();
						//string traducao = "\t" + composto + " = " + "(" + aux->tipoTmp + ")" + $3.temporaria + ";\n";
						string traducao, traducaoUna;
						if(aux->tipo == "real")
						{
							traducaoUna = "\t" + unario + " = 1.0;\n";
						}
						else if(aux->tipo == "int")
						{
							traducaoUna = "\t" + unario + " = 1;\n";
						}
						string declaracaoUna = "\t" + aux->tipoTmp + " " + unario + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + composto + ";\n";
						declaracoes.append(declaracaoTmp);
						declaracoes.append(declaracaoUna);
						if($2.rotulo == "++"){
							string traducao = traducaoUna + "\t" + composto + " = "+ gambiarra + " + "+ unario + ";\n";
							$$.traducao = $$.traducao + traducao + "\t" + gambiarra + " = " + composto + ";\n";
						}
						else if($2.rotulo == "--"){
							string traducao = traducaoUna + "\t" + composto + " = "+ gambiarra + " - "+ unario + ";\n";
							$$.traducao = $$.traducao + traducao + "\t" + gambiarra + " = " + composto + ";\n";
						}
					}
				}
			}
			| TK_ID TK_COMP G ';' //operadores compostos
			{
				Simbolo *aux, sim, sim2, sim3, sim4;
				string buffer;
				if((aux = buscaPilhaBlocos($1.rotulo)) != NULL){

					buffer = aux->temporaria;

					if($3.verificadorInicializacao == 1){
						VariaveisPossiveis.pop_back(); //desempilha o rotulo de TK_ID
						cout << "Atenção: Operação com variável não inicializada!\n"; //libera warning
					}


					if(aux->tipo == "letra" || $3.tipo == "letra")
					{
						cout << "Essa atribuicao não pode! \n";
						exit(1);
					}
					else if(aux->tipo == "cadeia" && $3.tipo == "cadeia")
					{
						if($2.rotulo == "+="){
							string auxTempTam = geraTemp();
							string tempTam = geraTemp();
							string opVar = geraTemp();
							sim2.rotulo = "operacao";
							sim2.temporaria = opVar;
							sim2.tipo = "cadeia";
							sim2.tipoTmp = "char *";
							sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
							declaracoes.append("\tint " + auxTempTam + ";\n");
							declaracoes.append("\tint " + tempTam + ";\n");
							declaracoes.append(sim2.declaracaoTmp);

							Cadeia s1, s2;

							buscaInfoCadeia(&s1, aux->temporaria);
							buscaInfoCadeia(&s2, $3.temporaria);

							if(s1.tempTam == ""){ //caso da inicialização onde não sei o tipo do operando
								string varTamAux = geraTemp();
								string varAux = geraTemp();

								sim4.rotulo = "auxiliarTam";
								sim4.temporaria = varTamAux;
								sim4.tipo = "int";
								sim4.tipoTmp = "int";
								sim4.declaracaoTmp = "\t" + sim4.tipoTmp + " " + sim4.temporaria + ";\n";
								declaracoes.append(sim4.declaracaoTmp);
								insereTabelaSimbolos((PilhaBlocos.back()), &sim4);

								string varTamAuxTraducao = "\t"+sim4.temporaria +" = 1;\n";
								//////////////////////////////////////////////////////////////////////
								sim4.rotulo = "auxiliar";
								sim4.temporaria = varAux;
								sim4.tipo = "cadeia";
								sim4.tipoTmp = "char *";
								sim4.declaracaoTmp = "\t" + sim4.tipoTmp + " " + sim4.temporaria + ";\n";
								declaracoes.append(sim4.declaracaoTmp);
								insereTabelaSimbolos((PilhaBlocos.back()), &sim4);

								string varAuxTraducao = varTamAuxTraducao + "\t"+sim4.temporaria + " = " + "(char *)malloc("+ varTamAux + "*sizeof(char));\n\t" + sim4.temporaria + " = "+"strcpy("+sim4.temporaria+", \"\");\n";

								sim2.traducao = varAuxTraducao + "\t" + auxTempTam + " = " + varTamAux + " + " + s2.tempTam + ";\n" + "\t" + tempTam + " = " + auxTempTam + " - 1;\n" +
								"\t" + sim2.temporaria + " = " + "(char *) malloc(" + tempTam + " * sizeof(char));\n" + "\t" + sim2.temporaria + " = strcat(" + varAux + ", " + $3.temporaria + ");\n";

							}else{
								sim2.traducao = "\t" + auxTempTam + " = " + s1.tempTam + " + " + s2.tempTam + ";\n" + "\t" + tempTam + " = " + auxTempTam + " - 1;\n" +
								"\t" + sim2.temporaria + " = " + "(char *) malloc(" + tempTam + " * sizeof(char));\n" + "\t" + sim2.temporaria + " = strcat(" + aux->temporaria + ", " + $3.temporaria + ");\n";
							}

							preencheSimbolo(&sim2, "composto", sim2.traducao, "none", sim2.temporaria, sim2.tipoTmp, sim2.tipoTmp, sim2.declaracaoTmp);
							$$.traducao = $3.traducao + sim2.traducao + "\n\t" + buffer + " = " + sim2.temporaria + ";\n\t";
						}
						else{
							cout << "Essa atribuicao não pode! \n";
							exit(1);
						}


					}
					else if(aux->tipoTmp == $3.tipoTmp && aux->tipo == $3.tipo){ //senão precisar de conversão
						string composto = geraTemp();
						//string traducao = "\t" + composto + " = " + "(" + aux->tipoTmp + ")" + $3.temporaria + ";\n";
						string traducao;
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + composto + ";\n";
						declaracoes.append(declaracaoTmp);
						if($2.rotulo == "+="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " + "+ $3.temporaria + ";\n";
							$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if($2.rotulo == "-="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " - "+ $3.temporaria + ";\n";
							$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if($2.rotulo == "*="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " * "+ $3.temporaria + ";\n";
							$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if($2.rotulo == "/="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " / "+ $3.temporaria + ";\n";
							$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if($2.rotulo == "%="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " % "+ $3.temporaria + ";\n";
							$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						preencheSimbolo(&sim, "composto", traducao, "none", composto, aux->tipoTmp, aux->tipoTmp, declaracaoTmp);

					}else if(aux->tipoTmp == "float" && $3.tipoTmp =="int" || aux->tipoTmp == "int" && $3.tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string composto = geraTemp();
						string traducao1 = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + $3.temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						string declaracaoComp = "\t" + aux->tipoTmp + " " + composto + ";\n";

						if($2.rotulo == "+="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " + "+ converteVar + ";\n";
							$$.traducao = $3.traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if($2.rotulo == "-="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " - "+ converteVar + ";\n";
							$$.traducao = $3.traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if($2.rotulo == "*="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " * "+ converteVar + ";\n";
							$$.traducao = $3.traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if($2.rotulo == "/="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " / "+ converteVar + ";\n";
							$$.traducao = $3.traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if($2.rotulo == "%="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " % "+ converteVar + ";\n";
							$$.traducao = $3.traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						declaracoes.append(declaracaoTmp);
						declaracoes.append(declaracaoComp);
						preencheSimbolo(&sim, "conversao", traducao1, "none", converteVar, aux->tipoTmp, aux->tipoTmp, declaracaoTmp);

						//$$.traducao = $3.traducao + traducao + "\t" + aux->temporaria + " = " + converteVar + ";\n";

					}
					else{
						cout << "Essa atribuicao não pode! \n";
						exit(1);
					}
				}

				$$.rotulo = "atribuicao";
				$$.conteudo = "none";
				$$.temporaria = aux->temporaria;
				$$.tipo = aux->temporaria;
				$$.tipoTmp = $$.tipo;
				$$.declaracaoTmp = aux->declaracaoTmp;
			}
			| TK_CONT ';'
 			{
 				string aux1;
 				if(PilhaLaco.empty())
 				{
 					cout << "continue aqui não pode.\n";
 					exit(1);
 				}
 				else if(PilhaLaco.back().continuar=="")
 				{
 					aux1 = geraBloco();
 					PilhaLaco.back().continuar ="\t" + aux1 + ":\n";
 					PilhaLaco.back().continuar2 =aux1;
 					$$.traducao = "\n\tgoto " + aux1 + ";\n";
 				}
 				else
 				{

 					$$.traducao = "\n\tgoto " + PilhaLaco.back().continuar2 + ";\n";

 				}
 			}
 			| TK_BREAK ';'
 			{
 				string aux1;
 				if(PilhaLaco.empty())
 				{
 					cout << "break aqui não pode.\n";
 					exit(1);
 				}
 				else if(PilhaLaco.back().quebrar=="")
 				{
 					aux1 = geraBloco();
 					PilhaLaco.back().quebrar = aux1;
 					$$.traducao = "\n\tgoto " + aux1 + ";\n";
 				}
 				else
 				{

 					$$.traducao = "\n\tgoto " + PilhaLaco.back().quebrar + ";\n";

 				}
 			}
 			//derivação de de condicionais
			|N TK_IF '(' G ')' BLOCO ELIF
 			{
				Simbolo sim;
 				string temporaria3	= geraTemp();
				string tipoTmp3 = "int";
				string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
				string atribuicao3 = "\t" + temporaria3 + " = " + "!" + $4.temporaria + ";\n";
				preencheSimbolo(&sim, "teste", atribuicao3, "none", temporaria3, "booleano", tipoTmp3, declaracaoTmp3);
				declaracoes.append(declaracaoTmp3);
 				string aux1, fim, aux3;
 				if(PilhaIf.back().fim == "")
 				{
 					fim = PilhaIf.back().fim;
 					aux3 = PilhaIf.back().fim;
 				}
 				else
 				{
 					fim = "goto " + PilhaIf.back().fim + ";";
 					aux3 = PilhaIf.back().fim + ":";
 				}
 				aux1 = geraBloco();
 				$$.traducao = $4.traducao + atribuicao3 + "\t" + $2.rotulo + "(" + temporaria3 + ") goto "+ aux1 + ";\n" + $6.traducao +"\t"+ fim +"\n\t"+ aux1 + ":\n" + $7.traducao +"\t"+aux3 +"\n";
 				desempilhaIf();
 			}
 			| Y
 			{
 				$$.traducao = $1.traducao;
 			}
			| BLOCO
			{
				$$.traducao = $1.traducao;
			}
			| TK_OUT ':' G ';'
			{
				$$.traducao = $3.traducao + "\tcout << " + $3.temporaria + " << endl;\n";
			}
			| TK_IN ':' G ';'
			{
				//7 variavéis, a primeira já tá em G
				if($3.tipoTmp == "char *"){
					Simbolo sim;
					string temporaria1	= geraTemp();
					string tipoTmp1 = "char *";
					string declaracaoTmp1 = "\tchar *" + temporaria1 + ";\n";
					string atribuicao1 = "\t" + temporaria1 + " = " + "(char*)malloc(sizeof(char));\n";
					preencheSimbolo(&sim, "char auxiliar", atribuicao1, "none", temporaria1, "letra", tipoTmp1, declaracaoTmp1);

					string temporaria2	= geraTemp();
					string tipoTmp2 = "int";
					string declaracaoTmp2 = "\tint " + temporaria2 + ";\n";
					string atribuicao2 = "\t" + temporaria2 + " = " + "1;\n";
					preencheSimbolo(&sim, "int tamanho", atribuicao2, "none", temporaria2, "int", tipoTmp2, declaracaoTmp2);

					string temporaria5	= geraTemp();
					string tipoTmp5 = "int";
					string declaracaoTmp5 = "\tint " + temporaria5 + ";\n";
					string atribuicao5 = "\t" + temporaria5 + " = " + "1;\n";
					preencheSimbolo(&sim, "incremento do tamanho", atribuicao5, "none", temporaria5, "int", tipoTmp5, declaracaoTmp5);

					string temporaria6	= geraTemp();
					string tipoTmp6 = "int";
					string declaracaoTmp6 = "\tint " + temporaria6 + ";\n";
					string atribuicao6 = "\t" + temporaria6 + " = " + "'\\n';\n";
					preencheSimbolo(&sim, "quebra de linha", atribuicao6, "none", temporaria6, "letra", tipoTmp6, declaracaoTmp6);

					string temporaria3	= geraTemp();
					string tipoTmp3 = "int";
					string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
					string atribuicao3 = "\t" + temporaria3 + " = " + "*" + temporaria1 + "!=" + temporaria6 + ";\n";
					preencheSimbolo(&sim, "booleano verificador da entrada", atribuicao3, "none", temporaria3, "booleano", tipoTmp3, declaracaoTmp3);

					string temporaria4	= geraTemp();
					string tipoTmp4 = "int";
					string declaracaoTmp4 = "\tint " + temporaria4 + ";\n";
					string atribuicao4 = "\t" + temporaria4 + " = " + "!" + temporaria3 + ";\n";
					preencheSimbolo(&sim, "negador do verificador", atribuicao4, "none", temporaria4, "booleano", tipoTmp4, declaracaoTmp4);

					declaracoes.append(declaracaoTmp1 + declaracaoTmp2 + declaracaoTmp3 + declaracaoTmp4 + declaracaoTmp5 + declaracaoTmp6);

					string blocoIni = geraBloco();
					string blocoFim = geraBloco();

					$$.traducao = "\t" + $3.temporaria + " = " + "NULL;\n" + atribuicao1 + atribuicao2 + atribuicao3 + atribuicao4 + atribuicao5 + atribuicao6;
					$$.traducao = $$.traducao + "\n\t" + blocoIni + ":\n" + "\tcin >> std::noskipws;\n\tcin >> *" + temporaria1 + ";\n";
					$$.traducao = $$.traducao + atribuicao3 + atribuicao4;
					$$.traducao = $$.traducao + "\tif(" + temporaria3 + ") goto " + blocoFim + ";\n";
					$$.traducao = $$.traducao + "\t" + $3.temporaria + " = " + "(char*)realloc(" + $3.temporaria + ", (" + temporaria2 + ")*sizeof(char));\n";
					$$.traducao = $$.traducao + "\t" + $3.temporaria + " = " + "strcat(" + $3.temporaria + ", "+ temporaria1 + ");\n";
					$$.traducao = $$.traducao + "\t" + temporaria2 + " = " + temporaria2 + " + " + temporaria5; + ";\n";
					$$.traducao = $$.traducao + "\n\tgoto " + blocoIni + ";\n\t" + blocoFim + ":\n";
					$$.traducao = $$.traducao + "\t" + $3.temporaria + " = " + "(char*)realloc(" + $3.temporaria + ", (" + temporaria2 + ")*sizeof(char));\n";
					$$.traducao = $$.traducao + "\t" + $3.temporaria + " = " + "strcat(" + $3.temporaria + ", '\\0');\n";
					$$.traducao = $$.traducao + "\tcin >> std::skipws;\n";

					Simbolo aux, aux2;
					Cadeia s;
					s.nomeVar = $3.rotulo;
					s.tempTam = temporaria2;
					s.tempNome = $3.temporaria;

					preencheSimbolo(&aux, "tam cadeia", s.tempTam + " = " , "?", s.tempTam, "int", "int", "int " + s.tempTam + ";");

					insereTabelaCadeias(s);
				}
				else{
					$$.traducao = $3.traducao + "\tcin >> " + $3.temporaria +";\n";
				}
			}
			;

//derivação dos blocos de repetição
Y 			: Z TK_WHILE '(' G ')' BLOCO
 			{
				Simbolo sim;
 				string temporaria3	= geraTemp();
				string tipoTmp3 = "int";
				string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
				string atribuicao3 = "\t" + temporaria3 + " = " + "!" + $4.temporaria + ";\n";
				preencheSimbolo(&sim, "teste", atribuicao3, "none", temporaria3, "booleano", tipoTmp3, declaracaoTmp3);
				declaracoes.append(declaracaoTmp3);

 				string aux1, aux2, aux3;
 				aux1 = geraBloco();
 				if(PilhaLaco.back().continuar!= "")
 				{
 					aux3 = PilhaLaco.back().continuar2;
 				}
 				else{
 					aux3 = geraBloco();
 				}
 				if(PilhaLaco.back().quebrar!= "")
 				{
 					aux2 = PilhaLaco.back().quebrar;
 				}
 				else{
 					aux2 = geraBloco();
 				}
				$$.traducao = "\t"+ aux3 +":\n"+ $4.traducao + atribuicao3 + "\tif(" + temporaria3 + ") goto "+ aux2 + ":\n\t \n"+ $6.traducao + "\n\tgoto " + aux3 +";\n\t"+ aux2 + ":\n";
 				// $$.traducao = "\n\t" + aux3 +":\n"+ $3.traducao + "\tif(" + $3.temporaria + ") goto "+ aux1 + ";\n\tgoto " + aux2 + ";\n\t" + aux1 +":"+ $5.traducao + "\n\tgoto " + aux3 +";\n\t"+ aux2 + ":\n";
 				//$$.traducao = "\n\t" + aux3 +":\n"+ $2.traducao + "\tif(" + $2.temporaria + ") goto "+ aux1 + ";\n\tgoto " + aux2 + ";\n\t" + aux1 +":"+ $4.traducao + "\n\tgoto " + aux3 +";\n\t"+ aux2 + ":\n";
 				desempilhaLaco();
 			}
 			| Z TK_DO BLOCO TK_WHILE '(' G ')'
 			{
 				string aux1, aux2, aux3;
 				aux1 = geraBloco();
 				aux2 = PilhaLaco.back().continuar ;

 				if(PilhaLaco.back().quebrar!= "")
 				{
 					aux3 = "\t"+ PilhaLaco.back().quebrar + ":";
 				}
 				else{
 					aux3 = PilhaLaco.back().quebrar;
 				}
 				$$.traducao = "\n\t" + aux1 +":\n"+ $3.traducao + $6.traducao + aux2 + "\n\tif(" + $6.temporaria + ") goto "+ aux1 +";\n"+ aux3 +"\n";
 				desempilhaLaco();

 			}
 			| Z TK_FOR '(' DECLARACAO ';' G ';' DECLARACAO ')' BLOCO
 			{
 				Simbolo sim;
 				string aux1, aux2, aux3, aux4;
 				aux1 = geraBloco();
 				aux3 = geraBloco();

 				string temporaria3	= geraTemp();
				string tipoTmp3 = "int";
				string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
				string atribuicao3 = "\t" + temporaria3 + " = " + "!" + $6.temporaria + ";\n";
				preencheSimbolo(&sim, "teste", atribuicao3, "none", temporaria3, "booleano", tipoTmp3, declaracaoTmp3);
				declaracoes.append(declaracaoTmp3);

 				if(PilhaLaco.back().quebrar!= "")
 				{
 					aux2 = PilhaLaco.back().quebrar;
 				}
 				else{
 					aux2 = geraBloco();
 				}
 				aux4 = PilhaLaco.back().continuar ;
 				$$.traducao = $4.traducao + "\n\t" + aux3 +":\n"+ $6.traducao + atribuicao3 +"\tif(" + temporaria3 + ") goto "+ aux2 + ";\n\t\n"+ $10.traducao + aux4 + $8.traducao +"\n\tgoto " + aux3 +";\n\t"+ aux2 + ":\n";
 				desempilhaLaco();
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
					declaracoes.append(declaracaoTmp);
					preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, "int", "int", declaracaoTmp);
					sim2.tipo = "int";
					sim2.tipoTmp = "int";

				}else if($1.rotulo == "flutua"){
					traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
					declaracaoTmp = "\tfloat " + converteVar + ";\n";
					declaracoes.append(declaracaoTmp);
					preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, "real", "float", declaracaoTmp);
					sim2.tipo = "real";
					sim2.tipoTmp = "float";

				}
				$$.traducao = $3.traducao + traducao;

				string opVar = geraTemp();
				sim2.rotulo = "operacao";
				sim2.temporaria = opVar;

				sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
				declaracoes.append(sim2.declaracaoTmp);
				sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + ";\n";

				insereTabelaSimbolos((PilhaBlocos.back()), &sim2);

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
					declaracoes.append("\tint " + $$.temporaria + ";\n");
					string traducao = "\t" + $$.temporaria + " = " + $1.temporaria + " " + op + " " + $3.temporaria + ";\n";
					preencheSimbolo(&sim, "operacao", traducao, "none", $$.temporaria, "booleano", "int", $$.declaracaoTmp);

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

				if($1.tipoTmp == "" || $3.tipoTmp == ""){ //caso da inicialização onde não sei o tipo do operando
					if($3.tipoTmp == "int"){
						string opVar = geraTemp();
						string varAux = geraTemp();
						sim2.rotulo = "auxiliar";
						sim2.temporaria = varAux;
						sim2.tipo = "int";
						sim2.tipoTmp = "int";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);
						insereTabelaSimbolos((PilhaBlocos.back()), &sim2);
						////////////////////////////////////////////////////////////////////////
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;
						sim2.tipo = "int";
						sim2.tipoTmp = "int";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);

						sim2.traducao = "\t" + varAux + " = 0;\n" + "\t" + sim2.temporaria + " = " + varAux + $2.rotulo + $3.temporaria + ";\n";
					}else if($3.tipoTmp == "float"){
						string opVar = geraTemp();
						string varAux = geraTemp();
						sim2.rotulo = "auxiliar";
						sim2.temporaria = varAux;
						sim2.tipo = "real";
						sim2.tipoTmp = "float";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);
						insereTabelaSimbolos((PilhaBlocos.back()), &sim2);
						////////////////////////////////////////////////////////////////////////
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;
						sim2.tipo = "real";
						sim2.tipoTmp = "float";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);

						sim2.traducao = "\t" + varAux + " = 0.0;\n" + "\t" + sim2.temporaria + " = " + varAux + $2.rotulo + $3.temporaria + ";\n";
					}
				}else{

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
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, $1.tipoTmp, $1.tipoTmp, declaracaoTmp);

						}else if($3.tipoTmp == "float"){

							traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
							declaracaoTmp = "\t" + $3.tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, $3.tipoTmp, $3.tipoTmp, declaracaoTmp);
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
					declaracoes.append(sim2.declaracaoTmp);
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
				}
				insereTabelaSimbolos((PilhaBlocos.back()), &sim2);

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
				$$.verificadorInicializacao = $1.verificadorInicializacao;
			}
			;

E 			: E TK_SUM_SUB T //soma ou subtração
			{
				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteuOp2 = false; //var aux para saber qual operando foi convertido, nesse caso ela aciona na conversão do 2º operando
				string converteVar = "none";
				$$.traducao = $1.traducao + $3.traducao;

				if($1.tipoTmp == "" || $3.tipoTmp == ""){ //caso da inicialização onde não sei o tipo do operando
					if($3.tipoTmp == "int"){
						string opVar = geraTemp();
						string varAux = geraTemp();
						sim2.rotulo = "auxiliar";
						sim2.temporaria = varAux;
						sim2.tipo = "int";
						sim2.tipoTmp = "int";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);
						insereTabelaSimbolos((PilhaBlocos.back()), &sim2);
						////////////////////////////////////////////////////////////////////////
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;
						sim2.tipo = "int";
						sim2.tipoTmp = "int";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);

						sim2.traducao = "\t" + varAux + " = 0;\n" + "\t" + sim2.temporaria + " = " + varAux + $2.rotulo + $3.temporaria + ";\n";
					}else if($3.tipoTmp == "float"){
						string opVar = geraTemp();
						string varAux = geraTemp();
						sim2.rotulo = "auxiliar";
						sim2.temporaria = varAux;
						sim2.tipo = "real";
						sim2.tipoTmp = "float";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);
						insereTabelaSimbolos((PilhaBlocos.back()), &sim2);
						////////////////////////////////////////////////////////////////////////
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;
						sim2.tipo = "real";
						sim2.tipoTmp = "float";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);

						sim2.traducao = "\t" + varAux + " = 0.0;\n" + "\t" + sim2.temporaria + " = " + varAux + $2.rotulo + $3.temporaria + ";\n";
					}else if($3.tipoTmp == "char *"){
						string opVar = geraTemp();
						string varAux = geraTemp();
						sim2.rotulo = "auxiliar";
						sim2.temporaria = varAux;
						sim2.tipo = "cadeia";
						sim2.tipoTmp = "char *";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);
						insereTabelaSimbolos((PilhaBlocos.back()), &sim2);
						////////////////////////////////////////////////////////////////////////
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;
						sim2.tipo = "cadeia";
						sim2.tipoTmp = "char *";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);

						sim2.traducao = "\t" + varAux + " = (char*)malloc(sizeof(char));\n" + "\t" + varAux + " = strcpy(" + varAux + ",\"\");\n" + "\t" + sim2.temporaria + " = " + varAux + $2.rotulo + $3.temporaria + ";\n";
					}

				}else{

					if($1.tipoTmp != $3.tipoTmp){ //conversão, falta fazer a conversão dos outros tipos pra string, quando um dos tipos for string e o outro não
						converteu = true;			// pergunta: faremos essa conversão implícita, ou só permitiremos a explícita : palavreando()?
						converteVar = geraTemp();
						string traducao, declaracaoTmp;
						if($1.tipoTmp == "float"){
							converteuOp2 = true;
							traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
							declaracaoTmp = "\t" + $1.tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, $1.tipoTmp, $1.tipoTmp, declaracaoTmp);

						}else if($3.tipoTmp == "float"){

							traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
							declaracaoTmp = "\t" + $3.tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, $3.tipoTmp, $3.tipoTmp, declaracaoTmp);
						}

						$$.traducao = $$.traducao + traducao;
					}

					if($1.tipo == "cadeia" && $3.tipo == "cadeia"){
						string auxTempTam = geraTemp();
						string tempTam = geraTemp();
						string opVar = geraTemp();
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;
						sim2.tipo = "cadeia";
						sim2.tipoTmp = "char *";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append("\tint " + auxTempTam + ";\n");
						declaracoes.append("\tint " + tempTam + ";\n");
						declaracoes.append(sim2.declaracaoTmp);

						Cadeia s1, s2;

						buscaInfoCadeia(&s1, $1.temporaria);
						buscaInfoCadeia(&s2, $3.temporaria);

						sim2.traducao = "\t" + auxTempTam + " = " + s1.tempTam + " + " + s2.tempTam + ";\n" + "\t" + tempTam + " = " + auxTempTam + " - 1;\n" +
						"\t" + sim2.temporaria + " = " + "(char *) malloc(" + tempTam + " * sizeof(char));\n" + "\t" + sim2.temporaria + " = strcat(" + $1.temporaria + ", " + $3.temporaria + ");\n";
					}else{
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
						declaracoes.append(sim2.declaracaoTmp);
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
					}

				}

				insereTabelaSimbolos((PilhaBlocos.back()), &sim2);

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
				$$.verificadorInicializacao = $1.verificadorInicializacao;
			}
			;

T 			: T TK_MUL_DIV F //multiplicação ou divisão
			{
				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteuOp2 = false; //var aux para saber qual operando foi convertido, nesse caso ela aciona na conversão do 2º operando
				string converteVar = "none";
				$$.traducao = $1.traducao + $3.traducao;

				if($1.tipoTmp == "" || $3.tipoTmp == ""){ //caso da inicialização onde não sei o tipo do operando
					if($3.tipoTmp == "int"){
						string opVar = geraTemp();
						string varAux = geraTemp();
						sim2.rotulo = "auxiliar";
						sim2.temporaria = varAux;
						sim2.tipo = "int";
						sim2.tipoTmp = "int";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);
						insereTabelaSimbolos((PilhaBlocos.back()), &sim2);
						////////////////////////////////////////////////////////////////////////
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;
						sim2.tipo = "int";
						sim2.tipoTmp = "int";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);

						sim2.traducao = "\t" + varAux + " = 0;\n" + "\t" + sim2.temporaria + " = " + varAux + $2.rotulo + $3.temporaria + ";\n";
					}else if($3.tipoTmp == "float"){
						string opVar = geraTemp();
						string varAux = geraTemp();
						sim2.rotulo = "auxiliar";
						sim2.temporaria = varAux;
						sim2.tipo = "real";
						sim2.tipoTmp = "float";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);
						insereTabelaSimbolos((PilhaBlocos.back()), &sim2);
						////////////////////////////////////////////////////////////////////////
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;
						sim2.tipo = "real";
						sim2.tipoTmp = "float";
						sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
						declaracoes.append(sim2.declaracaoTmp);

						sim2.traducao = "\t" + varAux + " = 0.0;\n" + "\t" + sim2.temporaria + " = " + varAux + $2.rotulo + $3.temporaria + ";\n";
					}
				}else{
					if($1.tipoTmp != $3.tipoTmp){ //conversão
						converteu = true;
						converteVar = geraTemp();
						string traducao, declaracaoTmp;
						if($1.tipoTmp == "float"){
							converteuOp2 = true;
							traducao = "\t" + converteVar + " = " + "(float)" + $3.temporaria + ";\n";
							declaracaoTmp = "\t" + $1.tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, $1.tipoTmp, $1.tipoTmp, declaracaoTmp);

						}else if($3.tipoTmp == "float"){

							traducao = "\t" + converteVar + " = " + "(float)" + $1.temporaria + ";\n";
							declaracaoTmp = "\t" + $3.tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, $3.tipoTmp, $3.tipoTmp, declaracaoTmp);
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
					declaracoes.append(sim2.declaracaoTmp);
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
				}

				insereTabelaSimbolos((PilhaBlocos.back()), &sim2);

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
				$$.verificadorInicializacao = $1.verificadorInicializacao;
			}
			;

F 			: '(' E ')'
			{
				$$.rotulo = $2.rotulo;
				$$.traducao = $2.traducao;
				$$.conteudo = $2.conteudo;
				$$.temporaria = $2.temporaria;
				$$.tipo = $2.tipo;
				$$.tipoTmp = $2.tipoTmp;
				$$.declaracaoTmp = $2.declaracaoTmp;
			}
			| TK_NUM //inteiros
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
					$$.tempLinhas = aux->tempLinhas;
					$$.tempColunas = aux->tempColunas;
				}else{ //não confirmo que não foi declarada ainda, dou uma chance
					VariaveisPossiveis.push_back($1.rotulo);
					$$.rotulo = $1.rotulo;
					$$.traducao = "";
					$$.conteudo = "";
					$$.temporaria = "";
					$$.tipo = "";
					$$.tipoTmp = "";
					$$.declaracaoTmp = "";
					$$.verificadorInicializacao = 1;
					//yyerror("Identificador sem pai! D:"); esse cara vai lá pro bloco!!!
				}
			}
			| TK_CADEIA
			{
				Cadeia s;
				Simbolo aux, sim;
				s.nomeVar = "none";
				s.tam = $1.traducao.length() - 1;
				s.tempTam = geraTemp();
				s.tempNome = geraTemp();

				declaracoes.append("\tint " + s.tempTam + ";\n");

				preencheSimbolo(&aux, "tam cadeia", s.tempTam + " = " + to_string(s.tam), to_string(s.tam), s.tempTam, "int", "int", "int " + s.tempTam + ";");

				subirInfoString(&$$, sim, "cadeia", $1.traducao, s.tempNome, "cadeia", "char *", s.tempTam, to_string(s.tam));

				insereTabelaCadeias(s);

				/*
					int temp_tamanho_string = 0;
					char * temp;
					temp = (char*) malloc(temp_tamanho_string*sizeof(char));
				*/
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
	cout << "Linha " + to_string(num_linhas) + ": " << MSG << endl;
	exit (0);
}
