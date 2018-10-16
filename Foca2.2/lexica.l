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
BOOL "true"|"false"

%%

"\n"		{}

{DELIM} 	{}

"main"		{return TK_MAIN;}

"int"|"real"|"letra"|"booleano"		{yylval.rotulo = yytext; return TK_TIPO;}

"flutua"|"inteirao"	{ yylval.rotulo = yytext; return TK_CONVERTE;}

[(){}[\];,]	{ return *yytext; }

[=]			{ return *yytext; }

[+\-]		{ yylval.rotulo = yytext; return TK_SUM_SUB;}
[*/]		{ yylval.rotulo = yytext; return TK_MUL_DIV;}

">"			{yylval.rotulo = yytext; return TK_REL;}
"<"			{yylval.rotulo = yytext; return TK_REL;}
"=="		{yylval.rotulo = yytext; return TK_REL;}
"!="		{yylval.rotulo = yytext; return TK_REL;}
">="		{yylval.rotulo = yytext; return TK_REL;}
"<="		{yylval.rotulo = yytext; return TK_REL;}

"ou"		{yylval.rotulo = yytext; return TK_LOG;}
"e"			{yylval.rotulo = yytext; return TK_LOG;}

{BOOL}		{ yylval.traducao = yytext; return TK_BOOLEAN; }
{NUM}		{ yylval.traducao = yytext; return TK_NUM; }
{REAL}		{ yylval.traducao = yytext; return TK_REAL; }
{CHAR}		{ yylval.traducao = yytext; return TK_CHAR;}
{ID}		{ yylval.rotulo = yytext; return TK_ID; }

.			{ *yytext; }

%%