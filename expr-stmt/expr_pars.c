/* $Id: Parser.c,v 1.54 2010/07/07 09:53:21 grosch Exp $ */

# include "expr_pars.h"
# include <stdio.h>
# include <stddef.h>

# ifndef EXTERN_C_BEGIN
#  define EXTERN_C_BEGIN
#  define EXTERN_C_END
# endif

EXTERN_C_BEGIN
# include "rString.h"
# include "rSystem.h"
# include "rMemory.h"
# include "General.h"
# include "DynArray.h"
# ifndef NO_RECOVER
#  include "Sets.h"
# endif
# if ! defined NO_RECOVER | defined YYReParse
#  include "Errors.h"
# endif
# if defined YYDEBUG | defined lex_interface
#  include "Position.h"
# endif
EXTERN_C_END

# ifdef lex_interface
#  define expr_scan_GetToken	yylex
     extern int yylex ARGS ((void));
#  ifndef AttributeDef
#   include "Position.h"
	   typedef struct { tPosition Position; } expr_scan_tScanAttribute;
	   expr_scan_tScanAttribute	expr_scan_Attribute = {{ 0, 0 }};
#  endif
#  ifndef ErrorAttributeDef
#   define expr_scan_ErrorAttribute(Token, RepairAttribute)
#  endif
#  ifndef yyGetAttribute
#   define yyGetAttribute(yyAttrStackPtr, a) * yyAttrStackPtr = yylval
#  endif
# else
#  include "expr_scan.h"
#  ifndef yyGetAttribute
#   define yyGetAttribute(yyAttrStackPtr, a) (yyAttrStackPtr)->Scan = a
#  endif
# endif

static void yyExit ARGS ((void)) { rExit (1); }

	void		(* expr_pars_Exit) ARGS ((void)) = yyExit;

static void yyCheckMemory
# ifdef HAVE_ARGS
   (char * ptr)
# else
   (ptr) char * ptr;
# endif
{
  if (! (ptr)) expr_pars_Exit ();
}

# define yyMakeArray(ptr, count, size)	 { MakeArray (ptr, count, size); \
					   yyCheckMemory (* ptr); }
# define yyExtendArray(ptr, count, size) { ExtendArray (ptr, count, size); \
					   yyCheckMemory (* ptr); }

typedef unsigned short	yyStateRange	;
typedef unsigned short	yySymbolRange	;
typedef struct { yyStateRange Check, Next; } yytComb;
typedef enum {
yyNT0_intern	= 32,
yyNTroot	= 33,
yyNTstmt_l	= 34,
yyNTstmt	= 35,
yyNTelseif_l	= 36,
yyNTexpr	= 37,
yyNTexpr_l	= 38,
yyNTexprs	= 39
} yytNonterminal;
typedef struct { short yyMode; rbool yyActions, yyMessages; } yytControl;

static	yytControl	yyControl	= { 0, rtrue, rtrue };
	rbool		expr_pars_Debug	= rfalse;

# define yyFirstTerminal	0
# define yyLastTerminal	31
# define yySetSize	32
# define yyFirstSymbol	0
# define yyLastSymbol	39
# define yyTTableMax	407
# define yyNTableMax	71
# define yyStartState	1
# define yyFirstReadState	1
# define yyLastReadState	61
# define yyFirstReadReduceState	62
# define yyLastReadReduceState	69
# define yyFirstReduceState	70
# define yyLastReduceState	105
# define yyLastState	105
# define yyLastStopState	70
# define YYTDefault
# define YYNDefault

# define yyFirstFinalState	yyFirstReadReduceState

# define ErrorMessages(Messages) yyControl.yyMessages = Messages
# define SemActions(Actions)	 yyControl.yyActions = Actions

# ifdef YYCSTree
#  include "cs_tree.h"
#  define CommonParsAttrs tCSTree Tree;
# endif

# ifdef YYGetLook

#  define GetLookahead(k)	yyGetLookahead ((k) - 1, yyTerminal)
#  define GetAttribute(k, a)	xxGetAttribute ((k) - 1, yyTerminal, a)

static int yyGetLookahead	ARGS ((int yyk, yySymbolRange yyToken));
static void xxGetAttribute	ARGS ((int yyk, yySymbolRange yyToken,
				expr_scan_tScanAttribute * yyAttribute));

# endif

/* line 8 "expr_pars.lrk" */


/* line 24 "expr.pars" */

 # include <stdio.h>
 # include "Tree.h"

  static tTree set_stmt_end (tTree head)
  /* Set the Next field of 'head' (a STMT-node) to no_stmt() */
  {
     head->STMT.Next = mno_stmt();
     return head;
  }

  static tTree set_stmt_next (tTree head, tTree tail)
  /* Set the Next field of 'head' (a STMT-node) to 'tail' (a STMTS-node) */
  {
     head->STMT.Next = tail;
     return head;
  }


/* line 31 "expr_pars.lrk" */
# ifdef CommonParsAttrs
typedef struct { CommonParsAttrs } yytCommonParsAttrs;
#  define yyCommon yytCommonParsAttrs Common;
#  define yyCommonParsAttrs CommonParsAttrs
# else
#  define yyCommon
#  define yyCommonParsAttrs
# endif

typedef struct { yyCommonParsAttrs tTree tree; } zz_stmt_l;
typedef struct { yyCommonParsAttrs tTree tree; } zz_stmt;
typedef struct { yyCommonParsAttrs tTree tree; } zz_elseif_l;
typedef struct { yyCommonParsAttrs tTree tree; } zz_expr;
typedef struct { yyCommonParsAttrs tTree tree; } zz_expr_l;

typedef union {
expr_scan_tScanAttribute Scan;
yyCommon
zz_stmt_l stmt_l;
zz_stmt stmt;
zz_elseif_l elseif_l;
zz_expr expr;
zz_expr_l expr_l;
} tParsAttribute;

/* line 177 "expr_pars.c" */

# if defined lex_interface & ! defined yylvalDef
     tParsAttribute yylval;
# endif

# ifndef yyInitStackSize
#  define yyInitStackSize	100
# endif
# define yyNoState		0
# define yystandard		1
# define yytrial		2
# define yybuffer		4
# define yyreparse		8
# define yyS			yySynAttribute
# define yyA			yyAttrStackPtr
# define YYACCEPT		goto yyAccept
# define YYABORT		goto yyAbort

# ifdef YYDEC_TABLE
#  define yyDecrement(x)
#  define yySetNT(x)
# else
#  define yyDecrement(x)	yyStateStackPtr -= x; yyAttrStackPtr -= x;
#  define yySetNT(x)		yyNonterminal = x;
# endif

# ifdef YYNDefault
#  define yytNComb yytComb
# else
#  define yytNComb yyStateRange
# endif

# if defined YYDEBUG | defined YYDCRP
static	long		yyCount		= 0;
static	FILE *		yyTrace		;

static	void		yyPrintState	ARGS ((yyStateRange yyState));
static	void		yyNl		ARGS ((void));

static	char *		yyRule		[] = { 0,
"0_intern : root _EOF_ ",
"root : stmt_l ",
"stmt_l : stmt ",
"stmt_l : stmt_l ';' stmt ",
"stmt : identifier ':=' expr ",
"stmt : IF expr THEN stmt_l elseif_l END ",
"stmt : WHILE expr DO stmt_l END ",
"stmt : PRINT '(' expr_l ')' ",
"elseif_l : ",
"elseif_l : ELSE stmt_l ",
"elseif_l : ELSEIF expr THEN stmt_l elseif_l ",
"expr : int_const ",
"expr : float_const ",
"expr : pi ",
"expr : identifier ",
"expr : '(' expr ')' ",
"expr : expr '+' expr ",
"expr : expr '-' expr ",
"expr : expr '*' expr ",
"expr : expr '/' expr ",
"expr : expr '^' expr ",
"expr : expr '?' expr ':' expr ",
"expr : '+' expr ",
"expr : '-' expr ",
"expr : expr '>' expr ",
"expr : expr '<' expr ",
"expr : expr '=' expr ",
"expr : expr '&' expr ",
"expr : expr '|' expr ",
"expr : '!' expr ",
"expr : identifier '(' expr_l ')' ",
"expr_l : ",
"expr_l : expr ",
"expr_l : exprs ',' expr ",
"exprs : expr ",
"exprs : exprs ',' expr ",
""
};
# endif
	char *		expr_pars_TokenName	[yyLastTerminal + 2] = {
"_EOF_",
"int_const",
"float_const",
"identifier",
":=",
"pi",
"(",
")",
"+",
"-",
"*",
"/",
"^",
"?",
":",
">",
"<",
"=",
"&",
"|",
"!",
",",
"IF",
"THEN",
"ELSE",
"ELSEIF",
"END",
"WHILE",
"DO",
"PRINT",
";",
0,
""
};
static	yytComb		yyTComb		[yyTTableMax + 1] = {
{   9,   84}, {   6,   70}, {   0,    0}, {   0,    0}, {   2,    8}, 
{   0,    0}, {   9,   19}, {   9,   84}, {   9,   84}, {   9,   84}, 
{   9,   84}, {   9,   84}, {   9,   84}, {   9,   84}, {   9,   84}, 
{   9,   84}, {   9,   84}, {   9,   84}, {   9,   84}, {   9,   84}, 
{   5,   16}, {   9,   84}, {  35,   64}, {   9,   84}, {   9,   84}, 
{   9,   84}, {   9,   84}, {  41,   89}, {   9,   84}, {   7,   71}, 
{   9,   84}, {  61,   53}, {  61,   54}, {  61,   78}, {  41,   89}, 
{  41,   89}, {  41,   89}, {  41,   89}, {  41,   89}, {  37,   69}, 
{  41,   89}, {  41,   89}, {  41,   89}, {  41,   89}, {  41,   89}, 
{  41,   89}, {  41,   89}, {  16,  101}, {  41,   89}, {  36,   51}, 
{  41,   89}, {  41,   89}, {  41,   89}, {  41,   89}, {  42,   90}, 
{  41,   89}, {  14,   32}, {  41,   89}, {  55,   62}, {   7,   17}, 
{  34,  102}, {  42,   90}, {  42,   90}, {  42,   90}, {  42,   90}, 
{  42,   90}, {  58,   79}, {  42,   90}, {  42,   90}, {  42,   90}, 
{  42,   90}, {  42,   90}, {  42,   90}, {  42,   90}, {  34,  104}, 
{  42,   90}, {   0,    0}, {  42,   90}, {  42,   90}, {  42,   90}, 
{  42,   90}, {  40,   88}, {  42,   90}, {   0,    0}, {  42,   90}, 
{   0,    0}, {   0,    0}, {  56,  103}, {  40,   88}, {  40,   88}, 
{  40,   88}, {  40,   88}, {  40,   88}, {   0,    0}, {  40,   88}, 
{  40,   88}, {  40,   88}, {  40,   88}, {  40,   88}, {  40,   88}, 
{  40,   88}, {  56,  105}, {  40,   88}, {   0,    0}, {  40,   88}, 
{  40,   88}, {  40,   88}, {  40,   88}, {  39,   87}, {  40,   88}, 
{  50,   63}, {  40,   88}, {   0,    0}, {   0,    0}, {  50,   17}, 
{  39,   87}, {  39,   87}, {  39,   87}, {   0,    0}, {   0,    0}, 
{   0,    0}, {  39,   87}, {  39,   87}, {  39,   87}, {  39,   87}, 
{  39,   87}, {  39,   87}, {  39,   87}, {   0,    0}, {  39,   87}, 
{   0,    0}, {  39,   87}, {  39,   87}, {  39,   87}, {  39,   87}, 
{  38,   86}, {  39,   87}, {   0,    0}, {  39,   87}, {   0,    0}, 
{   0,    0}, {   0,    0}, {  38,   86}, {  38,   86}, {  38,   86}, 
{   0,    0}, {   0,    0}, {   0,    0}, {  38,   86}, {  38,   86}, 
{  38,   86}, {  38,   86}, {  38,   86}, {  38,   86}, {  38,   86}, 
{  45,   95}, {  38,   86}, {   0,    0}, {  38,   86}, {  38,   86}, 
{  38,   86}, {  38,   86}, {  45,   95}, {  38,   86}, {   0,    0}, 
{  38,   86}, {   0,    0}, {   0,    0}, {  45,   95}, {  45,   95}, 
{  45,   95}, {  45,   95}, {  45,   95}, {  45,   95}, {  45,   95}, 
{  46,   96}, {  45,   95}, {   0,    0}, {  45,   95}, {  45,   95}, 
{  45,   95}, {  45,   95}, {  46,   96}, {  45,   95}, {   0,    0}, 
{  45,   95}, {   0,    0}, {   0,    0}, {  46,   96}, {  46,   96}, 
{  46,   96}, {  46,   96}, {  46,   96}, {  46,   96}, {  46,   96}, 
{   0,    0}, {  46,   96}, {   0,    0}, {  46,   96}, {  46,   96}, 
{  46,   96}, {  46,   96}, {  18,   74}, {  46,   96}, {   0,    0}, 
{  46,   96}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{  18,   21}, {  18,   22}, {  18,   23}, {  18,   24}, {  18,   25}, 
{  18,   26}, {   0,    0}, {  18,   27}, {  18,   28}, {  18,   29}, 
{  18,   30}, {  18,   31}, {  44,   94}, {   0,    0}, {   0,    0}, 
{   0,    0}, {  18,   74}, {  18,   74}, {  18,   74}, {  44,   94}, 
{   0,    0}, {   0,    0}, {  18,   74}, {   0,    0}, {   0,    0}, 
{  44,   94}, {  44,   94}, {  44,   94}, {  44,   94}, {  44,   94}, 
{  44,   94}, {  44,   94}, {  47,   97}, {  44,   94}, {   0,    0}, 
{  44,   94}, {  44,   94}, {  44,   94}, {  44,   94}, {  47,   97}, 
{  44,   94}, {   0,    0}, {  44,   94}, {   0,    0}, {   0,    0}, 
{  47,   97}, {  47,   97}, {   0,    0}, {   0,    0}, {   0,    0}, 
{  47,   97}, {  47,   97}, {   0,    0}, {  47,   97}, {   0,    0}, 
{  47,   97}, {  47,   97}, {  47,   97}, {  47,   97}, {   0,    0}, 
{  47,   97}, {   0,    0}, {  47,   97}, {  43,   21}, {  43,   22}, 
{  43,   23}, {  43,   24}, {  43,   25}, {  43,   26}, {  43,   52}, 
{  43,   27}, {  43,   28}, {  43,   29}, {  43,   30}, {  43,   31}, 
{  20,   68}, {  20,   21}, {  20,   22}, {  20,   23}, {  20,   24}, 
{  20,   25}, {  20,   26}, {   0,    0}, {  20,   27}, {  20,   28}, 
{  20,   29}, {  20,   30}, {  20,   31}, {  59,   21}, {  59,   22}, 
{  59,   23}, {  59,   24}, {  59,   25}, {  59,   26}, {   0,    0}, 
{  59,   27}, {  59,   28}, {  59,   29}, {  59,   30}, {  59,   31}, 
{   0,    0}, {  33,    2}, {   0,    0}, {  59,   60}, {  15,   21}, 
{  15,   22}, {  15,   23}, {  15,   24}, {  15,   25}, {  15,   26}, 
{   0,    0}, {  15,   27}, {  15,   28}, {  15,   29}, {  15,   30}, 
{  15,   31}, {  48,   98}, {   0,    0}, {   0,    0}, {   0,    0}, 
{  33,    3}, {   0,    0}, {   0,    0}, {  48,   98}, {  15,   33}, 
{  33,    4}, {   0,    0}, {  33,    5}, {   0,    0}, {  48,   98}, 
{  48,   98}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{  48,   98}, {  57,   91}, {  48,   98}, {   0,    0}, {  48,   98}, 
{  48,   98}, {  48,   98}, {  48,   98}, {  57,   91}, {  48,   98}, 
{   0,    0}, {  48,   98}, {   0,    0}, {   0,    0}, {  57,   91}, 
{  57,   91}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {  57,   91}, {   0,    0}, {  57,   91}, 
{  57,   91}, {  57,   91}, {  57,   91}, {   0,    0}, {  57,   91}, 
{   0,    0}, {  57,   91}, {  12,   65}, {  12,   66}, {  12,    9}, 
{   0,    0}, {  12,   67}, {  12,   10}, {   0,    0}, {  12,   11}, 
{  12,   12}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {  12,   13}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, 
};
static	yytNComb	yyNComb		[yyNTableMax - yyLastTerminal] = {
{   0,    0}, {   0,    0}, {  60,   61}, {  60,   72}, {   0,    0}, 
{  16,   34}, {  16,   35}, {  16,   36}, {   1,    6}, {   1,    7}, 
{  19,   37}, {  53,   58}, {  32,   49}, {  33,   50}, {  26,   43}, 
{  13,   99}, {  11,   92}, {  10,   20}, {  51,   56}, {  21,   38}, 
{  22,   39}, {  27,   44}, {  23,   40}, {  49,   55}, {  12,   93}, 
{  24,   41}, {  61,   80}, {  17,   73}, {  25,   42}, {   3,   14}, 
{   4,   15}, {  54,   59}, {  52,   57}, {   8,   18}, {  31,   48}, 
{  30,   47}, {  29,   46}, {  28,   45}, {   0,    0}, {   0,    0}, 
};
static	yytComb *	yyTBasePtr	[yyLastReadState + 1] = { 0,
& yyTComb [   0], & yyTComb [   0], & yyTComb [   0], & yyTComb [   0], 
& yyTComb [  14], & yyTComb [   1], & yyTComb [  29], & yyTComb [   0], 
& yyTComb [   0], & yyTComb [   0], & yyTComb [   0], & yyTComb [ 376], 
& yyTComb [   0], & yyTComb [  33], & yyTComb [ 306], & yyTComb [  40], 
& yyTComb [   0], & yyTComb [ 202], & yyTComb [   0], & yyTComb [ 278], 
& yyTComb [   0], & yyTComb [   0], & yyTComb [   0], & yyTComb [   0], 
& yyTComb [   0], & yyTComb [   0], & yyTComb [   0], & yyTComb [   0], 
& yyTComb [   0], & yyTComb [   0], & yyTComb [   0], & yyTComb [   0], 
& yyTComb [ 308], & yyTComb [  53], & yyTComb [  15], & yyTComb [  28], 
& yyTComb [  32], & yyTComb [ 135], & yyTComb [ 108], & yyTComb [  81], 
& yyTComb [  27], & yyTComb [  54], & yyTComb [ 265], & yyTComb [ 222], 
& yyTComb [ 155], & yyTComb [ 175], & yyTComb [ 242], & yyTComb [ 326], 
& yyTComb [   0], & yyTComb [  84], & yyTComb [   0], & yyTComb [   0], 
& yyTComb [   0], & yyTComb [   0], & yyTComb [  32], & yyTComb [  80], 
& yyTComb [ 346], & yyTComb [  40], & yyTComb [ 290], & yyTComb [   0], 
& yyTComb [   7], 
};
static	yytNComb *	yyNBasePtr	[yyLastReadState + 1] = { 0,
& yyNComb [ -25], & yyNComb [ -32], & yyNComb [  -8], & yyNComb [  -7], 
& yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], & yyNComb [  -4], 
& yyNComb [ -32], & yyNComb [ -20], & yyNComb [ -21], & yyNComb [ -13], 
& yyNComb [ -22], & yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], 
& yyNComb [  -8], & yyNComb [ -32], & yyNComb [ -28], & yyNComb [ -32], 
& yyNComb [ -18], & yyNComb [ -17], & yyNComb [ -15], & yyNComb [ -12], 
& yyNComb [  -9], & yyNComb [ -23], & yyNComb [ -16], & yyNComb [   0], 
& yyNComb [  -1], & yyNComb [  -2], & yyNComb [  -3], & yyNComb [ -22], 
& yyNComb [ -21], & yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], 
& yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], 
& yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], 
& yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], 
& yyNComb [ -13], & yyNComb [ -32], & yyNComb [ -19], & yyNComb [  -5], 
& yyNComb [ -23], & yyNComb [  -6], & yyNComb [ -32], & yyNComb [ -32], 
& yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], & yyNComb [ -32], 
& yyNComb [ -10], 
};
# ifdef YYTDefault
static	unsigned short	yyTDefault	[yyLastReadState + 1] = { 0,
   33,     0,    12,    12,     0,     0,     0,    12,     0,    12, 
   12,     0,    12,    59,     0,    12,    33,     0,    16,     0, 
   12,    12,    12,    12,    12,    12,    12,    12,    12,    12, 
   12,    33,     0,    20,     0,     0,     0,    57,    38,    38, 
   38,    38,     0,    57,    57,    57,    57,    57,    61,     0, 
   12,    12,    33,    12,     0,    34,    18,    50,     0,    33, 
   50, 
};
# endif
# ifdef YYNDefault
static	unsigned short	yyNDefault	[yyLastReadState + 1] = { 0,
   60,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,    16,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,    60,    60,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,    60,     0,     0,     0,     0,     0,     0,     0, 
    0, 
};
# endif
# if ! defined NO_RECOVER | defined YYDEC_TABLE | defined YYCSTree
static	unsigned char	yyLength	[yyLastReduceState - yyFirstReduceState
							+ 1] = {
    2,     1,     1,     3,     3,     6,     5,     4,     0,     2, 
    5,     1,     1,     1,     1,     3,     3,     3,     3,     3, 
    3,     5,     2,     2,     3,     3,     3,     3,     3,     2, 
    4,     0,     1,     3,     1,     3, 
};
# endif
# if ! defined NO_RECOVER | defined YYDEC_TABLE
static	yytNonterminal	yyLeftHandSide	[yyLastReduceState - yyFirstReduceState
							+ 1] = {
yyNT0_intern,
yyNTroot,
yyNTstmt_l,
yyNTstmt_l,
yyNTstmt,
yyNTstmt,
yyNTstmt,
yyNTstmt,
yyNTelseif_l,
yyNTelseif_l,
yyNTelseif_l,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr,
yyNTexpr_l,
yyNTexpr_l,
yyNTexpr_l,
yyNTexprs,
yyNTexprs,
};
# endif
# ifndef NO_RECOVER
static	yySymbolRange	yyContinuation	[yyLastReadState + 1] = { 0,
   29,     4,     3,     3,     6,     0,     0,     3,     0,     3, 
    3,     3,     3,    23,    28,     7,    29,     0,     7,     7, 
    3,     3,     3,     3,     3,     3,     3,     3,     3,     3, 
    3,    29,    29,     7,     7,    21,     7,     0,     0,     0, 
    0,     0,    14,     0,     0,     0,     0,     0,    26,    26, 
    3,     3,    29,     3,    26,     7,     0,    26,    23,    29, 
   26, 
};
static	unsigned short	yyCondition	[yyLastState - yyLastReduceState + 1] =
{ 0,
};
# endif
static	unsigned short	yyFinalToProd	[yyLastReadReduceState -
						yyFirstReadReduceState + 2] = {
   75,    76,    77,    81,    82,    83,    85,   100, 
0
};
static	unsigned short	yyStartLine	[yyLastStopState - yyFirstReduceState
							+ 2] = { 0,
113,
};
# ifdef YYaccDefault

static	unsigned long *	yyDefaultLook	[yyLastReadState + 1] = { 0,
};
# endif


static	int	yyParse		ARGS ((yyStateRange, yySymbolRange, int));

# ifndef NO_RECOVER
static	yyStateRange yyNext	ARGS ((yyStateRange, yySymbolRange));
#  ifdef YYDEBUG
static	int	yyErrorRecovery	ARGS ((yySymbolRange, yySymbolRange *, long));
#  else
static	int	yyErrorRecovery	ARGS ((yySymbolRange, long));
#  endif
static	void	yyComputeContinuation	ARGS ((long, tSet *));
static	rbool	yyIsContinuation	ARGS ((yySymbolRange, long));
static	void	yyComputeRestartPoints	ARGS ((long, tSet *));
# endif

# if defined YYTrialParse | defined YYReParse | defined YYGetLook

# ifndef yyInitBufferSize
#  define yyInitBufferSize 100
# endif

typedef struct { yySymbolRange	yyToken;
		 expr_scan_tScanAttribute	yyAttribute;
# ifdef YYMemoParse
		 short		yyStart;
# endif
	       } yytBuffer;

static yytBuffer *	yyBuffer	= NULL;
static unsigned long	yyBufferSize	= yyInitBufferSize;
static long		yyBufferNext	= 1;
static long		yyBufferLast	= 1;
static rbool		yyBufferClear	= rtrue;
static unsigned short	yyParseLevel	= 0;

static void yyBufferSet
# ifdef HAVE_ARGS
   (yySymbolRange yyToken)
# else
   (yyToken) yySymbolRange yyToken;
# endif
{
   if (yyBufferNext == yyBufferLast) {
      if (yyBufferClear) yyBufferLast = 0;
      if (++ yyBufferLast >= (long) yyBufferSize) {
	 yyExtendArray ((char * *) & yyBuffer, & yyBufferSize,
			  (unsigned long) sizeof (yytBuffer));
# ifdef YYDEBUG
	 if (expr_pars_Debug) {
	    yyPrintState (0);
	    fprintf (yyTrace, "extend  token buffer from %ld to %ld",
		yyBufferSize / 2, yyBufferSize); yyNl ();
	 }
# endif
      }
      yyBuffer [yyBufferLast].yyToken	= yyToken;
      yyBuffer [yyBufferLast].yyAttribute= expr_scan_Attribute;
# ifdef YYMemoParse
      yyBuffer [yyBufferLast].yyStart	= 0;
# endif
      yyBufferNext = yyBufferLast;
   }
}

static int yyGetToken ARGS ((void))
{
   register yySymbolRange yyToken;

   if (yyBufferNext < yyBufferLast) {
      yyToken = yyBuffer [++ yyBufferNext].yyToken;
      expr_scan_Attribute = yyBuffer [yyBufferNext].yyAttribute;
   } else {
      yyToken = expr_scan_GetToken ();
      if ((yytrial | yybuffer) & yyControl.yyMode) {
	 if (++ yyBufferLast >= (long) yyBufferSize) {
	    yyExtendArray ((char * *) & yyBuffer, & yyBufferSize,
			     (unsigned long) sizeof (yytBuffer));
# ifdef YYDEBUG
	    if (expr_pars_Debug) {
	       yyPrintState (0);
	       fprintf (yyTrace, "extend  token buffer from %ld to %ld",
		  yyBufferSize / 2, yyBufferSize); yyNl ();
	    }
# endif
	 }
	 yyBuffer [yyBufferLast].yyToken = yyToken;
	 yyBuffer [yyBufferLast].yyAttribute = expr_scan_Attribute;
# ifdef YYMemoParse
	 yyBuffer [yyBufferLast].yyStart = 0;
# endif
	 yyBufferNext = yyBufferLast;
      }
   }
# ifdef TOKENOP
   TOKENOP
# endif
   return yyToken;
}

# else
# define yyGetToken expr_scan_GetToken
# endif

# ifdef YYGetLook

static int yyGetLookahead
# ifdef HAVE_ARGS
   (int yyk, yySymbolRange yyToken)
# else
   (yyk, yyToken) int yyk; yySymbolRange yyToken;
# endif
{
   if (yyk == 0) return yyToken;
   if (yyControl.yyMode == yystandard) yyBufferSet (yyToken);
   while (yyBufferNext + yyk > yyBufferLast) {
      if (yyBufferNext < yyBufferLast &&
	 yyBuffer [yyBufferLast].yyToken == expr_scan_EofToken)
	 return expr_scan_EofToken;
      if (++ yyBufferLast >= (long) yyBufferSize) {
	 yyExtendArray ((char * *) & yyBuffer, & yyBufferSize,
			  (unsigned long) sizeof (yytBuffer));
# ifdef YYDEBUG
	 if (expr_pars_Debug) {
	    yyPrintState (0);
	    fprintf (yyTrace, "extend  token buffer from %ld to %ld",
		yyBufferSize / 2, yyBufferSize); yyNl ();
	 }
# endif
      }
      yyBuffer [yyBufferLast].yyToken = expr_scan_GetToken ();
      yyBuffer [yyBufferLast].yyAttribute = expr_scan_Attribute;
# ifdef YYMemoParse
      yyBuffer [yyBufferLast].yyStart = 0;
# endif
   }
   expr_scan_Attribute = yyBuffer [yyBufferNext].yyAttribute;
   return yyBuffer [yyBufferNext + yyk].yyToken;
}

static void xxGetAttribute
# ifdef HAVE_ARGS
   (int yyk, yySymbolRange yyToken, expr_scan_tScanAttribute * yyAttribute)
# else
   (yyk, yyToken, yyAttribute)
   int yyk; yySymbolRange yyToken; expr_scan_tScanAttribute * yyAttribute;
# endif
{
   if (yyk == 0) * yyAttribute = expr_scan_Attribute;
   else {
      yyGetLookahead (yyk, yyToken);
      * yyAttribute =
	 yyBuffer [Min (yyBufferNext + yyk, yyBufferLast)].yyAttribute;
   }
}

# endif

# ifdef YYReParse

#  define BufferOn(Actions, Messages) yyBufferOn (Actions, Messages, yyTerminal)
#  define BufferPosition yyBufferNext

static yytControl yyPrevControl;

static long yyBufferOn
# ifdef HAVE_ARGS
   (rbool yyActions, rbool yyMessages, yySymbolRange yyToken)
# else
   (yyActions, yyMessages, yyToken)
   rbool yyActions, yyMessages; yySymbolRange yyToken;
# endif
{
   if (yyControl.yyMode == yystandard) {
      yyPrevControl		= yyControl;
      yyControl.yyMode		= yybuffer;
      yyControl.yyActions	= yyActions;
      yyControl.yyMessages	= yyMessages;
      yyBufferSet (yyToken);
      yyBufferClear		= rfalse;
   }
   return yyBufferNext;
}

static long BufferOff ARGS ((void))
{
   if (yyControl.yyMode == yybuffer) yyControl = yyPrevControl;
   return yyBufferNext;
}

static void BufferClear ARGS ((void))
{
   yyBufferClear = rtrue;
}

# endif

# if defined YYDEBUG | defined YYDCRP

static void yyNl ARGS ((void)) { putc ('\n', yyTrace); fflush (yyTrace); }

# endif

# ifdef YYDEBUG

static void yyPrintState
# ifdef HAVE_ARGS
   (yyStateRange yyState)
# else
   (yyState) yyStateRange yyState;
# endif
{
   fprintf (yyTrace, "%4ld:", ++ yyCount);
   WritePosition  (yyTrace, expr_scan_Attribute.Position);
   fprintf (yyTrace, ":%5d  %c  ", yyState, " ST-B---R" [yyControl.yyMode]);
# if defined YYTrialParse | defined YYReParse
   if (yyParseLevel > 0) {
      register int yyi = yyParseLevel;
      fprintf (yyTrace, "%2d  ", yyi);
      do fputs ("  ", yyTrace); while (-- yyi);
   } else
# endif
   fputs ("    ", yyTrace);
}

static rbool yyPrintResult
# ifdef HAVE_ARGS
   (yyStateRange yyState, int yyLine, rbool yyCondition)
# else
   (yyState, yyLine, yyCondition)
   yyStateRange	yyState;
   int		yyLine;
   rbool	yyCondition;
# endif
{
   if (expr_pars_Debug) {
      yyPrintState (yyState);
      fprintf (yyTrace, "check   predicate in line %d, result = %d",
	 yyLine, yyCondition); yyNl ();
   }
   return yyCondition;
}

# else
#  define yyPrintResult(State, Line, Condition) Condition
# endif

# if defined YYDEBUG | defined YYDEC_TABLE
#  define yyGotoReduce(State, Rule)	{ yyState = State; goto yyReduce; }
#  define yyGotoRead(State)		{ yyState = State; goto yyRead; }
# else
#  define yyGotoReduce(State, Rule)	goto Rule;
#  define yyGotoRead(State)		{ yyState = State; goto yyRead; }
# endif

static unsigned long	yyStateStackSize	= yyInitStackSize;
static yyStateRange *	yyStateStack		= NULL;
static yyStateRange *	yyEndOfStack		;
static unsigned long	yyAttrStackSize		= yyInitStackSize;
static tParsAttribute * yyAttributeStack	= NULL;
# if defined YYTrialParse | defined YYReParse
static yyStateRange *	yyStateStackPtr		;
static tParsAttribute * yyAttrStackPtr		;
# endif
# ifndef NO_RECOVER
static yyStateRange *	yyIsContStackPtr	= NULL;
static unsigned long	yyIsContStackSize	= yyInitStackSize;
static yyStateRange *	yyCompResStackPtr	= NULL;
static unsigned long	yyCompResStackSize	= yyInitStackSize;
# endif

void Resetexpr_pars ARGS ((void))
   {
      if (yyStateStack) {
	 ReleaseArray ((char * *) & yyStateStack, & yyStateStackSize,
			(unsigned long) sizeof (yyStateRange));
	 yyStateStack = NULL;
      }
      if (yyAttributeStack) {
	 ReleaseArray ((char * *) & yyAttributeStack, & yyAttrStackSize,
			(unsigned long) sizeof (tParsAttribute));
	 yyAttributeStack = NULL;
      }
# ifndef NO_RECOVER
      if (yyIsContStackPtr) {
	 ReleaseArray ((char * *) & yyIsContStackPtr, & yyIsContStackSize,
			(unsigned long) sizeof (yyStateRange));
	 yyIsContStackPtr = NULL;
      }
      if (yyCompResStackPtr) {
	 ReleaseArray ((char * *) & yyCompResStackPtr, & yyCompResStackSize,
			(unsigned long) sizeof (yyStateRange));
	 yyCompResStackPtr = NULL;
      }
# endif
# if defined YYTrialParse | defined YYReParse | defined YYGetLook
      if (yyBuffer) {
	 ReleaseArray ((char * *) & yyBuffer, & yyBufferSize,
			(unsigned long) sizeof (yytBuffer));
	 yyBuffer = NULL;
      }
# endif
   }

int expr_pars ARGS ((void))
   {
      return expr_pars2 (yyStartState);
   }

int expr_pars2
# ifdef HAVE_ARGS
   (int yyStartSymbol)
# else
   (yyStartSymbol) int yyStartSymbol;
# endif
   {
      int		yyErrorCount;
# if defined YYDEBUG | defined YYDCRP
      yyTrace		= stdout;
# endif
      Beginexpr_pars ();
      yyStateStackSize	= yyInitStackSize;
      yyMakeArray ((char * *) & yyStateStack, & yyStateStackSize,
		     (unsigned long) sizeof (yyStateRange));
      yyAttrStackSize	= yyInitStackSize;
      yyMakeArray ((char * *) & yyAttributeStack, & yyAttrStackSize,
		     (unsigned long) sizeof (tParsAttribute));
# ifndef NO_RECOVER
      yyIsContStackSize	= yyInitStackSize;
      yyMakeArray ((char * *) & yyIsContStackPtr, & yyIsContStackSize,
		     (unsigned long) sizeof (yyStateRange));
      yyCompResStackSize= yyInitStackSize;
      yyMakeArray ((char * *) & yyCompResStackPtr, & yyCompResStackSize,
		     (unsigned long) sizeof (yyStateRange));
# endif
# if defined YYTrialParse | defined YYReParse | defined YYGetLook
      yyBufferSize	= yyInitBufferSize;
      yyMakeArray ((char * *) & yyBuffer, & yyBufferSize,
		     (unsigned long) sizeof (yytBuffer));
# endif
      yyEndOfStack	= & yyStateStack [yyStateStackSize - 1];
# if defined YYTrialParse | defined YYReParse
      yyStateStackPtr	= yyStateStack;
      yyAttrStackPtr	= yyAttributeStack;
      yyBufferNext	= 1;
      yyBufferLast	= 1;
      yyBufferClear	= rtrue;
      yyParseLevel	= 0;
# endif
# ifdef YYDEBUG
      if (expr_pars_Debug) {
	 yyCount = 0;
	 fprintf (yyTrace,
      "  # |Position|State|Mod|Lev|Action |Terminal and Lookahead or Rule\n");
	 yyNl ();
      }
# endif
      yyControl.yyMode		= yystandard;
      yyControl.yyActions	= rtrue;
      yyControl.yyMessages	= rtrue;
      yyErrorCount = yyParse ((yyStateRange) yyStartSymbol,
	 (yySymbolRange) yyGetToken (), (int) yyStartLine [yyStartSymbol]);
      Resetexpr_pars ();
      return yyErrorCount;
   }

# ifdef YYTrialParse

# ifdef YYMemoParse
#  define MemoryClear(Position) yyBuffer [Position].yyStart = 0
# endif

static int yyTrialParse
# ifdef HAVE_ARGS
   (yyStateRange yyStartSymbol, yySymbolRange yyToken, int yyLine)
# else
   (yyStartSymbol, yyToken, yyLine)
   yyStateRange		yyStartSymbol	;
   yySymbolRange	yyToken		;
   int			yyLine		;
# endif
   {
      int	yyErrorCount		;
      ptrdiff_t	yyPrevStateStackPtr	= yyStateStackPtr - yyStateStack;
      ptrdiff_t	yyPrevAttrStackPtr	= yyAttrStackPtr - yyAttributeStack;
      long	yyPrevBufferNext	;
      yytControl yyPrevControl		;

# ifdef BEFORE_TRIAL
      BEFORE_TRIAL
# endif
# ifdef YYMemoParse
      if (yyBuffer [yyBufferNext].yyStart ==   yyStartSymbol) return 0;
      if (yyBuffer [yyBufferNext].yyStart == - yyStartSymbol) return 1;
# endif
      yyPrevControl		= yyControl;
      yyStateStackPtr		++;
      yyAttrStackPtr		++;
      yyParseLevel		++;
      if (yyControl.yyMode == yystandard) yyBufferSet (yyToken);
      yyPrevBufferNext		= yyBufferNext;
      yyControl.yyMode		= yytrial;
      yyControl.yyActions	= rfalse;
      yyControl.yyMessages	= rfalse;
      yyErrorCount		= yyParse (yyStartSymbol, yyToken, yyLine);
# ifdef YYMemoParse
      yyBuffer [yyPrevBufferNext].yyStart = yyErrorCount ?
					- yyStartSymbol : yyStartSymbol;
# endif
      yyStateStackPtr		= yyStateStack + yyPrevStateStackPtr;
      yyAttrStackPtr		= yyAttributeStack + yyPrevAttrStackPtr;
      yyBufferNext		= yyPrevBufferNext;
      yyControl			= yyPrevControl;
      yyParseLevel		--;
      expr_scan_Attribute		= yyBuffer [yyBufferNext].yyAttribute;
# ifdef AFTER_TRIAL
      AFTER_TRIAL
# endif
      return yyErrorCount;
   }

# endif

# ifdef YYReParse

static int ReParse
# ifdef HAVE_ARGS
   (yyStateRange yyStartSymbol, int yyFrom, int yyTo, rbool yyActions,
      rbool yyMessages)
# else
   (yyStartSymbol, yyFrom, yyTo, yyActions, yyMessages)
   yyStateRange	yyStartSymbol		;
   int		yyFrom, yyTo		;
   rbool	yyActions, yyMessages	;
# endif
   {
      int yyErrorCount = 1;

      if (1 <= yyFrom && yyFrom <= yyTo && yyTo <= yyBufferLast) {
	 ptrdiff_t yyPrevStateStackPtr	= yyStateStackPtr - yyStateStack;
	 ptrdiff_t yyPrevAttrStackPtr	= yyAttrStackPtr - yyAttributeStack;
	 long	yyPrevBufferNext	= yyBufferNext;
	 int	yyToToken		= yyBuffer [yyTo].yyToken;
	 yytControl yyPrevControl	;

	 yyPrevControl		= yyControl;
	 yyStateStackPtr	++;
	 yyAttrStackPtr		++;
	 yyParseLevel		++;
	 yyBufferNext		= yyFrom - 1;
	 yyBuffer [yyTo].yyToken= expr_scan_EofToken;
	 yyControl.yyMode	= yyreparse;
	 yyControl.yyActions	= yyActions;
	 yyControl.yyMessages	= yyMessages;
	 yyErrorCount		= yyParse (yyStartSymbol,
	    (yySymbolRange) yyGetToken (), (int) yyStartLine [yyStartSymbol]);
	 yyStateStackPtr	= yyStateStack + yyPrevStateStackPtr;
	 yyAttrStackPtr		= yyAttributeStack + yyPrevAttrStackPtr;
	 yyBufferNext		= yyPrevBufferNext;
	 yyControl		= yyPrevControl;
	 yyParseLevel		--;
	 yyBuffer [yyTo].yyToken= yyToToken;
	 expr_scan_Attribute		= yyBuffer [yyBufferNext].yyAttribute;
      } else {
      ErrorMessage (xxInvalidCallOfReParse, xxError, expr_scan_Attribute.Position);
      }
      return yyErrorCount;
   }

# endif

static char * yyGetTokenName
# ifdef HAVE_ARGS
   (yySymbolRange yyTerminal)
# else
   (yyTerminal) yySymbolRange yyTerminal;
# endif
   {
      if (yyTerminal <= yyLastTerminal && expr_pars_TokenName [yyTerminal])
	 return expr_pars_TokenName [yyTerminal];
      else
	 return "_unknown_";
   }

static void yyExtendStack
# ifdef HAVE_ARGS
   (yyStateRange * *	yyStateStackPtr,
    tParsAttribute * *	yyAttrStackPtr,
    yyStateRange	yyState)
# else
   (yyStateStackPtr, yyAttrStackPtr, yyState)
   yyStateRange * *	yyStateStackPtr;
   tParsAttribute * *	yyAttrStackPtr;
   yyStateRange		yyState;
# endif
   {
      ptrdiff_t yyyStateStackPtr = * yyStateStackPtr - yyStateStack;
      ptrdiff_t yyyAttrStackPtr = * yyAttrStackPtr - yyAttributeStack;
      yyExtendArray ((char * *) & yyStateStack, & yyStateStackSize,
		       (unsigned long) sizeof (yyStateRange));
      yyExtendArray ((char * *) & yyAttributeStack, & yyAttrStackSize,
		       (unsigned long) sizeof (tParsAttribute));
      * yyStateStackPtr	= yyStateStack + yyyStateStackPtr;
      * yyAttrStackPtr	= yyAttributeStack + yyyAttrStackPtr;
      yyEndOfStack	= & yyStateStack [yyStateStackSize - 1];
# ifdef YYDEBUG
      if (expr_pars_Debug) {
	 yyPrintState (yyState);
	 fprintf (yyTrace, "extend  stack from %ld to %ld",
	    yyStateStackSize / 2, yyStateStackSize); yyNl ();
      }
# endif
   }

static int yyParse
# ifdef HAVE_ARGS
   (yyStateRange yyStartSymbol, yySymbolRange yyToken, int yyLine)
# else
   (yyStartSymbol, yyToken, yyLine)
   yyStateRange		yyStartSymbol	;
   yySymbolRange	yyToken		;
   int			yyLine		;
# endif
   {
      register	yyStateRange	yyState		= yyStartSymbol;
      register	yySymbolRange	yyTerminal	= yyToken;
      register	rbool		yyIsRepairing	= rfalse;
		tParsAttribute	yySynAttribute	;   /* synthesized attribute */
		int		yyErrorCount	= 0;
# if ! (defined YYTrialParse | defined YYReParse)
		yyStateRange *	yyStateStackPtr	= yyStateStack;
		tParsAttribute *yyAttrStackPtr	= yyAttributeStack;
# endif
# ifdef YYDEBUG
		long		yyStartCount	= yyCount + 1;
		yySymbolRange	yyPrevTerminal	= yyToken;
# endif
# ifdef YYGetLook
		yySymbolRange	yy2;
# endif

/* line 57 "expr_pars.lrk" */


/* line 1066 "expr_pars.c" */

# ifdef YYDEBUG
      if (expr_pars_Debug) {
	 yyPrintState (yyStartSymbol);
	 fprintf (yyTrace, "parse   for predicate in line %d, lookahead: %s",
	    yyLine, yyGetTokenName (yyTerminal)); yyNl ();
      }
# endif

      memset (& yySynAttribute, 0, sizeof yySynAttribute);

      for (;;) {
	 if (yyStateStackPtr >= yyEndOfStack) {
	    yyExtendStack (& yyStateStackPtr, & yyAttrStackPtr, yyState);
	 }
	 * yyStateStackPtr = yyState;

	 for (;;) { /* SPEC State = Next (State, Terminal); terminal transit */
	    register yytComb * yyTCombPtr = yyTBasePtr [yyState] + yyTerminal;
# if defined YYTDefault & defined YYaccDefault
	    register unsigned long * yylp;
# endif
	    if (yyTCombPtr->Check == yyState) {
	       yyState = yyTCombPtr->Next; break;
	    }
# ifdef YYTDefault
#  ifdef YYaccDefault
	    if ((yylp = yyDefaultLook [yyState]) &&
	       (yylp [yyTerminal >> 5] >> (yyTerminal & 0x1f)) & 1) {
	       yyState = yyTDefault [yyState]; break;
	    }
	    yyState = yyNoState; break;
#  else
	    if ((yyState = yyTDefault [yyState]) == yyNoState) break;
#  endif
# endif
	 }

	 if (yyState == yyNoState ||			/* syntax error ? */
	    yyIsRepairing && yyState >= yyFirstReduceState) { /* repair mode */
	    yySymbolRange yyRepairToken;

	    if (yyState == yyNoState && ! yyIsRepairing) { /* syntax error */
# ifdef ERROR
	       for (;;) {		/* be compatible with error trick */
		  yySymbolRange yyyTerminal = (yySymbolRange) yyTerminal;
		  ERROR
		  goto yyRecover;
	       }
	       goto yyFinal;
   yyRecover:
# endif
# ifdef ERROR2
	       ERROR2
# endif
# ifdef YYTrialParse
	       if (yyControl.yyMode == yytrial) YYABORT;
# endif
# ifndef NO_RECOVER
	       yyErrorCount ++;				/* report and recover */
	       yyTerminal = yyErrorRecovery (yyTerminal,
#  ifdef YYDEBUG
			& yyPrevTerminal,
#  endif
			(long) (yyStateStackPtr - yyStateStack));
	       yyIsRepairing = rtrue;
	       yyState = * yyStateStackPtr;
	       continue;
# else
	       YYABORT;
# endif
	    }

# ifndef NO_RECOVER
	/* SPEC State = Next (Top (), Continuation [yyState]); repair transit */
	    yyState = * yyStateStackPtr;
	    yyRepairToken = yyContinuation [yyState];	/* repair */
	    yyState = yyNext (yyState, yyRepairToken);
	    if (yyState > yyLastReduceState) {		/* dynamic ? */
	       yyState = yyCondition [yyState - yyLastReduceState];
	    }
	    if (yyState <= yyLastReadReduceState) { /* read or read reduce ? */
	       expr_scan_tScanAttribute yyRepairAttribute;
	       expr_scan_ErrorAttribute ((int) yyRepairToken, & yyRepairAttribute);
	       if (yyControl.yyMessages)
		  ErrorMessageI (xxTokenInserted, xxRepair,
		     expr_scan_Attribute.Position, xxString,
		     yyGetTokenName (yyRepairToken));
#  ifdef YYDEBUG
	       if (expr_pars_Debug) {
		  yyPrintState (* yyStateStackPtr);
		  fprintf (yyTrace, "insert  %s",
		     yyGetTokenName (yyRepairToken)); yyNl ();
		  yyPrintState (* yyStateStackPtr);
		  fprintf (yyTrace, "shift   %s, lookahead: %s",
		     yyGetTokenName (yyRepairToken),
		     yyGetTokenName (yyTerminal)); yyNl ();
	       }
#  endif
	       if (yyStateStackPtr >= yyEndOfStack) {
		  yyExtendStack (& yyStateStackPtr, & yyAttrStackPtr, yyState);
	       }
	       yyStateStackPtr ++;
	       yyGetAttribute (yyAttrStackPtr ++, yyRepairAttribute);
	       if (yyState >= yyFirstFinalState) {	/* read reduce */
		  * yyStateStackPtr = yyStateStackPtr [-1];
		  yyState = yyFinalToProd [yyState - yyFirstReadReduceState];
	       } else {					/* read */
		  * yyStateStackPtr = yyState;
	       }
	    }
	    if (yyState <= yyLastReadState) continue;	/* read ? */
# endif
	 }

   yyFinal:
	 if (yyState >= yyFirstFinalState) {		/* final state ? */
	    if (yyState <= yyLastReadReduceState) {	/* read reduce ? */
	       yyStateStackPtr ++;
	       yyGetAttribute (yyAttrStackPtr ++, expr_scan_Attribute);
	       yyTerminal = yyGetToken ();
# ifdef YYDEBUG
	       if (expr_pars_Debug) {
		  yyStateStackPtr [0] = yyStateStackPtr [-1];
		  yyPrintState (* yyStateStackPtr);
		  fprintf (yyTrace, "shift   %s, lookahead: %s",
		     yyGetTokenName (yyPrevTerminal),
		     yyGetTokenName (yyTerminal)); yyNl ();
		  yyPrevTerminal = yyTerminal;
	       }
# endif
	       yyIsRepairing = rfalse;
	    }

	    for (;;) {
	       register yytNonterminal yyNonterminal;	/* left-hand side */

   yyReduce:
# ifdef YYDEBUG
	       if (expr_pars_Debug) {
		  if (yyState <= yyLastReadReduceState)	/* read reduce ? */
		     yyState = yyFinalToProd [yyState - yyFirstReadReduceState];
		  yyPrintState (* yyStateStackPtr);
		  if (yyState <= yyLastReduceState) {
		     fprintf (yyTrace, "reduce  %s",
			yyRule [yyState - yyLastReadReduceState]); yyNl ();
		  } else {
		     fprintf (yyTrace, "dynamic decision %d",
			yyState - yyLastReduceState); yyNl ();
		  }
	       }
# endif
# ifdef YYCSTree
	       if (yyControl.yyActions) {
		 yyStateRange yystate = yyState;
		 if (yystate <= yyLastReadReduceState) { /* read reduce ? */
		   yystate = yyFinalToProd [yystate - yyFirstReadReduceState];
		 }
		 if (yystate <= yyLastStopState) {		/* accept */
		   CSTree = NewNonterminal (yystate - yyLastReadReduceState,
		     yyAttrStackPtr [-1].Common.Tree);
		 } else if (yystate <= yyLastReduceState) {	/* reduce */
		   int yyrule = yystate - yyLastReadReduceState;
		   int yyleng = yyLength [yyrule - 1], i;
		   tCSTree yynode = NULL, yynext = NULL;
		   for (i = yyleng - 1; i >= 0; i --) {
		     unsigned short yysymbol = yyRules [yyrule] [i];
		     tParsAttribute * yyap = & yyAttrStackPtr [i - yyleng];
		     if (yysymbol < yyEpsilon) {		/* terminal */
		       yynode = NewTerminal (yyap->Scan.Position,
			 StGetCStr (yyap->Scan.Common.Text));
		     } else {					/* nonterminal*/
		       yynode = yyap->Common.Tree;
		     }
		     yynode->Next = yynext;
		     if (yynext) yynext->Previous = yynode;
		     yynext = yynode;
		   }
		   yySynAttribute.Common.Tree = NewNonterminal (yyrule, yynode);
		 }
	       }
# endif
# ifdef YYDEC_TABLE
	       if (yyLastStopState < yyState && yyState <= yyLastReduceState) {
		  register int yyd = yyLength [yyState - yyFirstReduceState];
		  yyStateStackPtr -= yyd;
		  yyAttrStackPtr  -= yyd;
		  yyNonterminal = yyLeftHandSide [yyState - yyFirstReduceState];
	       }
# endif
switch (yyState) {
case 70:
YYACCEPT;
case 71: /* root : stmt_l */
yyDecrement (1) yySetNT (yyNTroot) {
/* line 113 "expr_pars.lrk" */

/* line 55 "expr.pars" */
{  TreeRoot = ReverseTree (yyA [0].stmt_l.tree);; }
/* line 1266 "expr_pars.c" */
} break;
case 72: /* stmt_l : stmt */
yyDecrement (1) yySetNT (yyNTstmt_l) {
/* line 59 "expr.pars" */

yyS.stmt_l.tree = set_stmt_end (yyA [0].stmt.tree);
/* line 1273 "expr_pars.c" */
} break;
case 73: /* stmt_l : stmt_l ';' stmt */
yyDecrement (3) yySetNT (yyNTstmt_l) {
/* line 62 "expr.pars" */

yyS.stmt_l.tree = set_stmt_next (yyA [2].stmt.tree, yyA [0].stmt_l.tree);
/* line 1280 "expr_pars.c" */
} break;
case 74: /* stmt : identifier ':=' expr */
yyDecrement (3) yySetNT (yyNTstmt) {
/* line 67 "expr.pars" */

yyS.stmt.tree = massign_stmt (NoTree, yyA [1].Scan.Position, mname (yyA [0].Scan.Position, yyA [0].Scan.identifier.Ident), yyA [2].expr.tree);
/* line 1287 "expr_pars.c" */
} break;
case 75:
case 62: /* stmt : IF expr THEN stmt_l elseif_l END */
yyDecrement (6) yySetNT (yyNTstmt) {
/* line 70 "expr.pars" */

yyS.stmt.tree = mif_stmt (NoTree, yyA [0].Scan.Position, yyA [1].expr.tree, ReverseTree (yyA [3].stmt_l.tree), yyA [4].elseif_l.tree);
/* line 1295 "expr_pars.c" */
} break;
case 76:
case 63: /* stmt : WHILE expr DO stmt_l END */
yyDecrement (5) yySetNT (yyNTstmt) {
/* line 73 "expr.pars" */

yyS.stmt.tree = mwhile_stmt (NoTree, yyA [0].Scan.Position, yyA [1].expr.tree, ReverseTree (yyA [3].stmt_l.tree));
/* line 1303 "expr_pars.c" */
} break;
case 77:
case 64: /* stmt : PRINT '(' expr_l ')' */
yyDecrement (4) yySetNT (yyNTstmt) {
/* line 76 "expr.pars" */

/* line 78 "expr.pars" */
yyS.stmt.tree = mprint_stmt (NoTree, yyA [0].Scan.Position, ReverseTree (yyA [2].expr_l.tree));
/* line 1312 "expr_pars.c" */
} break;
case 78: /* elseif_l : */
yySetNT (yyNTelseif_l) {
/* line 83 "expr.pars" */

yyS.elseif_l.tree = mno_stmt();
/* line 1319 "expr_pars.c" */
} break;
case 79: /* elseif_l : ELSE stmt_l */
yyDecrement (2) yySetNT (yyNTelseif_l) {
/* line 86 "expr.pars" */

yyS.elseif_l.tree = ReverseTree (yyA [1].stmt_l.tree);
/* line 1326 "expr_pars.c" */
} break;
case 80: /* elseif_l : ELSEIF expr THEN stmt_l elseif_l */
yyDecrement (5) yySetNT (yyNTelseif_l) {
/* line 89 "expr.pars" */

yyS.elseif_l.tree = mif_stmt (mno_stmt(), yyA [0].Scan.Position, yyA [1].expr.tree, ReverseTree (yyA [3].stmt_l.tree), yyA [4].elseif_l.tree);
/* line 1333 "expr_pars.c" */
} break;
case 81:
case 65: /* expr : int_const */
yyDecrement (1) yySetNT (yyNTexpr) {
/* line 95 "expr.pars" */

yyS.expr.tree = mint_const (yyA [0].Scan.Position, yyA [0].Scan.int_const.Value);
/* line 1341 "expr_pars.c" */
} break;
case 82:
case 66: /* expr : float_const */
yyDecrement (1) yySetNT (yyNTexpr) {
/* line 98 "expr.pars" */

yyS.expr.tree = mfloat_const (yyA [0].Scan.Position, yyA [0].Scan.float_const.Value);
/* line 1349 "expr_pars.c" */
} break;
case 83:
case 67: /* expr : pi */
yyDecrement (1) yySetNT (yyNTexpr) {
/* line 101 "expr.pars" */

yyS.expr.tree = mfloat_const (yyA [0].Scan.Position, 3.14159265);
/* line 1357 "expr_pars.c" */
} break;
case 84: /* expr : identifier */
yyDecrement (1) yySetNT (yyNTexpr) {
/* line 104 "expr.pars" */

yyS.expr.tree = mname (yyA [0].Scan.Position, yyA [0].Scan.identifier.Ident);
/* line 1364 "expr_pars.c" */
} break;
case 85:
case 68: /* expr : '(' expr ')' */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 107 "expr.pars" */

/* line 163 "expr_pars.lrk" */
yyS.expr.tree = yyA [1].expr.tree;

/* line 1374 "expr_pars.c" */
} break;
case 86: /* expr : expr '+' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 109 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '+', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1381 "expr_pars.c" */
} break;
case 87: /* expr : expr '-' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 113 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '-', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1388 "expr_pars.c" */
} break;
case 88: /* expr : expr '*' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 116 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '*', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1395 "expr_pars.c" */
} break;
case 89: /* expr : expr '/' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 119 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '/', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1402 "expr_pars.c" */
} break;
case 90: /* expr : expr '^' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 122 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '^',  yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1409 "expr_pars.c" */
} break;
case 91: /* expr : expr '?' expr ':' expr */
yyDecrement (5) yySetNT (yyNTexpr) {
/* line 125 "expr.pars" */

yyS.expr.tree = mcond_expr (yyA [1].Scan.Position, yyA [0].expr.tree, yyA [2].expr.tree, yyA [4].expr.tree);
/* line 1416 "expr_pars.c" */
} break;
case 92: /* expr : '+' expr */
yyDecrement (2) yySetNT (yyNTexpr) {
/* line 128 "expr.pars" */

yyS.expr.tree = munary_expr (yyA [0].Scan.Position, '+', yyA [1].expr.tree);
/* line 1423 "expr_pars.c" */
} break;
case 93: /* expr : '-' expr */
yyDecrement (2) yySetNT (yyNTexpr) {
/* line 131 "expr.pars" */

yyS.expr.tree = munary_expr (yyA [0].Scan.Position, '-', yyA [1].expr.tree);
/* line 1430 "expr_pars.c" */
} break;
case 94: /* expr : expr '>' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 134 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '>', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1437 "expr_pars.c" */
} break;
case 95: /* expr : expr '<' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 137 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '<', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1444 "expr_pars.c" */
} break;
case 96: /* expr : expr '=' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 140 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '=', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1451 "expr_pars.c" */
} break;
case 97: /* expr : expr '&' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 143 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '&', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1458 "expr_pars.c" */
} break;
case 98: /* expr : expr '|' expr */
yyDecrement (3) yySetNT (yyNTexpr) {
/* line 146 "expr.pars" */

yyS.expr.tree = mbinary_expr (yyA [1].Scan.Position, '|', yyA [0].expr.tree, yyA [2].expr.tree);
/* line 1465 "expr_pars.c" */
} break;
case 99: /* expr : '!' expr */
yyDecrement (2) yySetNT (yyNTexpr) {
/* line 149 "expr.pars" */

yyS.expr.tree = munary_expr (yyA [0].Scan.Position, '!', yyA [1].expr.tree);
/* line 1472 "expr_pars.c" */
} break;
case 100:
case 69: /* expr : identifier '(' expr_l ')' */
yyDecrement (4) yySetNT (yyNTexpr) {
/* line 152 "expr.pars" */

yyS.expr.tree = mcall_expr (yyA [0].Scan.Position, yyA [0].Scan.identifier.Ident, ReverseTree (yyA [2].expr_l.tree)); 
/* line 1480 "expr_pars.c" */
} break;
case 101: /* expr_l : */
yySetNT (yyNTexpr_l) {
/* line 158 "expr.pars" */

yyS.expr_l.tree = mno_exprs();
/* line 1487 "expr_pars.c" */
} break;
case 102: /* expr_l : expr */
yyDecrement (1) yySetNT (yyNTexpr_l) {
/* line 162 "expr.pars" */

yyS.expr_l.tree = mexprs (mno_exprs(), yyA [0].expr.tree);
/* line 1494 "expr_pars.c" */
} break;
case 103: /* expr_l : exprs ',' expr */
yyDecrement (3) yySetNT (yyNTexpr_l) {
/* line 165 "expr.pars" */

yyS.expr_l.tree = mexprs (yyA [0].expr_l.tree, yyA [2].expr.tree);
/* line 1501 "expr_pars.c" */
} break;
case 104: /* exprs : expr */
yyDecrement (1) yySetNT (yyNTexprs) {
/* line 162 "expr.pars" */

yyS.expr_l.tree = mexprs (mno_exprs(), yyA [0].expr.tree);
/* line 1508 "expr_pars.c" */
} break;
case 105: /* exprs : exprs ',' expr */
yyDecrement (3) yySetNT (yyNTexprs) {
/* line 165 "expr.pars" */

yyS.expr_l.tree = mexprs (yyA [0].expr_l.tree, yyA [2].expr.tree);
/* line 1515 "expr_pars.c" */
} break;
default: switch (yyState) {
case 1: goto yyAbort;
case 2: goto yyRead;
case 3: goto yyReduce;
}
}

	/* SPEC State = Next (Top (), Nonterminal); nonterminal transition */
# ifdef YYNDefault
	       yyState = * yyStateStackPtr ++;
	       for (;;) {
		  register yytComb * yyNCombPtr =
				yyNBasePtr [yyState] + (int) yyNonterminal;
		  if (yyNCombPtr->Check == yyState) {
		     yyState = yyNCombPtr->Next; break;
		  }
		  yyState = yyNDefault [yyState];
	       }
# else
	       yyState = yyNBasePtr [* yyStateStackPtr ++] [yyNonterminal];
# endif
	       * yyAttrStackPtr ++ = yySynAttribute;
	       if (yyState < yyFirstFinalState) break;	/* read nonterminal ? */
# ifdef YYDEBUG
	       yyStateStackPtr [0] = yyStateStackPtr [-1];
# endif
	    }

	 } else {					/* read */
   yyRead:  yyStateStackPtr ++;
	    yyGetAttribute (yyAttrStackPtr ++, expr_scan_Attribute);
	    yyTerminal = yyGetToken ();
# ifdef YYDEBUG
	    if (expr_pars_Debug) {
	       yyPrintState (yyStateStackPtr [-1]);
	       fprintf (yyTrace, "shift   %s, lookahead: %s",
		  yyGetTokenName (yyPrevTerminal),
		  yyGetTokenName (yyTerminal)); yyNl ();
	       yyPrevTerminal = yyTerminal;
	    }
# endif
	    yyIsRepairing = rfalse;
	 }
      }

   yyAbort:
# ifdef YYDEBUG
      if (expr_pars_Debug) {
	 yyPrintState (* yyStateStackPtr);
	 fprintf (yyTrace, "fail    parse started at %ld", yyStartCount);
	 yyNl ();
      }
# endif
      return ++ yyErrorCount;

   yyAccept:
# ifdef YYDEBUG
      if (expr_pars_Debug) {
	 yyPrintState (* yyStateStackPtr);
	 fprintf (yyTrace, "accept  parse started at %ld", yyStartCount);
	 yyNl ();
      }
# endif
      return yyErrorCount;
   }

# ifndef NO_RECOVER
static int yyErrorRecovery
# ifdef HAVE_ARGS
   (yySymbolRange yyTerminal,
#  ifdef YYDEBUG
    yySymbolRange * yyPrevTerminal,
#  endif
    long yyStackPtr)
# else
   (yyTerminal,
#  ifdef YYDEBUG
    yyPrevTerminal,
#  endif
    yyStackPtr)
   yySymbolRange	yyTerminal	;
#  ifdef YYDEBUG
   yySymbolRange *	yyPrevTerminal	;
#  endif
   long			yyStackPtr	;
# endif
   {
#     define	yyContinueSize	5000
      rbool	yyTokensSkipped	;
      tSet	yyContinueSet	;
      tSet	yyRestartSet	;
      int	yyLength	;
      char	yyContinueString [yyContinueSize + 2];

      if (yyControl.yyMessages) {
   /* 1. report an error */
	 ErrorMessage (xxSyntaxError, xxError, expr_scan_Attribute.Position);

   /* 2. report the offending token */
	 strcpy (yyContinueString, yyGetTokenName (yyTerminal));
# ifdef SPELLING
	 if (strncmp (yyContinueString, expr_scan_TokenPtr, expr_scan_TokenLength)) {
	    yyContinueString [yyLength = strlen (yyContinueString)] = ' ';
	    expr_scan_GetWord (& yyContinueString [++ yyLength]);
	 }
# endif
	 ErrorMessageI (xxTokenFound, xxInformation, expr_scan_Attribute.Position,
	    xxString, yyContinueString);

   /* 3. report the set of expected terminal symbols */
	 MakeSet (& yyContinueSet, yyLastTerminal);
	 yyComputeContinuation (yyStackPtr, & yyContinueSet);
	 yyLength = 0;
	 yyContinueString [0] = '\0';
	 while (! IsEmpty (& yyContinueSet)) {
	    char * yyTokenString =
	       yyGetTokenName ((yySymbolRange) Extract (& yyContinueSet));
	    int yyl = strlen (yyTokenString);
	    if (yyLength + yyl >= yyContinueSize) break;
	    strcpy (& yyContinueString [yyLength], yyTokenString);
	    yyLength += yyl;
	    yyContinueString [yyLength ++] = ' ';
	 }
	 yyContinueString [-- yyLength] = '\0';
	 ErrorMessageI (xxExpectedTokens, xxInformation, expr_scan_Attribute.Position,
	    xxString, yyContinueString);
	 ReleaseSet (& yyContinueSet);
      }

   /* 4. compute the set of terminal symbols for restart of the parse */
      MakeSet (& yyRestartSet, yyLastTerminal);
      yyComputeRestartPoints (yyStackPtr, & yyRestartSet);

   /* 5. skip terminal symbols until a restart point is reached */
      yyTokensSkipped = rfalse;
      while (! IsElement (yyTerminal, & yyRestartSet)) {
	 yyTerminal = yyGetToken ();
	 yyTokensSkipped = rtrue;
# ifdef YYDEBUG
	 if (expr_pars_Debug) {
	    yyPrintState (yyStateStack [yyStackPtr]);
	    fprintf (yyTrace, "skip    %s, lookahead: %s",
	       yyGetTokenName (* yyPrevTerminal),
	       yyGetTokenName (yyTerminal)); yyNl ();
	    * yyPrevTerminal = yyTerminal;
	 }
# endif
      }
      ReleaseSet (& yyRestartSet);

   /* 6. report the restart point */
      if (yyTokensSkipped & yyControl.yyMessages)
	 ErrorMessage (xxRestartPoint, xxInformation, expr_scan_Attribute.Position);

      return yyTerminal;
   }

/*
   compute the set of terminal symbols that can be accepted (read)
   in a given stack configuration (eventually after reduce actions)
*/

static void yyComputeContinuation
# ifdef HAVE_ARGS
   (long yyStackPtr, tSet * yyContinueSet)
# else
   (yyStackPtr, yyContinueSet)
   long			yyStackPtr	;
   tSet *		yyContinueSet	;
# endif
   {
      register yySymbolRange	yyTerminal;
      register yyStateRange	yyState = yyStateStack [yyStackPtr];

      AssignEmpty (yyContinueSet);
      for (yyTerminal = yyFirstTerminal; yyTerminal <= yyLastTerminal;
							yyTerminal ++) {
	 yyStateRange yyNextState = yyNext (yyState, yyTerminal);
	 if (yyNextState != yyNoState && (yyNextState <= yyLastStopState ||
	    yyIsContinuation (yyTerminal, yyStackPtr))) {
	    Include (yyContinueSet, yyTerminal);
	 }
      }
   }

/*
   check whether a given terminal symbol can be accepted (read)
   in a certain stack configuration (eventually after reduce actions)
*/

static rbool yyIsContinuation
# ifdef HAVE_ARGS
   (yySymbolRange yyTerminal, long yyStackPtr)
# else
   (yyTerminal, yyStackPtr)
   yySymbolRange	yyTerminal	;
   long			yyStackPtr	;
# endif
   {
      register yyStateRange	yState		;
      register yytNonterminal	yyNonterminal	;

      while (yyStackPtr >= yyIsContStackSize)	       /* pass Stack by value */
	 yyExtendArray ((char * *) & yyIsContStackPtr, & yyIsContStackSize,
			  (unsigned long) sizeof (yyStateRange));
      memcpy ((char *) yyIsContStackPtr, (char *) yyStateStack,
		(int) sizeof (yyStateRange) * (yyStackPtr + 1));

      yState = yyIsContStackPtr [yyStackPtr];
      for (;;) {
	 yyIsContStackPtr [yyStackPtr] = yState;
	 yState = yyNext (yState, yyTerminal);
	 if (yState == yyNoState) return rfalse;

	 do {						/* reduce */
	    if (yState > yyLastReduceState) {		/* dynamic ? */
	       yState = yyCondition [yState - yyLastReduceState];
	    }
	    if (yState <= yyLastStopState) { /* read, read reduce, or accept? */
	       return rtrue;
	    } else {					/* reduce */
	       yyStackPtr -= yyLength [yState - yyFirstReduceState];
	       yyNonterminal = yyLeftHandSide [yState - yyFirstReduceState];
	    }

	    yState = yyNext (yyIsContStackPtr [yyStackPtr],
				(yySymbolRange) yyNonterminal);
	    yyStackPtr ++;
	    if (yyStackPtr >= yyIsContStackSize) {
	       yyExtendArray ((char * *) & yyIsContStackPtr,
		  & yyIsContStackSize, (unsigned long) sizeof (yyStateRange));
	       if (yyStackPtr >= 1000) return rfalse; /* EMERGENCY break !!! */
	    }
	 } while (yState >= yyFirstFinalState);
      }
   }

/*
   compute the set of terminal symbols that can be accepted (read)
   directly in a given stack configuration
*/

static void yyCompContinuation
# ifdef HAVE_ARGS
   (yyStateRange yyState, tSet * yyContinueSet)
# else
   (yyState, yyContinueSet)
   yyStateRange		yyState		;
   tSet *		yyContinueSet	;
# endif
   {
      register yySymbolRange	yyTerminal;

      AssignEmpty (yyContinueSet);
      for (yyTerminal = yyFirstTerminal; yyTerminal <= yyLastTerminal;
							yyTerminal ++) {
	 yyStateRange yyNextState = yyNext (yyState, yyTerminal);
	 if (yyNextState != yyNoState && yyNextState <= yyLastStopState) {
	    Include (yyContinueSet, yyTerminal);
	 }
      }
   }

/*
   compute a set of terminal symbols that can be used to restart
   parsing in a given stack configuration. We simulate parsing until
   end of file using a suffix program synthesized by the function (array)
   yyContinuation. All symbols acceptable in the states reached during
   the simulation can be used to restart parsing.
*/

static void yyComputeRestartPoints
# ifdef HAVE_ARGS
   (long yyStackPtr, tSet * yyRestartSet)
# else
   (yyStackPtr, yyRestartSet)
   long			yyStackPtr	;
   tSet *		yyRestartSet	;
# endif
   {
      register yyStateRange	yState		;
      register yytNonterminal	yyNonterminal	;
	       tSet		yyContinueSet	;

      while (yyStackPtr >= yyCompResStackSize)	       /* pass Stack by value */
	 yyExtendArray ((char * *) & yyCompResStackPtr, & yyCompResStackSize,
			  (unsigned long) sizeof (yyStateRange));
      memcpy ((char *) yyCompResStackPtr, (char *) yyStateStack,
		(int) sizeof (yyStateRange) * (yyStackPtr + 1));

      MakeSet (& yyContinueSet, yyLastTerminal);
      AssignEmpty (yyRestartSet);
      yState = yyCompResStackPtr [yyStackPtr];

      for (;;) {
	 if (yyStackPtr >= yyCompResStackSize)
	    yyExtendArray ((char * *) & yyCompResStackPtr, & yyCompResStackSize,
			     (unsigned long) sizeof (yyStateRange));
	 yyCompResStackPtr [yyStackPtr] = yState;
	 yyCompContinuation (yState, & yyContinueSet);
	 Union (yyRestartSet, & yyContinueSet);
# ifdef YYDCRP
	 {
	    int yyLength = 0;
	    char yyContinueString [yyContinueSize + 2];
	    yyContinueString [0] = '\0';
	    while (! IsEmpty (& yyContinueSet)) {
	       char * yyTokenString =
		  yyGetTokenName ((yySymbolRange) Extract (& yyContinueSet));
	       int yyl = strlen (yyTokenString);
	       if (yyLength + yyl >= yyContinueSize) break;
	       strcpy (& yyContinueString [yyLength], yyTokenString);
	       yyLength += yyl;
	       yyContinueString [yyLength ++] = ' ';
	    }
	    yyContinueString [-- yyLength] = '\0';
	    fprintf (yyTrace, "%5d union %s", yState, yyContinueString);
	    yyNl ();
	 }
# endif
	 yState = yyNext (yState, yyContinuation [yState]);

	 if (yState >= yyFirstFinalState) {		/* final state ? */
	    if (yState <= yyLastReadReduceState) {	/* read reduce ? */
	       yyStackPtr ++;
	       yState = yyFinalToProd [yState - yyFirstReadReduceState];
# ifdef YYDCRP
	       yyCompResStackPtr [yyStackPtr] =
					yyCompResStackPtr [yyStackPtr - 1];
	       fprintf (yyTrace, "%5d shift   %s",
		  yyCompResStackPtr [yyStackPtr], yyGetTokenName
		  (yyContinuation [yyCompResStackPtr [yyStackPtr]])); yyNl ();
# endif
	    }

	    do {					/* reduce */
	       if (yState > yyLastReduceState) {	/* dynamic ? */
# ifdef YYDCRP
		  fprintf (yyTrace, "%5d dynamic decision %d",
		    yyCompResStackPtr [yyStackPtr], yState - yyLastReduceState);
		  yyNl ();
# endif
		  yState = yyCondition [yState - yyLastReduceState];
	       }
	       if (yyFirstReduceState <= yState &&
		   yState <= yyLastStopState) {		/* accept */
# ifdef YYDCRP
		  fprintf (yyTrace, "%5d accept",
		     yyCompResStackPtr [yyStackPtr]); yyNl ();
# endif
		  ReleaseSet (& yyContinueSet);
		  return;
	       } else if (yState < yyFirstFinalState) {	/* read */
		  goto yyRead;
	       } else {					/* reduce */
# ifdef YYDCRP
		  fprintf (yyTrace, "%5d reduce  %s",
		     yyCompResStackPtr [yyStackPtr],
		     yyRule [yState - yyLastReadReduceState]); yyNl ();
# endif
		  yyStackPtr -= yyLength [yState - yyFirstReduceState];
		  yyNonterminal = yyLeftHandSide [yState - yyFirstReduceState];
	       }

	       yState = yyNext (yyCompResStackPtr [yyStackPtr],
				(yySymbolRange) yyNonterminal);
	       yyStackPtr ++;
	    } while (yState >= yyFirstFinalState);
	 } else {					/* read */
yyRead:
# ifdef YYDCRP
	    fprintf (yyTrace, "%5d shift   %s",
	       yyCompResStackPtr [yyStackPtr], yyGetTokenName
	       (yyContinuation [yyCompResStackPtr [yyStackPtr]])); yyNl ();
# endif
	    yyStackPtr ++;
	 }
      }
   }

/* access the parse table:   Next : State x Symbol -> Action */

static yyStateRange yyNext
# ifdef HAVE_ARGS
   (yyStateRange yyState, yySymbolRange yySymbol)
# else
   (yyState, yySymbol) yyStateRange yyState; yySymbolRange yySymbol;
# endif
   {
      if (yySymbol <= yyLastTerminal) {
	 for (;;) {
	    register yytComb * yyTCombPtr = yyTBasePtr [yyState] + yySymbol;
# if defined YYTDefault & defined YYaccDefault
	    register unsigned long * yylp;
# endif
	    if (yyTCombPtr->Check == yyState) return yyTCombPtr->Next;
# ifdef YYTDefault
#  ifdef YYaccDefault
	    return (yylp = yyDefaultLook [yyState]) &&
	       (yylp [yySymbol >> 5] >> (yySymbol & 0x1f)) & 1 ?
		  yyTDefault [yyState] : yyNoState;
#  else
	    if ((yyState = yyTDefault [yyState]) == yyNoState) return yyNoState;
#  endif
# else
	    return yyNoState;
# endif
	 }
      }
# ifdef YYNDefault
      for (;;) {
	 register yytComb * yyNCombPtr = yyNBasePtr [yyState] + yySymbol;
	 if (yyNCombPtr->Check == yyState) return yyNCombPtr->Next;
	 yyState = yyNDefault [yyState];
      }
# else
      return yyNBasePtr [yyState] [yySymbol];
# endif
   }
# endif

void Beginexpr_pars ARGS ((void))
   {
/* line 60 "expr_pars.lrk" */


/* line 1943 "expr_pars.c" */
   }

void Closeexpr_pars ARGS ((void))
   {
/* line 63 "expr_pars.lrk" */


/* line 1951 "expr_pars.c" */
   }

