# ifndef yyl_scan
# define yyl_scan

/* $Id: Scanner.h,v 2.18 2005/03/24 17:43:29 grosch rel $ */

# include "config.h"
# if HAVE_WCHAR_H
#  include <wchar.h>
# endif
# include "ratc.h"

/* line 10 "l.rex" */

/* code to be put into Scanner.h */

# include "Position.h"

/* Token Attributes.
 * For each token with user defined attributes, we need a typedef for the
 * token attributes.
 * The first struct-field must be of type tPosition!
 */
typedef struct {tPosition Pos; char* Value;} tint_const;
typedef struct {tPosition Pos; char* Value;} tfloat_const;
typedef struct {tPosition Pos; char* Value;} tidentifier;
typedef struct {tPosition Pos; char* Value;} tstring_const;

/* There is only one "actual" token, during scanning. Therfore
 * we use a UNION of all token-attributes as data type for that unique
 * token-attribute variable.
 * All token (with and without user defined attributes) have one
 * attribute: the source position:
 *     tPosition     Position;
 */
typedef union {
  tPosition     Position;
  tint_const    int_const;
  tfloat_const  float_const;
  tidentifier   identifier;
  tstring_const string_const;
} l_scan_tScanAttribute;

/* Tokens are coded as int's, with values >=0
 * The value 0 is reserved for the EofToken, which is defined automatically
 */
# define tok_int_const    	1
# define tok_float_const  	2
# define tok_identifier   	3
# define tok_string_const 	4

# define tok_PROGRAM      	5
# define tok_DECLARATIONS 	6

# define tok_INPUT        	7
# define tok_OUTPUT 		8

# define tok_STRING 		9
# define tok_INT 		10
# define tok_FLOAT 		11

# define tok_BEGIN 		12
# define tok_END 		13

# define tok_IF 		14
# define tok_THEN 		15
# define tok_ELSE 		16
# define tok_ENDIF 		17

# define tok_WHILE 		18
# define tok_DO 		19
# define tok_ENDWHILE 		20

# define tok_FOR 		21
# define tok_SEMICOLON 		22
# define tok_ENDFOR 		23

# define tok_LT		 	24
# define tok_GT          	25
# define tok_EQUALS      	26

# define tok_ASSIGN 		27

# define tok_PLUS 		28
# define tok_MINUS 		29
# define tok_MULT 		30
# define tok_DIVIDE 		31

# define tok_BRACKETOP   	32
# define tok_BRACKETCL	 	33


/* line 92 "l_scan.h" */

# define l_scan_EofToken	0
# define l_scan_xxMaxCharacter	255

# ifndef l_scan_xxtChar
#  if l_scan_xxMaxCharacter < 256
#   define l_scan_xxtChar	char
#  else
#   define l_scan_xxtChar	wchar_t
#  endif
# endif

# ifndef l_scan_xxtusChar
#  if l_scan_xxMaxCharacter < 256
#   define l_scan_xxtusChar	unsigned char
#  else
#   define l_scan_xxtusChar	wchar_t
#  endif
# endif

# ifdef lex_interface
#  define l_scan_GetToken	yylex
#  define l_scan_TokenLength	yyleng
# endif

extern l_scan_xxtChar *	l_scan_TokenPtr	;
extern int		l_scan_TokenLength	;
extern l_scan_tScanAttribute	l_scan_Attribute	;
extern void		(* l_scan_Exit) ARGS ((void));

extern void	l_scan_BeginScanner	ARGS ((void));
extern void	l_scan_BeginFile	ARGS ((char * yyFileName));
# if HAVE_WCHAR_T
extern void	l_scan_BeginFileW	ARGS ((wchar_t * yyFileName));
# endif
extern void	l_scan_BeginMemory	ARGS ((void * yyInputPtr));
extern void	l_scan_BeginMemoryN	ARGS ((void * yyInputPtr, int yyLength));
extern void	l_scan_BeginGeneric	ARGS ((void * yyInputPtr));
extern int	l_scan_GetToken	ARGS ((void));
extern int	l_scan_GetWord 	ARGS ((l_scan_xxtChar * yyWord));
extern int	l_scan_GetLower	ARGS ((l_scan_xxtChar * yyWord));
extern int	l_scan_GetUpper	ARGS ((l_scan_xxtChar * yyWord));
extern void	l_scan_CloseFile	ARGS ((void));
extern void	l_scan_CloseScanner	ARGS ((void));
extern void	l_scan_ResetScanner	ARGS ((void));

# endif
