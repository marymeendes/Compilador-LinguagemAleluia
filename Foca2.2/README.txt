Esta versão marca oque seria o fim da Spring 1 ao nosso parecer. Após resolvermos refazer todo o código do quase zero. hahahahaha
Para a Spring 1 nosso compilador devia contemplar: 

Entrega I -> 21/09 -> 04/10

.Tipos:
	int
	float
	char
	bool

.Expressões

.Conversão
	implícita
	explícita

.Operadores
	aritméticos (+, -, *, /) opcional (++, --)
	lógicos (||, &&)
	relacionais (<, >, <=, >=, ==, !=)

*operadores relacionais e lógicos: saída deve, obrigatoriamente, ser booleano para o CLIENTE!!!
Ex.: (1<2)+1 tem que ser inválido!!!
No código intermediário, que é em C, o boolean é inteiro (0 ou 1), mas para o cliente não!

.Variáveis

.Atribuição

Exemplos:

float x
x = 1 (conversão implícita)

bool x
x = true || false

int x
x = (float)1 (conversão explícita)

bool x
x = 1 < 2

float x
x = 0
x = x+1

Nessa sprint, variável sem declaração de tipo tem que dar erro.

