%{
#include <string>

%}

ESPACO [ \t]
DIGITO [0-9]
DIGITOSZ [1-9]
LETRA [A-Za-z_]

DELIM {ESPACO}+
NUM 0|({DIGITOSZ}{DIGITO}*)
REAL {NUM}+("."{NUM}+)?
CHAR \'({LETRA}|{NUM})\'
ID {LETRA}({LETRA}|{NUM})*
BOOL "verdadeiro"|"falso"
CADEIA \"(\\.|[^"\\])*\"

%%

"\n"		{ num_linhas++; }

{DELIM} 	{}

"principal"	{ yylval.rotulo = yytext; return TK_MAIN;}

"ler"		{ yylval.rotulo = yytext; return TK_IN; }

"escrever"	{ yylval.rotulo = yytext; return TK_OUT; }

"seleciona"	{ yylval.rotulo = yytext; return TK_SWITCH; }

"caso"		{ yylval.rotulo = yytext; return TK_OP_SWITCH; }

"int"|"real"|"letra"|"booleano"|"cadeia"	{yylval.rotulo = yytext; return TK_TIPO;}

"flutua"|"inteirao"	{ yylval.rotulo = yytext; return TK_CONVERTE;}

[(){}[\];,]	{ return *yytext; }

[=:]		{ return *yytext; }

[+\-]		{ yylval.rotulo = yytext; return TK_SUM_SUB;}
[*/]		{ yylval.rotulo = yytext; return TK_MUL_DIV;}

">"			{yylval.rotulo = yytext; return TK_REL;}
"<"			{yylval.rotulo = yytext; return TK_REL;}
"=="		{yylval.rotulo = yytext; return TK_REL;}
"!="		{yylval.rotulo = yytext; return TK_REL;}
">="		{yylval.rotulo = yytext; return TK_REL;}
"<="		{yylval.rotulo = yytext; return TK_REL;}

"+="		{yylval.rotulo = yytext; return TK_COMP;}
"-="		{yylval.rotulo = yytext; return TK_COMP;}
"*="		{yylval.rotulo = yytext; return TK_COMP;}
"/="		{yylval.rotulo = yytext; return TK_COMP;}
"%="		{yylval.rotulo = yytext; return TK_COMP;}

"++"		{yylval.rotulo = yytext; return TK_UNA;}
"--"		{yylval.rotulo = yytext; return TK_UNA;}

"if"		{yylval.rotulo = yytext; return TK_IF;}
"elif"		{yylval.rotulo = yytext; return TK_ELIF;}
"else"		{yylval.rotulo = yytext; return TK_ELSE;}
"while"		{yylval.rotulo = yytext; return TK_WHILE;}
"for"		{yylval.rotulo = yytext; return TK_FOR;}
"do"		{yylval.rotulo = yytext; return TK_DO;}
"continue"	{yylval.rotulo = yytext; return TK_CONT;}
"break"		{yylval.rotulo = yytext; return TK_BREAK;}

"ou"		{yylval.rotulo = yytext; return TK_LOG;}
"e"			{yylval.rotulo = yytext; return TK_LOG;}

{BOOL}		{ yylval.traducao = yytext; return TK_BOOLEAN; }
{NUM}		{ yylval.traducao = yytext; return TK_NUM; }
{REAL}		{ yylval.traducao = yytext; return TK_REAL; }
{CHAR}		{ yylval.traducao = yytext; return TK_CHAR;}
{ID}		{ yylval.rotulo = yytext; return TK_ID; }

{CADEIA}	{ yylval.traducao = yytext; return TK_CADEIA; }

.			{ *yytext; }

%%
