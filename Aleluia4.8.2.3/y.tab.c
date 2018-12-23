/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 9 "sintatica.y" /* yacc.c:339  */

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


#line 314 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_TIPO = 258,
    TK_MAIN = 259,
    TK_ID = 260,
    TK_FIM = 261,
    TK_ERROR = 262,
    TK_CONVERTE = 263,
    TK_SUM_SUB = 264,
    TK_MUL_DIV = 265,
    TK_REL = 266,
    TK_LOG = 267,
    TK_BOOLEAN = 268,
    TK_NUM = 269,
    TK_REAL = 270,
    TK_CHAR = 271,
    TK_CADEIA = 272,
    TK_IF = 273,
    TK_ELIF = 274,
    TK_ELSE = 275,
    TK_WHILE = 276,
    TK_FOR = 277,
    TK_DO = 278,
    TK_SWITCH = 279,
    TK_OP_SWITCH = 280,
    TK_CONT = 281,
    TK_BREAK = 282,
    TK_OUT = 283,
    TK_IN = 284,
    TK_COMP = 285,
    TK_UNA = 286,
    LE = 287,
    GE = 288,
    EQ = 289,
    NE = 290
  };
#endif
/* Tokens.  */
#define TK_TIPO 258
#define TK_MAIN 259
#define TK_ID 260
#define TK_FIM 261
#define TK_ERROR 262
#define TK_CONVERTE 263
#define TK_SUM_SUB 264
#define TK_MUL_DIV 265
#define TK_REL 266
#define TK_LOG 267
#define TK_BOOLEAN 268
#define TK_NUM 269
#define TK_REAL 270
#define TK_CHAR 271
#define TK_CADEIA 272
#define TK_IF 273
#define TK_ELIF 274
#define TK_ELSE 275
#define TK_WHILE 276
#define TK_FOR 277
#define TK_DO 278
#define TK_SWITCH 279
#define TK_OP_SWITCH 280
#define TK_CONT 281
#define TK_BREAK 282
#define TK_OUT 283
#define TK_IN 284
#define TK_COMP 285
#define TK_UNA 286
#define LE 287
#define GE 288
#define EQ 289
#define NE 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 435 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      39,    40,     2,     2,    45,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    38,
      32,    43,    33,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    34,    35,    36,
      37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   278,   278,   283,   311,   318,   336,   368,   373,   378,
     427,   434,   444,   452,   457,   462,   473,   505,   570,   596,
     640,   702,   748,   904,   926,   948,   972,   976,   980,   984,
    1059,  1090,  1107,  1134,  1185,  1212,  1326,  1339,  1489,  1502,
    1607,  1620,  1630,  1635,  1640,  1645,  1655,  1681
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_TIPO", "TK_MAIN", "TK_ID", "TK_FIM",
  "TK_ERROR", "TK_CONVERTE", "TK_SUM_SUB", "TK_MUL_DIV", "TK_REL",
  "TK_LOG", "TK_BOOLEAN", "TK_NUM", "TK_REAL", "TK_CHAR", "TK_CADEIA",
  "TK_IF", "TK_ELIF", "TK_ELSE", "TK_WHILE", "TK_FOR", "TK_DO",
  "TK_SWITCH", "TK_OP_SWITCH", "TK_CONT", "TK_BREAK", "TK_OUT", "TK_IN",
  "TK_COMP", "TK_UNA", "'<'", "'>'", "LE", "GE", "EQ", "NE", "';'", "'('",
  "')'", "'{'", "'}'", "'='", "'['", "','", "']'", "':'", "$accept", "S",
  "A", "BLOCO", "ELIF", "DECLARACAO", "X", "Z", "N", "COMANDOS", "COMANDO",
  "Y", "G", "E", "T", "F", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    60,    62,   287,   288,   289,   290,    59,    40,
      41,   123,   125,    61,    91,    44,    93,    58
};
# endif

#define YYPACT_NINF -38

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-38)))

#define YYTABLE_NINF -15

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      52,    -1,   -33,    16,   -38,   -26,   -22,   -38,    52,   -38,
     -38,   -38,   -20,    12,    18,    89,    -4,   -38,   -38,   -38,
     -38,   -38,     6,    14,    10,    42,    68,   -38,   115,    82,
      60,    12,   -38,    20,   121,    96,   -38,    85,    62,    72,
      62,    68,    62,   -38,   -38,    62,    62,   -38,    -7,    95,
     103,   -38,   104,   -38,   -38,    68,    62,   -38,    68,    68,
     -38,    62,    68,    34,   -38,    84,     4,    51,    87,    93,
     -38,    62,   110,   124,    62,   121,   113,    96,   -38,    97,
       5,   -38,   -38,    68,   -38,   -38,   -38,    54,   105,   108,
     111,    57,   -38,    68,     1,   -38,    62,    62,    62,   -38,
       2,   109,   -38,   129,   101,    76,   107,   116,    62,   110,
     -38,   112,   -38,   -38,   -38,   106,   117,    62,   -38,   -38,
     -38,    81,   -38,   -38,   107,   -38
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     0,     1,     0,    10,
       3,     4,     0,    11,     0,    46,     0,    45,    42,    43,
      44,    47,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    11,    26,     0,    36,    38,    40,     0,     0,     0,
       0,     0,     0,    23,    24,     0,     0,    46,     0,     0,
       0,    10,     0,     5,    13,     0,     0,    15,     0,     0,
      18,     0,     0,     0,    21,     0,     0,     0,     0,     0,
      41,     0,     0,     0,     0,    35,    34,    37,    39,     0,
       0,    22,    19,     0,    33,    28,    29,     0,     0,     0,
       0,     0,    20,     0,     0,    10,     0,     0,     0,    10,
       0,     0,    30,     9,     0,     0,     8,     0,     0,     0,
      31,     0,    10,    25,    16,     0,     0,     0,     7,    17,
      10,     0,    32,    10,     8,     6
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -38,   -38,   139,    -9,    25,    44,   -38,   -38,   -38,   125,
     -38,   -38,   -37,   -19,   100,   102
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,    27,   113,    89,    12,    28,    29,    30,
      31,    32,    33,    34,    35,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      11,    63,    58,    65,     5,    67,     6,    48,    68,    69,
      58,    58,     8,    58,    58,    14,     7,    15,     9,    76,
      16,    13,    66,    37,    79,    17,    18,    19,    20,    21,
     -12,    55,    56,    70,    87,    42,    75,    91,    22,    23,
      24,    25,    73,    80,    43,    55,    56,   101,   107,    83,
      93,    26,    44,   -10,   -14,     1,     2,    45,    57,   103,
     104,   105,    55,    56,    94,    55,    56,    47,    55,    56,
      16,   115,    81,    47,   100,    17,    18,    19,    20,    21,
     121,    17,    18,    19,    20,    21,   102,    55,    56,    46,
     106,    84,    55,    56,    95,    55,    56,    99,    55,    56,
      52,    26,    53,   118,    55,    56,    59,    26,    55,    56,
      64,   122,    55,    56,   124,    88,   110,    55,    56,    38,
      39,   123,    82,    60,    55,    85,   111,   112,    61,    62,
      58,    86,    40,    41,    71,    92,    49,    50,    51,   109,
      55,    56,    72,    74,   119,    90,    97,    10,    96,   125,
      98,   117,   108,   116,   114,     0,    54,   120,    77,     0,
       0,    78
};

static const yytype_int8 yycheck[] =
{
       9,    38,     9,    40,     5,    42,    39,    26,    45,    46,
       9,     9,    38,     9,     9,     3,     0,     5,    40,    56,
       8,    41,    41,     5,    61,    13,    14,    15,    16,    17,
      18,    11,    12,    40,    71,    39,    55,    74,    26,    27,
      28,    29,    51,    62,    38,    11,    12,    46,    46,    45,
      45,    39,    38,    41,    42,     3,     4,    47,    38,    96,
      97,    98,    11,    12,    83,    11,    12,     5,    11,    12,
       8,   108,    38,     5,    93,    13,    14,    15,    16,    17,
     117,    13,    14,    15,    16,    17,    95,    11,    12,    47,
      99,    40,    11,    12,    40,    11,    12,    40,    11,    12,
      18,    39,    42,   112,    11,    12,    10,    39,    11,    12,
      38,   120,    11,    12,   123,     5,    40,    11,    12,    30,
      31,    40,    38,    38,    11,    38,    19,    20,    43,    44,
       9,    38,    43,    44,    39,    38,    21,    22,    23,    38,
      11,    12,    39,    39,    38,    21,    38,     8,    43,   124,
      39,    39,    43,   109,    38,    -1,    31,    40,    58,    -1,
      -1,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    49,    50,     5,    39,     0,    38,    40,
      50,    51,    54,    41,     3,     5,     8,    13,    14,    15,
      16,    17,    26,    27,    28,    29,    39,    51,    55,    56,
      57,    58,    59,    60,    61,    62,    63,     5,    30,    31,
      43,    44,    39,    38,    38,    47,    47,     5,    61,    21,
      22,    23,    18,    42,    57,    11,    12,    38,     9,    10,
      38,    43,    44,    60,    38,    60,    61,    60,    60,    60,
      40,    39,    39,    51,    39,    61,    60,    62,    63,    60,
      61,    38,    38,    45,    40,    38,    38,    60,     5,    53,
      21,    60,    38,    45,    61,    40,    43,    38,    39,    40,
      61,    46,    51,    60,    60,    60,    51,    46,    43,    38,
      40,    19,    20,    52,    38,    60,    53,    39,    51,    38,
      40,    60,    51,    40,    51,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    52,    52,    52,    53,
      54,    55,    56,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    59,    59,    60,    60,    60,    60,    61,    61,    62,
      62,    63,    63,    63,    63,    63,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     4,     4,     4,     6,     2,     0,     3,
       0,     0,     0,     2,     0,     2,     8,     9,     3,     4,
       5,     3,     4,     2,     2,     7,     1,     1,     4,     4,
       6,     7,    10,     4,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 279 "sintatica.y" /* yacc.c:1646  */
    {
				cout << "\n" + apresentacao << "\n" + declaracoesGlobais + "\n" << inicio << endl;
			}
#line 1599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 284 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo *aux, sim;

				if((aux = buscaVetorGlobais((yyvsp[-2]).rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string temporaria = geraTemp();
					if((yyvsp[-3]).rotulo == "int" || (yyvsp[-3]).rotulo == "booleano")
						tipoTmp = "int";
					else if((yyvsp[-3]).rotulo == "real")
						tipoTmp = "float";
					else if((yyvsp[-3]).rotulo == "letra")
						tipoTmp = "char";
					else if((yyvsp[-3]).rotulo == "cadeia")
						tipoTmp = "char *";

					declaracaoTmp = tipoTmp + " " + temporaria + ";\n";

					preencheGlobal(sim, (yyvsp[-2]).rotulo, "", "none", temporaria, (yyvsp[-3]).rotulo, tipoTmp, declaracaoTmp);

					declaracoesGlobais.append(declaracaoTmp);

				}else{
					cout << "Variável global " + (yyvsp[-2]).rotulo + " já foi declarada antes!";
					exit(1);
				}
			}
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 312 "sintatica.y" /* yacc.c:1646  */
    {
				apresentacao.append("/*Compilador ALELUIA*/\n#include <iostream>\n#include <string.h>\n#include <stdio.h>\n#include <stdlib.h>\n\nusing namespace std;\n");
				inicio.append("int main(void)\n{\n" + declaracoes + "\n" + (yyvsp[0]).traducao + "\treturn 0;\n}");
			}
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 319 "sintatica.y" /* yacc.c:1646  */
    {
				//processo de fechamento do bloco é aqui
				//cout << "estive aqui no fechamento.";
				(yyval).traducao = (yyvsp[-1]).traducao;
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
#line 1660 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 337 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim;
 				string temporaria3	= geraTemp();
				string tipoTmp3 = "int";
				string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
				string atribuicao3 = "\t" + temporaria3 + " = " + "!" + (yyvsp[-3]).temporaria + ";\n";
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
 				(yyval).traducao = (yyvsp[-3]).traducao + atribuicao3 + "\tif(" + temporaria3 + ") goto "+ aux1 + ";\n" + (yyvsp[-1]).traducao +"\t"+ fim +"\n\t"+ aux1 + ":\n" + (yyvsp[0]).traducao + "\n";
 				//cout << "entrei no if.\n";

 			}
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 369 "sintatica.y" /* yacc.c:1646  */
    {
 				(yyval).traducao = (yyvsp[0]).traducao;
 			}
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 373 "sintatica.y" /* yacc.c:1646  */
    {
 				(yyval).traducao = "";
 			}
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 379 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo *aux, sim;
				if((aux = buscaPilhaBlocos((yyvsp[-2]).rotulo)) != NULL){
					if(aux->tipoTmp == (yyvsp[0]).tipoTmp && aux->tipo == (yyvsp[0]).tipo){ //senão precisar de conversão
						(yyval).traducao = (yyvsp[0]).traducao + "\t" + aux->temporaria + " = " + (yyvsp[0]).temporaria + ";\n";

						if((yyvsp[0]).tipo == "cadeia"){
						  	Cadeia cad;
						  	buscaInfoCadeia(&cad, (yyvsp[0]).temporaria);
						  	cad.tempNome = aux->temporaria;
						  	insereTabelaCadeias(cad);
						}

					}else if(aux->tipoTmp == "float" && (yyvsp[0]).tipoTmp =="int" || aux->tipoTmp == "int" && (yyvsp[0]).tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + (yyvsp[0]).temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						declaracoes.append(declaracaoTmp);
						preencheSimbolo(&sim, "conversao", traducao, "none", converteVar, aux->tipoTmp, aux->tipoTmp, declaracaoTmp);

						(yyval).traducao = (yyvsp[0]).traducao + traducao + "\t" + aux->temporaria + " = " + converteVar + ";\n";
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

				(yyval).rotulo = "atribuicao";
				(yyval).conteudo = "none";
				(yyval).temporaria = aux->temporaria;
				(yyval).tipo = aux->temporaria;
				(yyval).tipoTmp = (yyval).tipo;
				(yyval).declaracaoTmp = aux->declaracaoTmp;
			}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 427 "sintatica.y" /* yacc.c:1646  */
    {
				vector<Simbolo> bloco;
				empilhaPilhaBlocos(bloco);
			}
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 434 "sintatica.y" /* yacc.c:1646  */
    {
				Laco aux;
				aux.continuar = "";
				aux.continuar2 = "";
				aux.quebrar = "";
				empilhaLaco(aux);
			}
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 444 "sintatica.y" /* yacc.c:1646  */
    {
				Cond aux;
				aux.inicio = "";
				aux.fim = "";
				empilhaIf(aux);
			}
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 453 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + "\n" + (yyvsp[0]).traducao;
			}
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 457 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
			}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 463 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).rotulo = (yyvsp[-1]).rotulo;
				(yyval).traducao = (yyvsp[-1]).traducao;
				(yyval).conteudo = (yyvsp[-1]).conteudo;
				(yyval).temporaria = (yyvsp[-1]).temporaria;
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).tipoTmp = (yyvsp[-1]).tipoTmp;
				(yyval).declaracaoTmp = (yyvsp[-1]).declaracaoTmp;
				(yyval).verificadorInicializacao = (yyvsp[-1]).verificadorInicializacao;
			}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 474 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-7]).rotulo == "cadeia" || (yyvsp[-7]).rotulo == "booleano"){
					yyerror("Desculpe: Tipo não suportado para matrizes!\n");
				}
				if((yyvsp[-4]).tipo != "int" || (yyvsp[-2]).tipo != "int"){
					yyerror("Limites para o tamanho da matriz não suportados!\n");
				}

				Simbolo *aux, sim;
				if((aux = buscaBlocoAtual((yyvsp[-6]).rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string traducao;
					string temporaria = geraTemp();
					if((yyvsp[-7]).rotulo == "int")
						tipoTmp = "int";
					else if((yyvsp[-7]).rotulo == "real")
						tipoTmp = "float";
					else if((yyvsp[-7]).rotulo == "letra")
						tipoTmp = "char";

					declaracaoTmp = "\t" + tipoTmp + " " + temporaria + ";\n";
					declaracoes.append(declaracaoTmp);
					traducao = "\t" + temporaria + " = " + "("+ tipoTmp +"*)malloc(" + (yyvsp[-4]).temporaria +"*"+ (yyvsp[-2]).temporaria +"*sizeof("+ tipoTmp +"));\n";
					preencheSimboloMatriz(&sim, (yyvsp[-6]).rotulo, traducao, "none", temporaria, (yyvsp[-7]).rotulo, tipoTmp, declaracaoTmp, (yyvsp[-4]).temporaria, (yyvsp[-2]).temporaria);
				}else{
					yyerror("Variável " + (yyvsp[-6]).rotulo + " já foi declarada antes!\n");
				}

				(yyval).traducao = (yyvsp[-4]).traducao + (yyvsp[-2]).traducao + sim.traducao;
			}
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 506 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[-1]).tipo == "cadeia" || (yyvsp[-1]).tipo == "booleano"){
					yyerror("Desculpe: Tipo de dado não suportado para matrizes!\n");
				}

				Simbolo *aux, sim;
				string buffer;
				if((aux = buscaPilhaBlocos((yyvsp[-8]).rotulo)) != NULL){ //se a variável existe
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

					if(aux->tipoTmp == (yyvsp[-1]).tipoTmp && aux->tipo == (yyvsp[-1]).tipo){ //senão precisar de conversão
						tradMultiplica = "\t" + multiplica + " = " + (yyvsp[-6]).temporaria +"*"+ aux->tempColunas + ";\n";
						tradSoma = "\t" + soma + " = " + multiplica + "+" + (yyvsp[-4]).temporaria + ";\n";

						(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[-6]).traducao + (yyvsp[-4]).traducao + tradMultiplica + tradSoma + "\t" + aux->temporaria +"["+ soma +"]" + " = " + (yyvsp[-1]).temporaria + ";\n";
						if((yyvsp[-6]).tipo == "cadeia"){
						  	Cadeia cad;
						  	buscaInfoCadeia(&cad, (yyvsp[-6]).temporaria);
						  	cad.tempNome = aux->temporaria;
						  	insereTabelaCadeias(cad);
						}
						buffer = aux->temporaria;

					}else if(aux->tipoTmp == "float" && (yyvsp[-1]).tipoTmp == "int" || aux->tipoTmp == "int" && (yyvsp[-1]).tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + (yyvsp[-1]).temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						declaracoes.append(declaracaoTmp);

						tradMultiplica = "\t" + multiplica + " = " + (yyvsp[-6]).temporaria +"*"+ aux->tempColunas + ";\n";
						tradSoma = "\t" + soma + " = " + multiplica + "+" + (yyvsp[-4]).temporaria + ";\n";

						(yyval).traducao = (yyvsp[-1]).traducao + (yyvsp[-6]).traducao + (yyvsp[-4]).traducao + tradMultiplica + tradSoma + traducao + "\t" + aux->temporaria +"["+ soma +"]" + " = " + converteVar + ";\n";
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

				(yyval).rotulo = "atribuicao";
				(yyval).conteudo = "none";
				(yyval).temporaria = aux->temporaria;
				(yyval).tipo = aux->tipo;
				(yyval).tipoTmp = aux->tipoTmp;
				(yyval).declaracaoTmp = aux->declaracaoTmp;
			}
#line 1929 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 571 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
				Simbolo *aux, sim;

				if((aux = buscaBlocoAtual((yyvsp[-1]).rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string temporaria = geraTemp();
					if((yyvsp[-2]).rotulo == "int" || (yyvsp[-2]).rotulo == "booleano")
						tipoTmp = "int";
					else if((yyvsp[-2]).rotulo == "real")
						tipoTmp = "float";
					else if((yyvsp[-2]).rotulo == "letra")
						tipoTmp = "char";
					else if((yyvsp[-2]).rotulo == "cadeia")
						tipoTmp = "char *";

					declaracaoTmp = "\t" + tipoTmp + " " + temporaria + ";\n";
					declaracoes.append(declaracaoTmp);
					preencheSimbolo(&sim, (yyvsp[-1]).rotulo, "", "none", temporaria, (yyvsp[-2]).rotulo, tipoTmp, declaracaoTmp);
				}else{
					yyerror("Variável " + (yyvsp[-1]).rotulo + " já foi declarada antes!\n");
				}

			}
#line 1959 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 597 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo *aux, sim;
				string buffer;
				if((aux = buscaPilhaBlocos((yyvsp[-3]).rotulo)) != NULL){
					buffer = aux->temporaria;
					if(aux->tipoTmp == (yyvsp[-1]).tipoTmp && aux->tipo == (yyvsp[-1]).tipo){ //senão precisar de conversão
						(yyval).traducao = (yyvsp[-1]).traducao + "\t" + aux->temporaria + " = " + (yyvsp[-1]).temporaria + ";\n";
						aux->conteudo = (yyvsp[-1]).conteudo;
						if((yyvsp[-1]).tipo == "cadeia"){
						  	Cadeia cad;
						  	buscaInfoCadeia(&cad, (yyvsp[-1]).temporaria);
						  	cad.tempNome = aux->temporaria;
						  	insereTabelaCadeias(cad);
						}
						buffer = aux->temporaria;

					}else if(aux->tipoTmp == "float" && (yyvsp[-1]).tipoTmp == "int" || aux->tipoTmp == "int" && (yyvsp[-1]).tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + (yyvsp[-1]).temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						declaracoes.append(declaracaoTmp);

						(yyval).traducao = (yyvsp[-1]).traducao + traducao + "\t" + aux->temporaria + " = " + converteVar + ";\n";
						buffer = aux->temporaria; // pq some dps da linha 521
						aux->conteudo = (yyvsp[-1]).conteudo;
						preencheSimbolo(&sim, "conversao", traducao, "none", converteVar, aux->tipo, aux->tipoTmp, declaracaoTmp);
					}
					else{
						yyerror("Essa atribuicao não pode! \n");
					}
				}else{
					yyerror("Variável não declarada!\n");
				}

				aux->temporaria = buffer;

				(yyval).rotulo = "atribuicao";
				(yyval).conteudo = "none";
				(yyval).temporaria = aux->temporaria;
				(yyval).tipo = aux->tipo;
				(yyval).tipoTmp = aux->tipoTmp;
				(yyval).declaracaoTmp = aux->declaracaoTmp;
			}
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 641 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = "";
				Simbolo *aux, sim;

				if((aux = buscaBlocoAtual((yyvsp[-3]).rotulo)) == NULL){ //variável não foi declarada antes
					string tipoTmp;
					string declaracaoTmp;
					string temporaria = geraTemp();
					if((yyvsp[-4]).rotulo == "int" || (yyvsp[-4]).rotulo == "booleano")
						tipoTmp = "int";
					else if((yyvsp[-4]).rotulo == "real")
						tipoTmp = "float";
					else if((yyvsp[-4]).rotulo == "letra")
						tipoTmp = "char";
					else if((yyvsp[-4]).rotulo == "cadeia")
						tipoTmp = "char *";

					declaracaoTmp = "\t" + tipoTmp + " " + temporaria + ";\n";
					declaracoes.append(declaracaoTmp);
					preencheSimbolo(&sim, (yyvsp[-3]).rotulo, "", "none", temporaria, (yyvsp[-4]).rotulo, tipoTmp, declaracaoTmp);

					if((yyvsp[-1]).verificadorInicializacao == 1){
						VariaveisPossiveis.pop_back(); //desempilha o rotulo de TK_ID
						cout << "Atenção: Operação com variável não inicializada!\n"; //libera warning
					}

					///parte da atribuição
					if(sim.tipoTmp == (yyvsp[-1]).tipoTmp && sim.tipo == (yyvsp[-1]).tipo){ //senão precisar de conversão
						(yyval).traducao = (yyval).traducao + (yyvsp[-1]).traducao + "\t" + sim.temporaria + " = " + (yyvsp[-1]).temporaria + ";\n";

						if((yyvsp[-1]).tipo == "cadeia"){
						  	Cadeia cad;
						  	buscaInfoCadeia(&cad, (yyvsp[-1]).temporaria);
						  	cad.tempNome = sim.temporaria;
						  	insereTabelaCadeias(cad);
						}

					}else if(sim.tipoTmp == "float" && (yyvsp[-1]).tipoTmp == "int" || sim.tipoTmp == "int" && (yyvsp[-1]).tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string traducao = "\t" + converteVar + " = " + "(" + sim.tipoTmp + ")" + (yyvsp[-1]).temporaria + ";\n";
						string declaracaoTmp = "\t" + sim.tipoTmp + " " + converteVar + ";\n";
						declaracoes.append(declaracaoTmp);
						preencheSimbolo(&sim, "conversao", traducao, "none", converteVar, sim.tipoTmp, sim.tipoTmp, declaracaoTmp);

						(yyval).traducao = (yyval).traducao + (yyvsp[-1]).traducao + traducao + "\t" + temporaria + " = " + converteVar + ";\n";
					}
					else{
						yyerror("Essa atribuicao não pode! \n");
					}

					(yyval).rotulo = "atribuicao";
					(yyval).conteudo = "none";
					(yyval).temporaria = sim.temporaria;
					(yyval).tipo = sim.temporaria;
					(yyval).tipoTmp = (yyval).tipo;
					(yyval).declaracaoTmp = sim.declaracaoTmp;

				}else{
					yyerror("Variável " + (yyvsp[-3]).rotulo + " já foi declarada antes!\n");
				}
			}
#line 2073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 703 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo *aux;
				if((aux = buscaPilhaBlocos((yyvsp[-2]).rotulo)) != NULL){
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
							(yyval).traducao = "\t" + aux->temporaria + " = 1;\n";
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
						if((yyvsp[-1]).rotulo == "++"){
							string traducao = traducaoUna + "\t" + composto + " = "+ gambiarra + " + "+ unario + ";\n";
							(yyval).traducao = (yyval).traducao + traducao + "\t" + gambiarra + " = " + composto + ";\n";
						}
						else if((yyvsp[-1]).rotulo == "--"){
							string traducao = traducaoUna + "\t" + composto + " = "+ gambiarra + " - "+ unario + ";\n";
							(yyval).traducao = (yyval).traducao + traducao + "\t" + gambiarra + " = " + composto + ";\n";
						}
					}
				}
			}
#line 2123 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 749 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo *aux, sim, sim2, sim3, sim4;
				string buffer;
				if((aux = buscaPilhaBlocos((yyvsp[-3]).rotulo)) != NULL){

					buffer = aux->temporaria;

					if((yyvsp[-1]).verificadorInicializacao == 1){
						VariaveisPossiveis.pop_back(); //desempilha o rotulo de TK_ID
						cout << "Atenção: Operação com variável não inicializada!\n"; //libera warning
					}


					if(aux->tipo == "letra" || (yyvsp[-1]).tipo == "letra")
					{
						cout << "Essa atribuicao não pode! \n";
						exit(1);
					}
					else if(aux->tipo == "cadeia" && (yyvsp[-1]).tipo == "cadeia")
					{
						if((yyvsp[-2]).rotulo == "+="){
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
							buscaInfoCadeia(&s2, (yyvsp[-1]).temporaria);

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
								"\t" + sim2.temporaria + " = " + "(char *) malloc(" + tempTam + " * sizeof(char));\n" + "\t" + sim2.temporaria + " = strcat(" + varAux + ", " + (yyvsp[-1]).temporaria + ");\n";

							}else{
								sim2.traducao = "\t" + auxTempTam + " = " + s1.tempTam + " + " + s2.tempTam + ";\n" + "\t" + tempTam + " = " + auxTempTam + " - 1;\n" +
								"\t" + sim2.temporaria + " = " + "(char *) malloc(" + tempTam + " * sizeof(char));\n" + "\t" + sim2.temporaria + " = strcat(" + aux->temporaria + ", " + (yyvsp[-1]).temporaria + ");\n";
							}

							preencheSimbolo(&sim2, "composto", sim2.traducao, "none", sim2.temporaria, sim2.tipoTmp, sim2.tipoTmp, sim2.declaracaoTmp);
							(yyval).traducao = (yyvsp[-1]).traducao + sim2.traducao + "\n\t" + buffer + " = " + sim2.temporaria + ";\n\t";
						}
						else{
							cout << "Essa atribuicao não pode! \n";
							exit(1);
						}


					}
					else if(aux->tipoTmp == (yyvsp[-1]).tipoTmp && aux->tipo == (yyvsp[-1]).tipo){ //senão precisar de conversão
						string composto = geraTemp();
						//string traducao = "\t" + composto + " = " + "(" + aux->tipoTmp + ")" + $3.temporaria + ";\n";
						string traducao;
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + composto + ";\n";
						declaracoes.append(declaracaoTmp);
						if((yyvsp[-2]).rotulo == "+="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " + "+ (yyvsp[-1]).temporaria + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if((yyvsp[-2]).rotulo == "-="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " - "+ (yyvsp[-1]).temporaria + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if((yyvsp[-2]).rotulo == "*="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " * "+ (yyvsp[-1]).temporaria + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if((yyvsp[-2]).rotulo == "/="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " / "+ (yyvsp[-1]).temporaria + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if((yyvsp[-2]).rotulo == "%="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " % "+ (yyvsp[-1]).temporaria + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						preencheSimbolo(&sim, "composto", traducao, "none", composto, aux->tipoTmp, aux->tipoTmp, declaracaoTmp);

					}else if(aux->tipoTmp == "float" && (yyvsp[-1]).tipoTmp =="int" || aux->tipoTmp == "int" && (yyvsp[-1]).tipoTmp == "float"){ //vai precisar de conversão
						string converteVar = geraTemp();
						string composto = geraTemp();
						string traducao1 = "\t" + converteVar + " = " + "(" + aux->tipoTmp + ")" + (yyvsp[-1]).temporaria + ";\n";
						string declaracaoTmp = "\t" + aux->tipoTmp + " " + converteVar + ";\n";
						string declaracaoComp = "\t" + aux->tipoTmp + " " + composto + ";\n";

						if((yyvsp[-2]).rotulo == "+="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " + "+ converteVar + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if((yyvsp[-2]).rotulo == "-="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " - "+ converteVar + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if((yyvsp[-2]).rotulo == "*="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " * "+ converteVar + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if((yyvsp[-2]).rotulo == "/="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " / "+ converteVar + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
						}
						else if((yyvsp[-2]).rotulo == "%="){
							string traducao = "\t" + composto + " = "+ aux->temporaria + " % "+ converteVar + ";\n";
							(yyval).traducao = (yyvsp[-1]).traducao + traducao1 + traducao + "\t" + aux->temporaria + " = " + composto;
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

				(yyval).rotulo = "atribuicao";
				(yyval).conteudo = "none";
				(yyval).temporaria = aux->temporaria;
				(yyval).tipo = aux->temporaria;
				(yyval).tipoTmp = (yyval).tipo;
				(yyval).declaracaoTmp = aux->declaracaoTmp;
			}
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 905 "sintatica.y" /* yacc.c:1646  */
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
 					(yyval).traducao = "\n\tgoto " + aux1 + ";\n";
 				}
 				else
 				{

 					(yyval).traducao = "\n\tgoto " + PilhaLaco.back().continuar2 + ";\n";

 				}
 			}
#line 2309 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 927 "sintatica.y" /* yacc.c:1646  */
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
 					(yyval).traducao = "\n\tgoto " + aux1 + ";\n";
 				}
 				else
 				{

 					(yyval).traducao = "\n\tgoto " + PilhaLaco.back().quebrar + ";\n";

 				}
 			}
#line 2334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 949 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim;
 				string temporaria3	= geraTemp();
				string tipoTmp3 = "int";
				string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
				string atribuicao3 = "\t" + temporaria3 + " = " + "!" + (yyvsp[-3]).temporaria + ";\n";
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
 				(yyval).traducao = (yyvsp[-3]).traducao + atribuicao3 + "\t" + (yyvsp[-5]).rotulo + "(" + temporaria3 + ") goto "+ aux1 + ";\n" + (yyvsp[-1]).traducao +"\t"+ fim +"\n\t"+ aux1 + ":\n" + (yyvsp[0]).traducao +"\t"+aux3 +"\n";
 				desempilhaIf();
 			}
#line 2362 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 973 "sintatica.y" /* yacc.c:1646  */
    {
 				(yyval).traducao = (yyvsp[0]).traducao;
 			}
#line 2370 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 977 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[0]).traducao;
			}
#line 2378 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 981 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).traducao = (yyvsp[-1]).traducao + "\tcout << " + (yyvsp[-1]).temporaria + " << endl;\n";
			}
#line 2386 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 985 "sintatica.y" /* yacc.c:1646  */
    {
				//7 variavéis, a primeira já tá em G
				if((yyvsp[-1]).tipoTmp == "char *"){
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

					(yyval).traducao = "\t" + (yyvsp[-1]).temporaria + " = " + "NULL;\n" + atribuicao1 + atribuicao2 + atribuicao3 + atribuicao4 + atribuicao5 + atribuicao6;
					(yyval).traducao = (yyval).traducao + "\n\t" + blocoIni + ":\n" + "\tcin >> std::noskipws;\n\tcin >> *" + temporaria1 + ";\n";
					(yyval).traducao = (yyval).traducao + atribuicao3 + atribuicao4;
					(yyval).traducao = (yyval).traducao + "\tif(" + temporaria3 + ") goto " + blocoFim + ";\n";
					(yyval).traducao = (yyval).traducao + "\t" + (yyvsp[-1]).temporaria + " = " + "(char*)realloc(" + (yyvsp[-1]).temporaria + ", (" + temporaria2 + ")*sizeof(char));\n";
					(yyval).traducao = (yyval).traducao + "\t" + (yyvsp[-1]).temporaria + " = " + "strcat(" + (yyvsp[-1]).temporaria + ", "+ temporaria1 + ");\n";
					(yyval).traducao = (yyval).traducao + "\t" + temporaria2 + " = " + temporaria2 + " + " + temporaria5; + ";\n";
					(yyval).traducao = (yyval).traducao + "\n\tgoto " + blocoIni + ";\n\t" + blocoFim + ":\n";
					(yyval).traducao = (yyval).traducao + "\t" + (yyvsp[-1]).temporaria + " = " + "(char*)realloc(" + (yyvsp[-1]).temporaria + ", (" + temporaria2 + ")*sizeof(char));\n";
					(yyval).traducao = (yyval).traducao + "\t" + (yyvsp[-1]).temporaria + " = " + "strcat(" + (yyvsp[-1]).temporaria + ", '\\0');\n";
					(yyval).traducao = (yyval).traducao + "\tcin >> std::skipws;\n";

					Simbolo aux, aux2;
					Cadeia s;
					s.nomeVar = (yyvsp[-1]).rotulo;
					s.tempTam = temporaria2;
					s.tempNome = (yyvsp[-1]).temporaria;

					preencheSimbolo(&aux, "tam cadeia", s.tempTam + " = " , "?", s.tempTam, "int", "int", "int " + s.tempTam + ";");

					insereTabelaCadeias(s);
				}
				else{
					(yyval).traducao = (yyvsp[-1]).traducao + "\tcin >> " + (yyvsp[-1]).temporaria +";\n";
				}
			}
#line 2462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 1060 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim;
 				string temporaria3	= geraTemp();
				string tipoTmp3 = "int";
				string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
				string atribuicao3 = "\t" + temporaria3 + " = " + "!" + (yyvsp[-2]).temporaria + ";\n";
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
				(yyval).traducao = "\t"+ aux3 +":\n"+ (yyvsp[-2]).traducao + atribuicao3 + "\tif(" + temporaria3 + ") goto "+ aux2 + ":\n\t \n"+ (yyvsp[0]).traducao + "\n\tgoto " + aux3 +";\n\t"+ aux2 + ":\n";
 				// $$.traducao = "\n\t" + aux3 +":\n"+ $3.traducao + "\tif(" + $3.temporaria + ") goto "+ aux1 + ";\n\tgoto " + aux2 + ";\n\t" + aux1 +":"+ $5.traducao + "\n\tgoto " + aux3 +";\n\t"+ aux2 + ":\n";
 				//$$.traducao = "\n\t" + aux3 +":\n"+ $2.traducao + "\tif(" + $2.temporaria + ") goto "+ aux1 + ";\n\tgoto " + aux2 + ";\n\t" + aux1 +":"+ $4.traducao + "\n\tgoto " + aux3 +";\n\t"+ aux2 + ":\n";
 				desempilhaLaco();
 			}
#line 2497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 1091 "sintatica.y" /* yacc.c:1646  */
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
 				(yyval).traducao = "\n\t" + aux1 +":\n"+ (yyvsp[-4]).traducao + (yyvsp[-1]).traducao + aux2 + "\n\tif(" + (yyvsp[-1]).temporaria + ") goto "+ aux1 +";\n"+ aux3 +"\n";
 				desempilhaLaco();

 			}
#line 2518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 1108 "sintatica.y" /* yacc.c:1646  */
    {
 				Simbolo sim;
 				string aux1, aux2, aux3, aux4;
 				aux1 = geraBloco();
 				aux3 = geraBloco();

 				string temporaria3	= geraTemp();
				string tipoTmp3 = "int";
				string declaracaoTmp3 = "\tint " + temporaria3 + ";\n";
				string atribuicao3 = "\t" + temporaria3 + " = " + "!" + (yyvsp[-4]).temporaria + ";\n";
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
 				(yyval).traducao = (yyvsp[-6]).traducao + "\n\t" + aux3 +":\n"+ (yyvsp[-4]).traducao + atribuicao3 +"\tif(" + temporaria3 + ") goto "+ aux2 + ";\n\t\n"+ (yyvsp[0]).traducao + aux4 + (yyvsp[-2]).traducao +"\n\tgoto " + aux3 +";\n\t"+ aux2 + ":\n";
 				desempilhaLaco();
 			}
#line 2547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 1135 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim1, sim2;

				string converteVar = geraTemp();
				string traducao;
				string declaracaoTmp;

				if((yyvsp[-1]).tipoTmp == "char"){ //só pq não pode entre char e outra coisa
					cout << "Operacao não suportada para tipo letra!\n";
					exit(1);
				}

				if((yyvsp[-3]).rotulo == "inteirao"){
					traducao = "\t" + converteVar + " = " + "(int)" + (yyvsp[-1]).temporaria + ";\n";
					declaracaoTmp = "\tint " + converteVar + ";\n";
					declaracoes.append(declaracaoTmp);
					preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, "int", "int", declaracaoTmp);
					sim2.tipo = "int";
					sim2.tipoTmp = "int";

				}else if((yyvsp[-3]).rotulo == "flutua"){
					traducao = "\t" + converteVar + " = " + "(float)" + (yyvsp[-1]).temporaria + ";\n";
					declaracaoTmp = "\tfloat " + converteVar + ";\n";
					declaracoes.append(declaracaoTmp);
					preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, "real", "float", declaracaoTmp);
					sim2.tipo = "real";
					sim2.tipoTmp = "float";

				}
				(yyval).traducao = (yyvsp[-1]).traducao + traducao;

				string opVar = geraTemp();
				sim2.rotulo = "operacao";
				sim2.temporaria = opVar;

				sim2.declaracaoTmp = "\t" + sim2.tipoTmp + " " + sim2.temporaria + ";\n";
				declaracoes.append(sim2.declaracaoTmp);
				sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + ";\n";

				insereTabelaSimbolos((PilhaBlocos.back()), &sim2);

				(yyval).traducao = (yyval).traducao + sim2.traducao;
				(yyval).rotulo = sim2.rotulo;
				(yyval).conteudo = sim2.conteudo;
				(yyval).temporaria = sim2.temporaria;
				(yyval).tipo = sim2.tipo;
				(yyval).tipoTmp = sim2.tipoTmp;
				(yyval).declaracaoTmp = sim2.declaracaoTmp;

			}
#line 2602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 1186 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim;
				string op;
				if((yyvsp[-1]).rotulo == "ou"){
					op = "||";
				}
				else{
					op = "&&";
				}
				if((yyvsp[-2]).tipo == "booleano" && (yyvsp[0]).tipo == "booleano"){
					(yyval).temporaria = geraTemp();
					(yyval).declaracaoTmp = "\tint " + (yyval).temporaria + ";\n";
					declaracoes.append("\tint " + (yyval).temporaria + ";\n");
					string traducao = "\t" + (yyval).temporaria + " = " + (yyvsp[-2]).temporaria + " " + op + " " + (yyvsp[0]).temporaria + ";\n";
					preencheSimbolo(&sim, "operacao", traducao, "none", (yyval).temporaria, "booleano", "int", (yyval).declaracaoTmp);

					(yyval).rotulo = "operacao";
					(yyval).conteudo = "none";
					(yyval).tipoTmp = "int";
					(yyval).tipo = "booleano";
					(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao + traducao;
				}else{
					cout << "Operacao lógica so entre booleanos, bb.\n";
					exit(1);
				}
			}
#line 2633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 1213 "sintatica.y" /* yacc.c:1646  */
    {

				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteuOp2 = false; //var aux para saber qual operando foi convertido, nesse caso ela aciona na conversão do 2º operando
				string converteVar = "none";
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;

				if((yyvsp[-2]).tipoTmp == "" || (yyvsp[0]).tipoTmp == ""){ //caso da inicialização onde não sei o tipo do operando
					if((yyvsp[0]).tipoTmp == "int"){
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

						sim2.traducao = "\t" + varAux + " = 0;\n" + "\t" + sim2.temporaria + " = " + varAux + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}else if((yyvsp[0]).tipoTmp == "float"){
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

						sim2.traducao = "\t" + varAux + " = 0.0;\n" + "\t" + sim2.temporaria + " = " + varAux + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}
				}else{

					if((yyvsp[-2]).tipoTmp != (yyvsp[0]).tipoTmp){ //conversão

						if((yyvsp[-2]).tipoTmp == "char" || (yyvsp[0]).tipoTmp == "char"){ //só pq não pode entre char e outra coisa
							cout << "Operacao não suportada entre letra e não-letra!\n";
							exit(1);
						}

						converteu = true;
						converteVar = geraTemp();
						string traducao, declaracaoTmp;

						if((yyvsp[-2]).tipoTmp == "float"){
							converteuOp2 = true;
							traducao = "\t" + converteVar + " = " + "(float)" + (yyvsp[0]).temporaria + ";\n";
							declaracaoTmp = "\t" + (yyvsp[-2]).tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, (yyvsp[-2]).tipoTmp, (yyvsp[-2]).tipoTmp, declaracaoTmp);

						}else if((yyvsp[0]).tipoTmp == "float"){

							traducao = "\t" + converteVar + " = " + "(float)" + (yyvsp[-2]).temporaria + ";\n";
							declaracaoTmp = "\t" + (yyvsp[0]).tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, (yyvsp[0]).tipoTmp, (yyvsp[0]).tipoTmp, declaracaoTmp);
						}

						(yyval).traducao = (yyval).traducao + traducao;
					}

					string opVar = geraTemp();
					sim2.rotulo = "operacao";
					sim2.temporaria = opVar;
					if((yyvsp[-2]).tipoTmp == "float" || (yyvsp[0]).tipoTmp == "float"){
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
							sim2.traducao = "\t" + sim2.temporaria + " = " + (yyvsp[-2]).temporaria + (yyvsp[-1]).rotulo + converteVar + ";\n";
						}
						else{
							sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
						}
					}else{
						sim2.traducao = "\t" + sim2.temporaria + " = " + (yyvsp[-2]).temporaria + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}
				}
				insereTabelaSimbolos((PilhaBlocos.back()), &sim2);

				(yyval).traducao = (yyval).traducao + sim2.traducao;
				(yyval).rotulo = sim2.rotulo;
				(yyval).conteudo = sim2.conteudo;
				(yyval).temporaria = sim2.temporaria;
				(yyval).tipoTmp = "int";
				(yyval).tipo = "booleano";
				(yyval).declaracaoTmp = sim2.declaracaoTmp;

			}
#line 2751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 1327 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).rotulo = (yyvsp[0]).rotulo;
				(yyval).traducao = (yyvsp[0]).traducao;
				(yyval).conteudo = (yyvsp[0]).conteudo;
				(yyval).temporaria = (yyvsp[0]).temporaria;
				(yyval).tipo = (yyvsp[0]).tipo;
				(yyval).tipoTmp = (yyvsp[0]).tipoTmp;
				(yyval).declaracaoTmp = (yyvsp[0]).declaracaoTmp;
				(yyval).verificadorInicializacao = (yyvsp[0]).verificadorInicializacao;
			}
#line 2766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 1340 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteuOp2 = false; //var aux para saber qual operando foi convertido, nesse caso ela aciona na conversão do 2º operando
				string converteVar = "none";
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;

				if((yyvsp[-2]).tipoTmp == "" || (yyvsp[0]).tipoTmp == ""){ //caso da inicialização onde não sei o tipo do operando
					if((yyvsp[0]).tipoTmp == "int"){
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

						sim2.traducao = "\t" + varAux + " = 0;\n" + "\t" + sim2.temporaria + " = " + varAux + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}else if((yyvsp[0]).tipoTmp == "float"){
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

						sim2.traducao = "\t" + varAux + " = 0.0;\n" + "\t" + sim2.temporaria + " = " + varAux + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}else if((yyvsp[0]).tipoTmp == "char *"){
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

						sim2.traducao = "\t" + varAux + " = (char*)malloc(sizeof(char));\n" + "\t" + varAux + " = strcpy(" + varAux + ",\"\");\n" + "\t" + sim2.temporaria + " = " + varAux + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}

				}else{

					if((yyvsp[-2]).tipoTmp != (yyvsp[0]).tipoTmp){ //conversão, falta fazer a conversão dos outros tipos pra string, quando um dos tipos for string e o outro não
						converteu = true;			// pergunta: faremos essa conversão implícita, ou só permitiremos a explícita : palavreando()?
						converteVar = geraTemp();
						string traducao, declaracaoTmp;
						if((yyvsp[-2]).tipoTmp == "float"){
							converteuOp2 = true;
							traducao = "\t" + converteVar + " = " + "(float)" + (yyvsp[0]).temporaria + ";\n";
							declaracaoTmp = "\t" + (yyvsp[-2]).tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, (yyvsp[-2]).tipoTmp, (yyvsp[-2]).tipoTmp, declaracaoTmp);

						}else if((yyvsp[0]).tipoTmp == "float"){

							traducao = "\t" + converteVar + " = " + "(float)" + (yyvsp[-2]).temporaria + ";\n";
							declaracaoTmp = "\t" + (yyvsp[0]).tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, (yyvsp[0]).tipoTmp, (yyvsp[0]).tipoTmp, declaracaoTmp);
						}

						(yyval).traducao = (yyval).traducao + traducao;
					}

					if((yyvsp[-2]).tipo == "cadeia" && (yyvsp[0]).tipo == "cadeia"){
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

						buscaInfoCadeia(&s1, (yyvsp[-2]).temporaria);
						buscaInfoCadeia(&s2, (yyvsp[0]).temporaria);

						sim2.traducao = "\t" + auxTempTam + " = " + s1.tempTam + " + " + s2.tempTam + ";\n" + "\t" + tempTam + " = " + auxTempTam + " - 1;\n" +
						"\t" + sim2.temporaria + " = " + "(char *) malloc(" + tempTam + " * sizeof(char));\n" + "\t" + sim2.temporaria + " = strcat(" + (yyvsp[-2]).temporaria + ", " + (yyvsp[0]).temporaria + ");\n";
					}else{
						string opVar = geraTemp();
						sim2.rotulo = "operacao";
						sim2.temporaria = opVar;

						if((yyvsp[-2]).tipoTmp == "float" || (yyvsp[0]).tipoTmp == "float"){
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
								sim2.traducao = "\t" + sim2.temporaria + " = " + (yyvsp[-2]).temporaria + (yyvsp[-1]).rotulo + converteVar + ";\n";
							}
							else{
								sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
							}
						}else{
							sim2.traducao = "\t" + sim2.temporaria + " = " + (yyvsp[-2]).temporaria + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
						}
					}

				}

				insereTabelaSimbolos((PilhaBlocos.back()), &sim2);

				(yyval).traducao = (yyval).traducao + sim2.traducao;
				(yyval).rotulo = sim2.rotulo;
				(yyval).conteudo = sim2.conteudo;
				(yyval).temporaria = sim2.temporaria;
				(yyval).tipo = sim2.tipo;
				(yyval).tipoTmp = sim2.tipoTmp;
				(yyval).declaracaoTmp = sim2.declaracaoTmp;
			}
#line 2920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1490 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).rotulo = (yyvsp[0]).rotulo;
				(yyval).traducao = (yyvsp[0]).traducao;
				(yyval).conteudo = (yyvsp[0]).conteudo;
				(yyval).temporaria = (yyvsp[0]).temporaria;
				(yyval).tipo = (yyvsp[0]).tipo;
				(yyval).tipoTmp = (yyvsp[0]).tipoTmp;
				(yyval).declaracaoTmp = (yyvsp[0]).declaracaoTmp;
				(yyval).verificadorInicializacao = (yyvsp[0]).verificadorInicializacao;
			}
#line 2935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1503 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim1, sim2;
				bool converteu = false;
				bool converteuOp2 = false; //var aux para saber qual operando foi convertido, nesse caso ela aciona na conversão do 2º operando
				string converteVar = "none";
				(yyval).traducao = (yyvsp[-2]).traducao + (yyvsp[0]).traducao;

				if((yyvsp[-2]).tipoTmp == "" || (yyvsp[0]).tipoTmp == ""){ //caso da inicialização onde não sei o tipo do operando
					if((yyvsp[0]).tipoTmp == "int"){
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

						sim2.traducao = "\t" + varAux + " = 0;\n" + "\t" + sim2.temporaria + " = " + varAux + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}else if((yyvsp[0]).tipoTmp == "float"){
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

						sim2.traducao = "\t" + varAux + " = 0.0;\n" + "\t" + sim2.temporaria + " = " + varAux + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}
				}else{
					if((yyvsp[-2]).tipoTmp != (yyvsp[0]).tipoTmp){ //conversão
						converteu = true;
						converteVar = geraTemp();
						string traducao, declaracaoTmp;
						if((yyvsp[-2]).tipoTmp == "float"){
							converteuOp2 = true;
							traducao = "\t" + converteVar + " = " + "(float)" + (yyvsp[0]).temporaria + ";\n";
							declaracaoTmp = "\t" + (yyvsp[-2]).tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, (yyvsp[-2]).tipoTmp, (yyvsp[-2]).tipoTmp, declaracaoTmp);

						}else if((yyvsp[0]).tipoTmp == "float"){

							traducao = "\t" + converteVar + " = " + "(float)" + (yyvsp[-2]).temporaria + ";\n";
							declaracaoTmp = "\t" + (yyvsp[0]).tipoTmp + " " + converteVar + ";\n";
							declaracoes.append(declaracaoTmp);
							preencheSimbolo(&sim1, "conversao", traducao, "none", converteVar, (yyvsp[0]).tipoTmp, (yyvsp[0]).tipoTmp, declaracaoTmp);
						}

						(yyval).traducao = (yyval).traducao + traducao;
					}

					string opVar = geraTemp();
					sim2.rotulo = "operacao";
					sim2.temporaria = opVar;
					if((yyvsp[-2]).tipoTmp == "float" || (yyvsp[0]).tipoTmp == "float"){
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
							sim2.traducao = "\t" + sim2.temporaria + " = " + (yyvsp[-2]).temporaria + (yyvsp[-1]).rotulo + converteVar + ";\n";
						}
						else{
							sim2.traducao = "\t" + sim2.temporaria + " = " + converteVar + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
						}
					}else{
						sim2.traducao = "\t" + sim2.temporaria + " = " + (yyvsp[-2]).temporaria + (yyvsp[-1]).rotulo + (yyvsp[0]).temporaria + ";\n";
					}
				}

				insereTabelaSimbolos((PilhaBlocos.back()), &sim2);

				(yyval).traducao = (yyval).traducao + sim2.traducao;
				(yyval).rotulo = sim2.rotulo;
				(yyval).conteudo = sim2.conteudo;
				(yyval).temporaria = sim2.temporaria;
				(yyval).tipo = sim2.tipo;
				(yyval).tipoTmp = sim2.tipoTmp;
				(yyval).declaracaoTmp = sim2.declaracaoTmp;
			}
#line 3044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1608 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).rotulo = (yyvsp[0]).rotulo;
				(yyval).traducao = (yyvsp[0]).traducao;
				(yyval).conteudo = (yyvsp[0]).conteudo;
				(yyval).temporaria = (yyvsp[0]).temporaria;
				(yyval).tipo = (yyvsp[0]).tipo;
				(yyval).tipoTmp = (yyvsp[0]).tipoTmp;
				(yyval).declaracaoTmp = (yyvsp[0]).declaracaoTmp;
				(yyval).verificadorInicializacao = (yyvsp[0]).verificadorInicializacao;
			}
#line 3059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1621 "sintatica.y" /* yacc.c:1646  */
    {
				(yyval).rotulo = (yyvsp[-1]).rotulo;
				(yyval).traducao = (yyvsp[-1]).traducao;
				(yyval).conteudo = (yyvsp[-1]).conteudo;
				(yyval).temporaria = (yyvsp[-1]).temporaria;
				(yyval).tipo = (yyvsp[-1]).tipo;
				(yyval).tipoTmp = (yyvsp[-1]).tipoTmp;
				(yyval).declaracaoTmp = (yyvsp[-1]).declaracaoTmp;
			}
#line 3073 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1631 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim;
				subirInfoPrimitiva(&(yyval), sim, "inteiro", (yyvsp[0]).traducao, geraTemp(), "int", "int");
			}
#line 3082 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1636 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim;
				subirInfoPrimitiva(&(yyval), sim, "real", (yyvsp[0]).traducao, geraTemp(), "real", "float");
			}
#line 3091 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1641 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo sim;
				subirInfoPrimitiva(&(yyval), sim, "letra", (yyvsp[0]).traducao, geraTemp(), "letra", "char");
			}
#line 3100 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1646 "sintatica.y" /* yacc.c:1646  */
    {
				if((yyvsp[0]).traducao == "falso"){
					(yyvsp[0]).traducao = "0";
				}else{
					(yyvsp[0]).traducao = "1";
				}
				Simbolo sim;
				subirInfoPrimitiva(&(yyval), sim, "booleano", (yyvsp[0]).traducao, geraTemp(), "booleano", "int");
			}
#line 3114 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1656 "sintatica.y" /* yacc.c:1646  */
    {
				Simbolo *aux;
				if((aux = buscaPilhaBlocos((yyvsp[0]).rotulo)) != NULL){ //nome de variável existe
					(yyval).rotulo = (yyvsp[0]).rotulo;
					(yyval).traducao = aux->traducao;
					(yyval).conteudo = aux->conteudo;
					(yyval).temporaria = aux->temporaria;
					(yyval).tipo = aux->tipo;
					(yyval).tipoTmp = aux->tipoTmp;
					(yyval).declaracaoTmp = aux->declaracaoTmp;
					(yyval).tempLinhas = aux->tempLinhas;
					(yyval).tempColunas = aux->tempColunas;
				}else{ //não confirmo que não foi declarada ainda, dou uma chance
					VariaveisPossiveis.push_back((yyvsp[0]).rotulo);
					(yyval).rotulo = (yyvsp[0]).rotulo;
					(yyval).traducao = "";
					(yyval).conteudo = "";
					(yyval).temporaria = "";
					(yyval).tipo = "";
					(yyval).tipoTmp = "";
					(yyval).declaracaoTmp = "";
					(yyval).verificadorInicializacao = 1;
					//yyerror("Identificador sem pai! D:"); esse cara vai lá pro bloco!!!
				}
			}
#line 3144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1682 "sintatica.y" /* yacc.c:1646  */
    {
				Cadeia s;
				Simbolo aux, sim;
				s.nomeVar = "none";
				s.tam = (yyvsp[0]).traducao.length() - 1;
				s.tempTam = geraTemp();
				s.tempNome = geraTemp();

				declaracoes.append("\tint " + s.tempTam + ";\n");

				preencheSimbolo(&aux, "tam cadeia", s.tempTam + " = " + to_string(s.tam), to_string(s.tam), s.tempTam, "int", "int", "int " + s.tempTam + ";");

				subirInfoString(&(yyval), sim, "cadeia", (yyvsp[0]).traducao, s.tempNome, "cadeia", "char *", s.tempTam, to_string(s.tam));

				insereTabelaCadeias(s);

				/*
					int temp_tamanho_string = 0;
					char * temp;
					temp = (char*) malloc(temp_tamanho_string*sizeof(char));
				*/
			}
#line 3171 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3175 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1706 "sintatica.y" /* yacc.c:1906  */


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
