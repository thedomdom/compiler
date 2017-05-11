/* $Id: Scanner.c,v 2.67 2009/10/13 14:13:39 grosch Exp $ */

# define rbool		char
# define rtrue		1
# define rfalse		0
# define StdIn		0

# include "l_scan.h"

# ifndef EXTERN_C_BEGIN
# define EXTERN_C_BEGIN
# define EXTERN_C_END
# endif

EXTERN_C_BEGIN
#    include "l_scanSource.h"
#    include "rSystem.h"
#    include "General.h"
#    include "DynArray.h"
#    include "Position.h"
#    include "Errors.h"
EXTERN_C_END

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>

# define yyStart(State)	{ yyPreviousStart = yyStartState; yyStartState = State;}
# define yyPrevious	{ yyStateRange s = yyStartState; \
			yyStartState = yyPreviousStart; yyPreviousStart = s; }
# define yyEcho		{ (void) fwrite (l_scan_TokenPtr, sizeof (yytChar), \
			l_scan_TokenLength, stdout); }
# define yyEol(Column)	{ yyLineCount ++; \
			yyLineStart = (yytusChar *) l_scan_TokenPtr + \
			l_scan_TokenLength - 1 - (Column); }
# if l_scan_xxMaxCharacter < 256
#  define output(c)	(void) putchar ((int) c)
# else
#  define output(c)	(void) printf ("%lc", c)
# endif
# define yyColumn(Ptr)	((int) ((Ptr) - (yytChar *) yyLineStart))
# define yyOffset(Ptr)	(yyFileOffset + ((Ptr) - yyChBufferStart2))

# define yytChar	l_scan_xxtChar
# define yytusChar	l_scan_xxtusChar

# define yyDNoState		0
# define yyFirstCh	(yytusChar) '\0'
# define yyEolCh	(yytusChar) '\12'
# define yyEobCh	(yytusChar) '\177'
# define yyDStateCount	123
# define yyTableSize	1350
# define yyEobState	69
# define yyDefaultState	70
# define yyToClassArraySize	0
# define STD	1
# define STRING	3
# define COMMENT	5
# define xxGetWord
# define xxinput

static void yyExit ARGS ((void))
{ rExit (1); }

typedef unsigned short	yyStateRange;
typedef struct { yyStateRange yyCheck, yyNext; } yyCombType;

	yytChar *	l_scan_TokenPtr	;
	int		l_scan_TokenLength	;
	l_scan_tScanAttribute	l_scan_Attribute	;
	void		(* l_scan_Exit)	ARGS ((void)) = yyExit;

static	void		yyInitialize	ARGS ((void));
static	void		yyErrorMessage	ARGS ((int yyErrorCode));
static	yytChar		input		ARGS ((void));
static	void		unput		ARGS ((yytChar));
static	void		yyLess		ARGS ((int));

static	yyCombType	yyComb		[yyTableSize   + 1] = {
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   1,   72}, 
{   1,   71}, {   0,    0}, {   3,   73}, {   3,   71}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   1,   74}, {   0,    0}, {   1,   81}, 
{   3,   75}, {   0,    0}, {   3,   80}, {   0,    0}, {   0,    0}, 
{   1,   86}, {   1,   85}, {   1,   87}, {   1,   89}, {   0,    0}, 
{   1,   88}, {   1,   48}, {   1,   83}, {   1,    9}, {   1,    9}, 
{   1,    9}, {   1,    9}, {   1,    9}, {   1,    9}, {   1,    9}, 
{   1,    9}, {   1,    9}, {   1,    9}, {   2,   44}, {   1,   94}, 
{   1,   92}, {   1,   90}, {   1,   93}, {   5,   72}, {   5,   71}, 
{   7,   82}, {   1,   53}, {  39,   21}, {   1,   67}, {   1,   51}, 
{   1,   95}, {  40,   22}, {  41,   23}, {   1,   26}, {  26,   17}, 
{  44,   11}, {   0,    0}, {   0,    0}, {  10,   32}, {   1,  111}, 
{   1,  117}, {  27,   14}, {  26,   34}, {   1,   60}, {   1,   31}, 
{  28,   15}, {   5,   76}, {   1,   99}, {   0,    0}, {   0,    0}, 
{  77,   79}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   3,   77}, {   5,    7}, {   0,    0}, {   1,   53}, {  29,   28}, 
{   1,   67}, {   1,   51}, {   1,   95}, {   0,    0}, {   0,    0}, 
{   1,   26}, {  26,   17}, {   0,    0}, {   0,    0}, {   0,    0}, 
{  10,   32}, {   1,  111}, {   1,  117}, {  27,   14}, {  26,   34}, 
{   1,   60}, {   1,   31}, {  28,   15}, {   9,   48}, {   1,   99}, 
{   9,    9}, {   9,    9}, {   9,    9}, {   9,    9}, {   9,    9}, 
{   9,    9}, {   9,    9}, {   9,    9}, {   9,    9}, {   9,    9}, 
{  68,   69}, {  29,   28}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {  83,   84}, {   8,    8}, {  90,   91}, 
{   7,   69}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {  77,   78}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, { 100,  101}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   0,    0}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, {   8,    8}, 
{   8,    8}, {   8,    8}, {   8,    8}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   13}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{   0,    0}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, 
{  11,   11}, {  11,   11}, {  11,   11}, {  11,   11}, {  12,   12}, 
{  12,   12}, {  12,   12}, {  12,   12}, {  12,   12}, {  12,   12}, 
{  12,   12}, {  12,   12}, {  12,   12}, {  12,   12}, {  30,   27}, 
{  31,   29}, {  32,   24}, {  33,   19}, {  35,   30}, {  36,   16}, 
{  48,   12}, {  48,   12}, {  48,   12}, {  48,   12}, {  48,   12}, 
{  48,   12}, {  48,   12}, {  48,   12}, {  48,   12}, {  48,   12}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{   0,    0}, {  30,   27}, {  31,   29}, {  32,   24}, {  33,   19}, 
{  35,   30}, {  36,   16}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {  14,   66}, {  12,   69}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, {  14,   66}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {   0,    0}, 
{  37,   33}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  37,   33}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {   0,    0}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, {  25,   25}, 
{  25,   25}, {  34,   37}, {  38,   20}, {  42,   10}, {  43,   36}, 
{  34,   18}, {  45,   41}, {  46,   42}, {  47,   45}, {  49,   40}, 
{  50,   38}, {   0,    0}, {  51,  104}, {  52,   39}, {  51,   50}, 
{  53,   35}, {  54,   52}, {  55,   61}, {  56,   54}, {  57,   43}, 
{  58,   57}, {  59,   56}, {  60,   58}, {  61,   46}, {  62,   63}, 
{  63,   55}, {  38,   47}, {  64,   65}, {  65,   62}, {  38,   49}, 
{   0,    0}, {   0,    0}, {   0,    0}, {  34,   37}, {   0,    0}, 
{  42,   10}, {  43,   36}, {  34,   18}, {  45,   41}, {  46,   42}, 
{  47,   45}, {  49,   40}, {  50,   38}, {  38,   59}, {  51,  104}, 
{  52,   39}, {  51,   50}, {  53,   35}, {  54,   52}, {  55,   61}, 
{  56,   54}, {  57,   43}, {  58,   57}, {  59,   56}, {  60,   58}, 
{  61,   46}, {  62,   63}, {  63,   55}, {  38,   47}, {  64,   65}, 
{  65,   62}, {  38,   49}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {   0,    0}, {  95,  107}, {  96,   97}, 
{  38,   59}, {  95,   96}, {   0,    0}, {  99,  100}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  95,  107}, {  96,   97}, { 101,  102}, {  95,   96}, {  66,   66}, 
{  99,  100}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, {  66,   66}, 
{  66,   66}, {  66,   66}, {  67,   64}, { 102,  103}, { 101,  102}, 
{ 104,  105}, { 105,  106}, { 107,  108}, { 108,  109}, { 109,  110}, 
{ 111,  112}, { 112,  113}, {  67,   98}, { 113,  114}, { 114,  115}, 
{ 115,  116}, { 117,  118}, { 118,  119}, { 119,  120}, { 120,  121}, 
{ 121,  122}, { 122,  123}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {  67,   64}, 
{ 102,  103}, {   0,    0}, { 104,  105}, { 105,  106}, { 107,  108}, 
{ 108,  109}, { 109,  110}, { 111,  112}, { 112,  113}, {  67,   98}, 
{ 113,  114}, { 114,  115}, { 115,  116}, { 117,  118}, { 118,  119}, 
{ 119,  120}, { 120,  121}, { 121,  122}, { 122,  123}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, {   0,    0}, 
{   0,    0}, 
};
static	yyCombType *	yyBasePtr	[yyDStateCount + 1] = { 0,
& yyComb [   0], & yyComb [  13], & yyComb [   3], & yyComb [   0], 
& yyComb [  54], & yyComb [   0], & yyComb [  18], & yyComb [ 132], 
& yyComb [  72], & yyComb [   0], & yyComb [ 388], & yyComb [ 596], 
& yyComb [   0], & yyComb [ 627], & yyComb [   0], & yyComb [   0], 
& yyComb [   0], & yyComb [   0], & yyComb [   0], & yyComb [   0], 
& yyComb [   0], & yyComb [   0], & yyComb [   0], & yyComb [   0], 
& yyComb [ 750], & yyComb [   4], & yyComb [   3], & yyComb [   7], 
& yyComb [  30], & yyComb [ 581], & yyComb [ 583], & yyComb [ 573], 
& yyComb [ 573], & yyComb [ 926], & yyComb [ 587], & yyComb [ 588], 
& yyComb [ 675], & yyComb [ 961], & yyComb [  21], & yyComb [  25], 
& yyComb [  26], & yyComb [ 929], & yyComb [ 931], & yyComb [  30], 
& yyComb [ 929], & yyComb [ 939], & yyComb [ 934], & yyComb [ 612], 
& yyComb [ 944], & yyComb [ 947], & yyComb [ 941], & yyComb [ 949], 
& yyComb [ 951], & yyComb [ 945], & yyComb [ 957], & yyComb [ 950], 
& yyComb [ 951], & yyComb [ 943], & yyComb [ 954], & yyComb [ 943], 
& yyComb [ 944], & yyComb [ 964], & yyComb [ 948], & yyComb [ 965], 
& yyComb [ 957], & yyComb [1019], & yyComb [1073], & yyComb [   3], 
& yyComb [   0], & yyComb [   0], & yyComb [   0], & yyComb [   0], 
& yyComb [   0], & yyComb [   0], & yyComb [   0], & yyComb [   0], 
& yyComb [  56], & yyComb [   0], & yyComb [   0], & yyComb [   0], 
& yyComb [   0], & yyComb [   0], & yyComb [ 100], & yyComb [   0], 
& yyComb [   0], & yyComb [   0], & yyComb [   0], & yyComb [   0], 
& yyComb [   0], & yyComb [  83], & yyComb [   0], & yyComb [   0], 
& yyComb [   0], & yyComb [   0], & yyComb [1002], & yyComb [ 997], 
& yyComb [   0], & yyComb [   0], & yyComb [1011], & yyComb [ 119], 
& yyComb [1036], & yyComb [1074], & yyComb [   0], & yyComb [1062], 
& yyComb [1077], & yyComb [   0], & yyComb [1068], & yyComb [1083], 
& yyComb [1065], & yyComb [   0], & yyComb [1065], & yyComb [1067], 
& yyComb [1073], & yyComb [1069], & yyComb [1071], & yyComb [   0], 
& yyComb [1074], & yyComb [1078], & yyComb [1087], & yyComb [1077], 
& yyComb [1095], & yyComb [1084], & yyComb [   0], 
};
static	yyStateRange	yyDefault	[yyDStateCount + 1] = { 0,
   14,     1,     8,     3,    25,     5,     0,     7,    12,    14, 
    1,     0,     0,    12,    14,    14,    14,    14,    14,     0, 
    0,     0,     0,    14,     7,    14,    14,    14,    14,    14, 
   14,    14,    14,    14,    14,    14,    14,    14,    14,    14, 
   66,    66,    66,    68,    66,    66,    66,    68,    66,    66, 
   66,    66,    66,    66,    66,    66,    66,    66,    66,    66, 
   66,    66,    66,    66,    66,    68,    66,     0,     0,     0, 
    0,     0,     8,     0,     8,    25,    68,     0,     0,     0, 
    0,     0,    68,     0,     0,     0,     0,     0,     0,    68, 
    0,     0,     0,     0,    66,    66,    66,    66,    66,    66, 
   66,    66,    66,    66,    66,    66,    66,    66,    66,    66, 
   66,    66,    66,    66,    66,    66,    66,    66,    66,    66, 
   66,    66,    66, 
};
static	yyStateRange	yyEobTrans	[yyDStateCount + 1] = { 0,
    0,     0,     8,     8,    25,    25,     0,     8,     0,     0, 
   11,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,    25,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     8,     0,     8,    25,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 
    0,     0,     0, 
};

# if l_scan_xxMaxCharacter < 256
#  define yyGetLine	l_scan_GetLine
# else
#  define yyGetLine	l_scan_GetWLine
# endif

# if yyToClassArraySize == 0
#  define yyToClass(x) (x)
# else
typedef	unsigned short	yytCharClass;

static	yytCharClass	yyToClassArray	[yyToClassArraySize] = {
};
#  if l_scan_xxMaxCharacter < yyToClassArraySize
#   define yyToClass(x) (yyToClassArray [x])
#  else
#   define yyToClass(x) \
	((x) < yyToClassArraySize ? yyToClassArray [x] : yyToClassFunction (x))

static	yytusChar	yyToClassUpb	[yyToClassRangeSize] = {
};
static	yytCharClass	yyToClassClass	[yyToClassRangeSize] = {
};

static yytCharClass yyToClassFunction
# ifdef HAVE_ARGS
   (yytusChar yyCh)
# else
   (yyCh) yytusChar yyCh;
# endif
{
   register int yyLower = 1, yyUpper = yyToClassRangeSize;
   while (yyUpper - yyLower > 1) {			/* binary search */
      register int yyMiddle = (yyLower + yyUpper) / 2;
      if (yyToClassUpb [yyMiddle] < yyCh)
	 yyLower = yyMiddle;
      else
	 yyUpper = yyMiddle;
   }
   if (yyToClassUpb [yyLower - 1] < yyCh && yyCh <= yyToClassUpb [yyLower])
      return yyToClassClass [yyLower];
   else
      return yyToClassClass [yyUpper];
}

#  endif
# endif

static	yyStateRange	yyStartState	= STD;
static	yyStateRange	yyPreviousStart	= STD;
static	int		yySourceFile	= StdIn;
static	rbool		yyEof		= rfalse;
static	long		yyBytesRead	= 0;
static	long		yyFileOffset	= 0;
static	unsigned int	yyLineCount	= 1;
static	yytusChar *	yyLineStart	;
static	yytChar *	yyChBufferStart2;

					/* Start State Stack: StStSt	*/

# if defined xxyyPush | defined xxyyPop
# define		yyInitStStStackSize	16

static	yyStateRange *	yyStStStackPtr	;
static	unsigned long	yyStStStackSize	= 0;
static	unsigned int	yyStStStackIdx	= 0;
# endif

# ifdef xxyyPush
static void yyPush
# ifdef HAVE_ARGS
   (yyStateRange yyState)
# else
   (yyState) yyStateRange yyState;
# endif
{
   if (yyStStStackIdx == yyStStStackSize) {
      if (yyStStStackSize == 0) {
	 yyStStStackSize = yyInitStStStackSize;
	 MakeArray ((char * *) & yyStStStackPtr, & yyStStStackSize,
			(unsigned long) sizeof (yyStateRange));
      } else {
	 ExtendArray ((char * *) & yyStStStackPtr, & yyStStStackSize,
			(unsigned long) sizeof (yyStateRange));
      }
      if (yyStStStackPtr == NULL) yyErrorMessage (xxScannerOutOfMemory);
   }
   yyStStStackPtr [yyStStStackIdx ++] = yyStartState;
   yyStart (yyState);
}
# endif

# ifdef xxyyPop
static void yyPop ARGS ((void))
{
   yyPreviousStart = yyStartState;
   if (yyStStStackIdx > 0)
      yyStartState = yyStStStackPtr [-- yyStStStackIdx];
   else
      yyErrorMessage (xxStartStackUnderflow);
}
# endif

static void yyTab1	ARGS ((int yya));

# define yyTab		yyTab1 (0)
# define yyTab2(a,b)	yyTab1 (a)

/* line 90 "l.rex" */

  # include <stdlib.h>
  # include "rString.h"

/* line 530 "l_scan.c" */

# ifndef yySetPosition
# define yySetPosition l_scan_Attribute.Position.Line = yyLineCount; \
l_scan_Attribute.Position.Column = (int) ((yytusChar *) l_scan_TokenPtr - yyLineStart);
# endif

# undef yyTab
# undef yyTab2

# ifndef yyInitBufferSize
# define yyInitBufferSize	1024 * 8 + 256
# endif
# ifndef yyInitFileStackSize
# define yyInitFileStackSize	8
# endif
# ifndef yyTabSpace
# define yyTabSpace		8
# endif

static void yyTab1
# ifdef HAVE_ARGS
   (int yya)
# else
   (yya) int yya;
# endif
   { yyLineStart -= (yyTabSpace - 1 - ((yytusChar *) l_scan_TokenPtr -
	yyLineStart + yya - 1)) & (yyTabSpace - 1); }

# define yyTab		yyLineStart -= (yyTabSpace - 1 - \
((yytusChar *) l_scan_TokenPtr - yyLineStart - 1)) & (yyTabSpace - 1)
# define yyTab1(a)	yyLineStart -= (yyTabSpace - 1 - \
((yytusChar *) l_scan_TokenPtr - yyLineStart + (a) - 1)) & (yyTabSpace - 1)
# define yyTab2(a,b)	yyLineStart -= (yyTabSpace - 1 - \
((yytusChar *) l_scan_TokenPtr - yyLineStart + (a) - 1)) & (yyTabSpace - 1)

# ifndef EBCDIC
#  if l_scan_xxMaxCharacter < 256
#   include <ctype.h>
#   define yyToUpper(x)	toupper (x)
#   define yyToLower(x)	tolower (x)
#  else
#   include <wctype.h>
#   define yyToUpper(x)	towupper (x)
#   define yyToLower(x)	towlower (x)
#  endif
# else
#  define yyToLower(x)	yyToLowerArray [x]
#  define yyToUpper(x)	yyToUpperArray [x]

# ifdef xxGetLower
static	yytusChar	yyToLowerArray	[] = {
'\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07',
'\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F',
'\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17',
'\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F',
'\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27',
'\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F',
'\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37',
'\x38', '\x39', '\x3A', '\x3B', '\x3C', '\x3D', '\x3E', '\x3F',
'\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47',
'\x48', '\x49', '\x4A', '\x4B', '\x4C', '\x4D', '\x4E', '\x4F',
'\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57',
'\x58', '\x59', '\x5A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F',
'\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67',
'\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F',
'\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77',
'\x78', '\x79', '\x7A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F',
'\x80',    'a',    'b',    'c',    'd',    'e',    'f',    'g',
   'h',    'i', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F',
'\x90',    'j',    'k',    'l',    'm',    'n',    'o',    'p',
   'q',    'r', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F',
'\xA0', '\xA1',    's',    't',   'u',     'v',    'w',    'x',
   'y',    'z', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF',
'\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7',
'\xB8', '\xB9', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF',
'\xC0',    'a',    'b',    'c',    'd',    'e',    'f',    'g',
   'h',    'i', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF',
'\xD0',    'j',    'k',    'l',    'm',    'n',    'o',    'p',
   'q',    'r', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF',
'\xE0', '\xE1',    's',    't',    'u',    'v',    'w',    'x',
   'y',    'z', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF',
'\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7',
'\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF'
};
# endif

# ifdef xxGetUpper
static	yytusChar	yyToUpperArray	[] = {
'\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07',
'\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F',
'\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17',
'\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F',
'\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27',
'\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F',
'\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37',
'\x38', '\x39', '\x3A', '\x3B', '\x3C', '\x3D', '\x3E', '\x3F',
'\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47',
'\x48', '\x49', '\x4A', '\x4B', '\x4C', '\x4D', '\x4E', '\x4F',
'\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57',
'\x58', '\x59', '\x5A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F',
'\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67',
'\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F',
'\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77',
'\x78', '\x79', '\x7A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F',
'\x80',    'A',    'B',    'C',    'D',    'E',    'F',    'G',
   'H',    'I', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F',
'\x90',    'J',    'K',    'L',    'M',    'N',    'O',    'P',
   'Q',    'R', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F',
'\xA0', '\xA1',    'S',    'T',    'U',    'V',    'W',    'X',
   'Y',    'Z', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF',
'\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7',
'\xB8', '\xB9', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF',
'\xC0',    'A',    'B',    'C',    'D',    'E',    'F',    'G',
   'H',    'I', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF',
'\xD0',    'J',    'K',    'L',    'M',    'N',    'O',    'P',
   'Q',    'R', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF',
'\xE0', '\xE1',    'S',    'T',    'U',    'V',    'W',    'X',
   'Y',    'Z', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF',
'\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7',
'\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF'
};
# endif

# endif

static	yyStateRange	yyInitStateStack [4] = { yyDefaultState };
static	yyStateRange *	yyStateStack	= yyInitStateStack;
static	unsigned long	yyStateStackSize= 0;

static	yytusChar	yyInitChBuffer [] = {
   '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
   '\0', '\0', '\0', '\0', '\0', '\0', '\0', yyEolCh, yyEobCh, '\0', };
static	yytusChar *	yyChBufferPtr	= yyInitChBuffer;
static	unsigned long	yyChBufferSize	= 0;
static	yytusChar *	yyChBufferStart	= & yyInitChBuffer [16];
static	yytusChar *	yyChBufferIndex	= & yyInitChBuffer [16];

# if yyInitFileStackSize != 0
typedef	struct {
	int		yySourceFile	;
	rbool		yyEof		;
	yytusChar *	yyChBufferPtr	;
	yytusChar *	yyChBufferStart	;
	unsigned long	yyChBufferSize	;
	yytusChar *	yyChBufferIndex	;
	long		yyBytesRead	;
	long		yyFileOffset	;
	unsigned int	yyLineCount	;
	yytusChar *	yyLineStart	;
	}		yytFileStack	;

static	yytFileStack *	yyFileStack	;
static	unsigned long	yyFileStackSize	= 0;
static	yytFileStack *	yyFileStackPtr	;
# endif

int l_scan_GetToken ARGS ((void))
{
   register	yyStateRange	yyState;
   register	yyStateRange *	yyStatePtr;
   register	yytusChar *	yyChBufferIndexReg;
   register	yyCombType * *	yyBasePtrReg = yyBasePtr;
/* line 95 "l.rex" */

 /* user-defined local variables of the generated GetToken routine */
  # define MAX_STRING_LEN 2048
  char string [MAX_STRING_LEN+1];
  int len;

  /* Variable zur Ueberpruefung auf korrekt geklammerte Ausdruecke */
  int bracketCounter = 0;

/* line 703 "l_scan.c" */

yyBegin:
   yyState		= yyStartState;		/* initialize */
   yyStatePtr		= & yyStateStack [1];
   yyChBufferIndexReg	= yyChBufferIndex;
   l_scan_TokenPtr		= (yytChar *) yyChBufferIndexReg;
   if (yyChBufferIndexReg [-1] == yyEolCh) yyState ++;

   /* ASSERT yyChBuffer [yyChBufferIndex] == first character */

yyContinue:		/* continue after sentinel or skipping blanks */
   for (;;) {		/* execute as many state transitions as possible */
			/* determine next state and get next character */
      register yyCombType * yyTablePtr =
		      yyBasePtrReg [yyState] + yyToClass (* yyChBufferIndexReg);
      if (yyTablePtr->yyCheck == yyState) {
	 yyState = yyTablePtr->yyNext;		/* determine next state */
	 * yyStatePtr ++ = yyState;		/* push state */
	 yyChBufferIndexReg ++;			/* get next character */
	 goto yyContinue;
      }
      if ((yyState = yyDefault [yyState]) == yyDNoState) break;
   }

   for (;;) {				/* search for last final state */
      l_scan_TokenLength =
	    (int) (yyChBufferIndexReg - (yytusChar *) l_scan_TokenPtr);
      yyChBufferIndex = yyChBufferIndexReg;
switch (* -- yyStatePtr) {
case 9:;
yySetPosition
/* line 149 "l.rex" */
{l_scan_Attribute.int_const.Value = malloc (l_scan_TokenLength+1);
	 l_scan_GetWord (l_scan_Attribute.int_const.Value);
	 return tok_int_const;
	
/* line 740 "l_scan.c" */
} goto yyBegin;
case 12:;
yySetPosition
/* line 157 "l.rex" */
{
		l_scan_Attribute.float_const.Value = malloc(l_scan_TokenLength+1);
		l_scan_GetWord(l_scan_Attribute.float_const.Value);
		return tok_float_const;
	
/* line 750 "l_scan.c" */
} goto yyBegin;
case 123:;
yySetPosition
/* line 164 "l.rex" */
{return tok_PROGRAM;
/* line 756 "l_scan.c" */
} goto yyBegin;
case 24:;
yySetPosition
/* line 165 "l.rex" */
{return tok_DECLARATIONS;
/* line 762 "l_scan.c" */
} goto yyBegin;
case 19:;
yySetPosition
/* line 166 "l.rex" */
{return tok_INPUT;
/* line 768 "l_scan.c" */
} goto yyBegin;
case 116:;
yySetPosition
/* line 167 "l.rex" */
{return tok_OUTPUT;
/* line 774 "l_scan.c" */
} goto yyBegin;
case 16:;
yySetPosition
/* line 169 "l.rex" */
{return tok_STRING;
/* line 780 "l_scan.c" */
} goto yyBegin;
case 18:;
yySetPosition
/* line 170 "l.rex" */
{return tok_INT;
/* line 786 "l_scan.c" */
} goto yyBegin;
case 110:;
yySetPosition
/* line 172 "l.rex" */
{return tok_FLOAT;
/* line 792 "l_scan.c" */
} goto yyBegin;
case 14:;
yySetPosition
/* line 174 "l.rex" */
{return tok_BEGIN;
/* line 798 "l_scan.c" */
} goto yyBegin;
case 20:;
yySetPosition
/* line 175 "l.rex" */
{return tok_END;
/* line 804 "l_scan.c" */
} goto yyBegin;
case 17:;
yySetPosition
/* line 177 "l.rex" */
{return tok_IF;
/* line 810 "l_scan.c" */
} goto yyBegin;
case 15:;
yySetPosition
/* line 178 "l.rex" */
{return tok_THEN;
/* line 816 "l_scan.c" */
} goto yyBegin;
case 106:;
yySetPosition
/* line 179 "l.rex" */
{return tok_ELSE;
/* line 822 "l_scan.c" */
} goto yyBegin;
case 22:;
yySetPosition
/* line 180 "l.rex" */
{return tok_ENDIF;
/* line 828 "l_scan.c" */
} goto yyBegin;
case 103:;
yySetPosition
/* line 182 "l.rex" */
{return tok_WHILE;
/* line 834 "l_scan.c" */
} goto yyBegin;
case 98:;
yySetPosition
/* line 183 "l.rex" */
{return tok_DO;
/* line 840 "l_scan.c" */
} goto yyBegin;
case 21:;
yySetPosition
/* line 184 "l.rex" */
{return tok_ENDWHILE;
/* line 846 "l_scan.c" */
} goto yyBegin;
case 97:;
yySetPosition
/* line 186 "l.rex" */
{return tok_FOR;
/* line 852 "l_scan.c" */
} goto yyBegin;
case 94:;
yySetPosition
/* line 187 "l.rex" */
{return tok_SEMICOLON;
/* line 858 "l_scan.c" */
} goto yyBegin;
case 23:;
yySetPosition
/* line 188 "l.rex" */
{return tok_ENDFOR;
/* line 864 "l_scan.c" */
} goto yyBegin;
case 93:;
yySetPosition
/* line 190 "l.rex" */
{return tok_GT;
/* line 870 "l_scan.c" */
} goto yyBegin;
case 92:;
yySetPosition
/* line 191 "l.rex" */
{return tok_LT;
/* line 876 "l_scan.c" */
} goto yyBegin;
case 90:;
yySetPosition
/* line 192 "l.rex" */
{return tok_ASSIGN;
/* line 882 "l_scan.c" */
} goto yyBegin;
case 91:;
yySetPosition
/* line 193 "l.rex" */
{return tok_EQUALS;
/* line 888 "l_scan.c" */
} goto yyBegin;
case 89:;
yySetPosition
/* line 195 "l.rex" */
{return tok_PLUS;
/* line 894 "l_scan.c" */
} goto yyBegin;
case 44:;
case 88:;
yySetPosition
/* line 196 "l.rex" */
{return tok_MINUS;
/* line 901 "l_scan.c" */
} goto yyBegin;
case 87:;
yySetPosition
/* line 197 "l.rex" */
{return tok_MULT;
/* line 907 "l_scan.c" */
} goto yyBegin;
case 83:;
yySetPosition
/* line 198 "l.rex" */
{return tok_DIVIDE;
/* line 913 "l_scan.c" */
} goto yyBegin;
case 86:;
yySetPosition
/* line 201 "l.rex" */
{
		bracketCounter = bracketCounter+1;
		return tok_BRACKETOP;
	
/* line 922 "l_scan.c" */
} goto yyBegin;
case 85:;
yySetPosition
/* line 207 "l.rex" */
{
		bracketCounter = bracketCounter-1;
		return tok_BRACKETCL;
	
/* line 931 "l_scan.c" */
} goto yyBegin;
case 10:;
case 26:;
case 27:;
case 28:;
case 29:;
case 30:;
case 31:;
case 32:;
case 33:;
case 34:;
case 35:;
case 36:;
case 37:;
case 38:;
case 39:;
case 40:;
case 41:;
case 42:;
case 43:;
case 45:;
case 46:;
case 47:;
case 49:;
case 50:;
case 51:;
case 52:;
case 53:;
case 54:;
case 55:;
case 56:;
case 57:;
case 58:;
case 59:;
case 60:;
case 61:;
case 62:;
case 63:;
case 64:;
case 65:;
case 66:;
case 67:;
case 95:;
case 96:;
case 99:;
case 100:;
case 101:;
case 102:;
case 104:;
case 105:;
case 107:;
case 108:;
case 109:;
case 111:;
case 112:;
case 113:;
case 114:;
case 115:;
case 117:;
case 118:;
case 119:;
case 120:;
case 121:;
case 122:;
yySetPosition
/* line 214 "l.rex" */
{
		l_scan_Attribute.identifier.Value = malloc(l_scan_TokenLength+1);
		l_scan_GetWord(l_scan_Attribute.identifier.Value);
		return tok_identifier;
	
/* line 1003 "l_scan.c" */
} goto yyBegin;
case 13:;
yyChBufferIndex -= 1;
l_scan_TokenLength -= 1;
yySetPosition
/* line 222 "l.rex" */
{ /* comment up to end of line, nothing to do */
	  WritePosition (stdout, l_scan_Attribute.Position);
	  printf (" -- Kommentar\n");
        
/* line 1014 "l_scan.c" */
} goto yyBegin;
case 84:;
yySetPosition
/* line 229 "l.rex" */
{ /**/
	  yyStart (COMMENT);
	  WritePosition (stdout, l_scan_Attribute.Position);
	  printf (" Beginn des Kommentars\n");
	
/* line 1024 "l_scan.c" */
} goto yyBegin;
case 7:;
case 25:;
case 76:;
yySetPosition
/* line 236 "l.rex" */
{
/* line 1032 "l_scan.c" */
} goto yyBegin;
case 82:;
yySetPosition
/* line 239 "l.rex" */
{yyStart (STD);
	 WritePosition (stdout, l_scan_Attribute.Position);
	 printf (" Ende des Kommentars\n");
	
/* line 1041 "l_scan.c" */
} goto yyBegin;
case 81:;
yySetPosition
/* line 246 "l.rex" */
{ /* start of string */
          yyStart (STRING);
	  len = 0;
	
/* line 1050 "l_scan.c" */
} goto yyBegin;
case 8:;
case 73:;
case 75:;
yySetPosition
/* line 251 "l.rex" */
{ /* we're inside the string */
          if (len + l_scan_TokenLength+1 >= MAX_STRING_LEN) {
	    Message ("String zu lang", xxError, l_scan_Attribute.Position);
	    len = 0;
	  } else {
  	    len += l_scan_GetWord (&string[len]);
	  }
        
/* line 1064 "l_scan.c" */
} goto yyBegin;
case 80:;
yySetPosition
/* line 260 "l.rex" */
{ /* end of string */
          yyStart(STD);
	  string[len] = '\0';
	  l_scan_Attribute.string_const.Value = malloc (len+1);
	  strcpy (l_scan_Attribute.string_const.Value, string);
	  return tok_string_const;
        
/* line 1076 "l_scan.c" */
} goto yyBegin;
case 79:;
yySetPosition
/* line 268 "l.rex" */
{ /* transform the " characters to a single " */
          if (len + 1 >= MAX_STRING_LEN) {
	    Message ("String zu lang", xxError, l_scan_Attribute.Position);
            len = 0;
	  } else {
  	    string[len++] = '"';
          }
	
/* line 1088 "l_scan.c" */
} goto yyBegin;
case 78:;
yySetPosition
/* line 277 "l.rex" */
{ /* transform the n characters to a single " */
          if (len + 1 >= MAX_STRING_LEN) {
	    Message ("String zu lang", xxError, l_scan_Attribute.Position);
            len = 0;
	  } else {
  	    string[len++] = '\n';
	  }
	
/* line 1100 "l_scan.c" */
} goto yyBegin;
case 77:;
yySetPosition
/* line 286 "l.rex" */
{ /* special treatment of the -character */
          if (len + 1 >= MAX_STRING_LEN) {
	    Message ("String zu lang", xxError, l_scan_Attribute.Position);
            len = 0;
	  } else {
  	    string[len++] = '\\';
	  }
	
/* line 1113 "l_scan.c" */
} goto yyBegin;
case 74:;
{/* BlankAction */
while (* yyChBufferIndexReg ++ == ' ') ;
l_scan_TokenPtr = (yytChar *) -- yyChBufferIndexReg;
yyState = yyStartState;
yyStatePtr = & yyStateStack [1];
goto yyContinue;
/* line 1122 "l_scan.c" */
} goto yyBegin;
case 72:;
{/* TabAction */
yyTab;
/* line 1127 "l_scan.c" */
} goto yyBegin;
case 71:;
{/* EolAction */
yyEol (0);
/* line 1132 "l_scan.c" */
} goto yyBegin;
case 1:;
case 2:;
case 3:;
case 4:;
case 5:;
case 6:;
case 11:;
case 48:;
case 68:;
	 /* non final states */
	 yyChBufferIndexReg --;			/* return character */
	 break;

case 70:
	 yySetPosition
      l_scan_TokenLength   = 1;
	 yyChBufferIndex = ++ yyChBufferIndexReg;
	 {
/* line 105 "l.rex" */

  /* What happens if no scanner rule matches the input */
  /*MessageI ("Unzulaessiges Zeichen", xxError, l_scan_Attribute.Position, xxCharacter, (char*)*l_scan_TokenPtr);*/
  Message ("Unzulaessiges Zeichen", xxError, l_scan_Attribute.Position);

/* line 1158 "l_scan.c" */
	 }
	 goto yyBegin;

      case yyDNoState:
	 goto yyBegin;

case 69:
	 yyChBufferIndex = -- yyChBufferIndexReg; /* undo last state transit */
	 if (-- l_scan_TokenLength == 0) {		/* get previous state */
	    yyState = yyStartState;
  	    if (yyChBufferIndexReg [-1] == yyEolCh) yyState ++;
	 } else {
	    yyState = * (yyStatePtr - 1);
	 }

	 if (yyChBufferIndex != & yyChBufferStart [yyBytesRead]) {
					/* end of buffer sentinel in buffer */
	    if ((yyState = yyEobTrans [yyState]) == yyDNoState) continue;
	    yyChBufferIndexReg ++;
	    * yyStatePtr ++ = yyState;		/* push state */
	    goto yyContinue;
	 }
						/* end of buffer reached */
	 if (! yyEof) {
	    register yytChar * yySource;
	    register yytChar * yyTarget;
	    unsigned long yyChBufferFree;

	    if (yyChBufferSize == 0) {
	       yyStateRange * yyOldStateStack = yyStateStack;
	       yyInitialize ();
	       yyStatePtr += yyStateStack - yyOldStateStack;
	       yyChBufferIndexReg = yyChBufferIndex;
	    }
	    yySource = l_scan_TokenPtr - 1;
	    yyTarget = (yytChar *) & yyChBufferPtr
		[(yyMaxAlign - 1 - l_scan_TokenLength) & (yyMaxAlign - 1)];
	    yyChBufferFree = Exp2 (Log2 (yyChBufferSize - 4 -
		yyMaxAlign - l_scan_TokenLength));
		/* copy initial part of token in front of the input buffer */
	    if (yySource > yyTarget) {
	       l_scan_TokenPtr = yyTarget + 1;
	       do * yyTarget ++ = * yySource ++;
	       while (yySource < (yytChar *) yyChBufferIndexReg);
	       yyLineStart += (yytusChar *) yyTarget - yyChBufferStart -
				yyBytesRead;
	       yyChBufferStart = (yytusChar *) yyTarget;
	    } else {
	       yyChBufferStart = yyChBufferIndexReg;
	    }
	    yyChBufferStart2 = (yytChar *) yyChBufferStart;
						/* extend buffer if necessary */
	    if (yyChBufferFree < yyChBufferSize >> 3 /* / 8 */ ) {
	       register ptrdiff_t yyDelta;
	       register yytusChar * yyOldChBufferPtr = yyChBufferPtr;
	       ExtendArray ((char * *) & yyChBufferPtr, & yyChBufferSize,
				(unsigned long) sizeof (yytChar));
	       if (yyChBufferPtr == NULL) yyErrorMessage (xxScannerOutOfMemory);
	       yyDelta = yyChBufferPtr - yyOldChBufferPtr;
	       yyChBufferStart	+= yyDelta;
	       yyLineStart	+= yyDelta;
	       l_scan_TokenPtr	+= yyDelta;
	       yyChBufferStart2	 = (yytChar *) yyChBufferStart;
	       yyChBufferFree = Exp2 (Log2 (yyChBufferSize - 4 -
			yyMaxAlign - l_scan_TokenLength));
	       if (yyStateStackSize < yyChBufferSize) {
		  yyStateRange * yyOldStateStack = yyStateStack;
		  ExtendArray ((char * *) & yyStateStack, & yyStateStackSize,
				   (unsigned long) sizeof (yyStateRange));
		  if (yyStateStack == NULL)
		     yyErrorMessage (xxScannerOutOfMemory);
		  yyStatePtr	+= yyStateStack - yyOldStateStack;
	       }
	    }
						/* read buffer and restart */
	    yyChBufferIndex = yyChBufferIndexReg = yyChBufferStart;
	    yyFileOffset += yyBytesRead;
	    yyBytesRead = yyGetLine (yySourceFile, (yytChar *) yyChBufferIndex,
	       (int) yyChBufferFree);
	    if (yyBytesRead <= 0) { yyBytesRead = 0; yyEof = rtrue; }
	    yyChBufferStart [yyBytesRead    ] = yyEobCh;
	    yyChBufferStart [yyBytesRead + 1] = '\0';
	    goto yyContinue;
	 }

	 if (l_scan_TokenLength == 0) {		/* end of file reached */
	    if (yyChBufferSize == 0) return l_scan_EofToken;
	    yySetPosition
	    l_scan_CloseFile ();
# if yyInitFileStackSize != 0
	    if (yyFileStackPtr == yyFileStack) {
/* line 111 "l.rex" */

  /* What should be done if the end-of-input-file has been reached? */
  if (bracketCounter != 0) {
      Message (" Klammerung falsch", xxError, l_scan_Attribute.Position);
  }

  /* E.g.: check hat strings and comments are closed. */
  switch (yyStartState) {
  case STD:
    /* ok */
    break;
  case STRING:
   Message ("Nicht abgeschlossene Stringkonstante", xxError, l_scan_Attribute.Position);
   break;
  case COMMENT:
    Message ("Nicht abgeschlossener Kommentar", xxError, l_scan_Attribute.Position);
    break;
  default:
    Message ("UUPSI: Das sollte nicht passieren!! Jeder macht mal Fehler...", xxFatal, l_scan_Attribute.Position);
    break;
  }

  /* implicit: return the EofToken */

/* line 1275 "l_scan.c" */
	    }
	    if (yyFileStackPtr == yyFileStack) {
	       l_scan_ResetScanner ();
	       return l_scan_EofToken;
	    }
	    goto yyBegin;
# else
/* line 111 "l.rex" */

  /* What should be done if the end-of-input-file has been reached? */
  if (bracketCounter != 0) {
      Message (" Klammerung falsch", xxError, l_scan_Attribute.Position);
  }

  /* E.g.: check hat strings and comments are closed. */
  switch (yyStartState) {
  case STD:
    /* ok */
    break;
  case STRING:
   Message ("Nicht abgeschlossene Stringkonstante", xxError, l_scan_Attribute.Position);
   break;
  case COMMENT:
    Message ("Nicht abgeschlossener Kommentar", xxError, l_scan_Attribute.Position);
    break;
  default:
    Message ("UUPSI: Das sollte nicht passieren!! Jeder macht mal Fehler...", xxFatal, l_scan_Attribute.Position);
    break;
  }

  /* implicit: return the EofToken */

/* line 1308 "l_scan.c" */
	    l_scan_ResetScanner ();
	    return l_scan_EofToken;
# endif
	 }
	 break;

      default:
	 yyErrorMessage (xxScannerInternalError);
      }
   }
}

static void yyInitialize ARGS ((void))
   {
      if (yyStateStackSize == 0) {
	 yyStateStackSize = yyInitBufferSize;
	 MakeArray ((char * *) & yyStateStack, & yyStateStackSize,
		       (unsigned long) sizeof (yyStateRange));
	 if (yyStateStack == NULL) yyErrorMessage (xxScannerOutOfMemory);
	 yyStateStack [0] = yyDefaultState;
      }
# if yyInitFileStackSize != 0
      if (yyFileStackSize == 0) {
	 yyFileStackSize = yyInitFileStackSize;
	 MakeArray ((char * *) & yyFileStack, & yyFileStackSize,
			(unsigned long) sizeof (yytFileStack));
	 if (yyFileStack == NULL) yyErrorMessage (xxScannerOutOfMemory);
	 yyFileStackPtr = yyFileStack;
      }

      if (yyFileStackPtr >= yyFileStack + yyFileStackSize - 1) {
	 ptrdiff_t yyyFileStackPtr = yyFileStackPtr - yyFileStack;
	 ExtendArray ((char * *) & yyFileStack, & yyFileStackSize,
			   (unsigned long) sizeof (yytFileStack));
	 if (yyFileStack == NULL) yyErrorMessage (xxScannerOutOfMemory);
	 yyFileStackPtr = yyFileStack + yyyFileStackPtr;
      }
      yyFileStackPtr ++;			/* push file */
      yyFileStackPtr->yySourceFile	= yySourceFile		;
      yyFileStackPtr->yyEof		= yyEof			;
      yyFileStackPtr->yyChBufferPtr	= yyChBufferPtr		;
      yyFileStackPtr->yyChBufferStart	= yyChBufferStart	;
      yyFileStackPtr->yyChBufferSize	= yyChBufferSize	;
      yyFileStackPtr->yyChBufferIndex	= yyChBufferIndex	;
      yyFileStackPtr->yyBytesRead	= yyBytesRead		;
      yyFileStackPtr->yyFileOffset	= yyFileOffset		;
      yyFileStackPtr->yyLineCount	= yyLineCount		;
      yyFileStackPtr->yyLineStart	= yyLineStart		;
# endif
						/* initialize file state */
      yyChBufferSize	   = yyInitBufferSize;
      MakeArray ((char * *) & yyChBufferPtr, & yyChBufferSize,
			(unsigned long) sizeof (yytChar));
      if (yyChBufferPtr == NULL) yyErrorMessage (xxScannerOutOfMemory);
      yyChBufferStart	   = & yyChBufferPtr [yyMaxAlign];
      yyChBufferStart2	   = (yytChar *) yyChBufferStart;
      yyChBufferStart [-1] = yyEolCh;		/* begin of line indicator */
      yyChBufferStart [ 0] = yyEobCh;		/* end of buffer sentinel */
      yyChBufferStart [ 1] = '\0';
      yyChBufferIndex	   = yyChBufferStart;
      l_scan_TokenPtr	   = (yytChar *) yyChBufferStart;
      yyEof		   = rfalse;
      yyBytesRead	   = 0;
      yyFileOffset	   = 0;
      yyLineCount	   = 1;
      yyLineStart	   = & yyChBufferStart [-1];
# ifdef HAVE_FILE_NAME
      if (l_scan_Attribute.Position.FileName == 0)
	 l_scan_Attribute.Position.FileName = 1; /* NoIdent */
# endif
   }

void l_scan_BeginFile
# ifdef HAVE_ARGS
   (char * yyFileName)
# else
   (yyFileName) char * yyFileName;
# endif
   {
      yyInitialize ();
      yySourceFile = yyFileName == NULL ? StdIn :
# ifdef SOURCE_VER
	 l_scan_BeginSourceFile (yyFileName);
# else
	 l_scan_BeginSource (yyFileName);
# endif
      if (yySourceFile < 0) yyErrorMessage (xxCannotOpenInputFile);
   }

# ifdef SOURCE_VER

# if HAVE_WCHAR_T

void l_scan_BeginFileW
# ifdef HAVE_ARGS
   (wchar_t * yyFileName)
# else
   (yyFileName) wchar_t * yyFileName;
# endif
   {
      yyInitialize ();
      yySourceFile = yyFileName == NULL ? StdIn :
	 l_scan_BeginSourceFileW (yyFileName);
      if (yySourceFile < 0) yyErrorMessage (xxCannotOpenInputFile);
   }

# endif

void l_scan_BeginMemory
# ifdef HAVE_ARGS
   (void * yyInputPtr)
# else
   (yyInputPtr) void * yyInputPtr;
# endif
   {
      yyInitialize ();
      l_scan_BeginSourceMemory (yyInputPtr);
   }

void l_scan_BeginMemoryN
# ifdef HAVE_ARGS
   (void * yyInputPtr, int yyLength)
# else
   (yyInputPtr, yyLength) void * yyInputPtr; int yyLength;
# endif
   {
      yyInitialize ();
      l_scan_BeginSourceMemoryN (yyInputPtr, yyLength);
   }

void l_scan_BeginGeneric
# ifdef HAVE_ARGS
   (void * yyInputPtr)
# else
   (yyInputPtr) void * yyInputPtr;
# endif
   {
      yyInitialize ();
      l_scan_BeginSourceGeneric (yyInputPtr);
   }

# endif

void l_scan_CloseFile ARGS ((void))
   {
# if yyInitFileStackSize != 0
      if (yyFileStackPtr == yyFileStack) yyErrorMessage (xxFileStackUnderflow);
# endif
      l_scan_CloseSource (yySourceFile);
      ReleaseArray ((char * *) & yyChBufferPtr, & yyChBufferSize,
			(unsigned long) sizeof (yytChar));
# if yyInitFileStackSize != 0
						/* pop file */
      yySourceFile	= yyFileStackPtr->yySourceFile		;
      yyEof		= yyFileStackPtr->yyEof			;
      yyChBufferPtr	= yyFileStackPtr->yyChBufferPtr		;
      yyChBufferStart	= yyFileStackPtr->yyChBufferStart	;
      yyChBufferStart2	= (yytChar *) yyChBufferStart		;
      yyChBufferSize	= yyFileStackPtr->yyChBufferSize	;
      yyChBufferIndex	= yyFileStackPtr->yyChBufferIndex	;
      yyBytesRead	= yyFileStackPtr->yyBytesRead		;
      yyFileOffset	= yyFileStackPtr->yyFileOffset		;
      yyLineCount	= yyFileStackPtr->yyLineCount		;
      yyLineStart	= yyFileStackPtr->yyLineStart		;
      yyFileStackPtr --;
# endif
   }

# ifdef xxGetWord
int l_scan_GetWord
# ifdef HAVE_ARGS
   (yytChar * yyWord)
# else
   (yyWord) yytChar * yyWord;
# endif
   {
      register yytChar * yySource		= l_scan_TokenPtr;
      register yytChar * yyTarget		= yyWord;
      register yytChar * yyChBufferIndexReg	= (yytChar *) yyChBufferIndex;

      while (yySource < yyChBufferIndexReg)
	 * yyTarget ++ = * yySource ++;
      * yyTarget = '\0';
      return (int) (yyChBufferIndexReg - l_scan_TokenPtr);
   }
# endif

# ifdef xxGetLower
int l_scan_GetLower
# ifdef HAVE_ARGS
   (yytChar * yyWord)
# else
   (yyWord) yytChar * yyWord;
# endif
   {
      register yytusChar * yySource	= (yytusChar *) l_scan_TokenPtr;
      register yytusChar * yyTarget	= (yytusChar *) yyWord;
      register yytusChar * yyChBufferIndexReg = yyChBufferIndex;

      while (yySource < yyChBufferIndexReg)
	 * yyTarget ++ = yyToLower (* yySource ++);
      * yyTarget = '\0';
      return (int) (yyChBufferIndexReg - (yytusChar *) l_scan_TokenPtr);
   }
# endif

# ifdef xxGetUpper
int l_scan_GetUpper
# ifdef HAVE_ARGS
   (yytChar * yyWord)
# else
   (yyWord) yytChar * yyWord;
# endif
   {
      register yytusChar * yySource	= (yytusChar *) l_scan_TokenPtr;
      register yytusChar * yyTarget	= (yytusChar *) yyWord;
      register yytusChar * yyChBufferIndexReg = yyChBufferIndex;

      while (yySource < yyChBufferIndexReg)
	 * yyTarget ++ = yyToUpper (* yySource ++);
      * yyTarget = '\0';
      return (int) (yyChBufferIndexReg - (yytusChar *) l_scan_TokenPtr);
   }
# endif

# ifdef xxinput
static yytChar input ARGS ((void))
   {
      if (yyChBufferIndex == & yyChBufferStart [yyBytesRead]) {
	 if (! yyEof) {
	    yyLineStart -= yyBytesRead;
	    yyChBufferIndex = yyChBufferStart = & yyChBufferPtr [yyMaxAlign];
	    yyChBufferStart2 = (yytChar *) yyChBufferStart;
	    yyFileOffset += yyBytesRead;
	    yyBytesRead = yyGetLine (yySourceFile, (yytChar *) yyChBufferIndex,
	       (int) Exp2 (Log2 (yyChBufferSize)));
	    if (yyBytesRead <= 0) { yyBytesRead = 0; yyEof = rtrue; }
	    yyChBufferStart [yyBytesRead    ] = yyEobCh;
	    yyChBufferStart [yyBytesRead + 1] = '\0';
	 }
      }
      if (yyChBufferIndex == & yyChBufferStart [yyBytesRead]) return '\0';
      else return * yyChBufferIndex ++;
   }
# endif

static void unput
# ifdef HAVE_ARGS
   (yytChar yyc)
# else
   (yyc) yytChar yyc;
# endif
   { * (-- yyChBufferIndex) = yyc; }

static void yyLess
# ifdef HAVE_ARGS
   (int yyn)
# else
   (yyn) int yyn;
# endif
   { yyChBufferIndex -= l_scan_TokenLength - yyn; l_scan_TokenLength = yyn; }

void l_scan_BeginScanner ARGS ((void))
   {
   }

void l_scan_CloseScanner ARGS ((void))
   {
   }

void l_scan_ResetScanner ARGS ((void))
   {
      yyChBufferPtr	= yyInitChBuffer;
      yyChBufferSize	= 0;
      yyChBufferStart	= & yyInitChBuffer [16];
      yyChBufferIndex	= & yyInitChBuffer [16];
      if (yyStateStackSize != 0)
	 ReleaseArray ((char * *) & yyStateStack, & yyStateStackSize,
			(unsigned long) sizeof (yyStateRange));
      yyStateStack	= yyInitStateStack;
      yyStateStackSize	= 0;
# if yyInitFileStackSize != 0
      if (yyFileStackSize != 0)
	 ReleaseArray ((char * *) & yyFileStack, & yyFileStackSize,
			(unsigned long) sizeof (yytFileStack));
      yyFileStackSize	= 0;
# endif
# if defined xxyyPush | defined xxyyPop
      if (yyStStStackSize != 0)
	 ReleaseArray ((char * *) & yyStStStackPtr, & yyStStStackSize,
			(unsigned long) sizeof (yyStateRange));
      yyStStStackSize	= 0;
      yyStStStackIdx	= 0;
# endif
      yyStartState	= STD;
      yyPreviousStart	= STD;
      yySourceFile	= StdIn;
   }

static void yyErrorMessage
# ifdef HAVE_ARGS
   (int yyErrorCode)
# else
   (yyErrorCode) int yyErrorCode;
# endif
   {
      ErrorMessageI (yyErrorCode, xxFatal, l_scan_Attribute.Position,
	 xxString, "l_scan");
      l_scan_Exit ();
   }
