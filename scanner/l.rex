/* Project:  COCKTAIL training
 * Descr:    a simple scanner generated with rex
 * Kind:     REX scanner specification (solution)
 * Author:   Dr. Juergen Vollmer <juergen.vollmer@informatik-vollmer.de>
 * $Id: l.rex.in,v 1.13 2016/11/11 10:38:11 vollmer Exp $
 */

SCANNER l_scan

EXPORT {
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

} // EXPORT

GLOBAL {
  # include <stdlib.h>
  # include "rString.h"
  
} // GLOBAL

LOCAL {
 /* user-defined local variables of the generated GetToken routine */
  # define MAX_STRING_LEN 2048
  char string [MAX_STRING_LEN+1];
  int len;
}  // LOCAL

DEFAULT {
  /* What happens if no scanner rule matches the input */
  /*MessageI ("Unzulaessiges Zeichen", xxError, l_scan_Attribute.Position, xxCharacter, (char*)*l_scan_TokenPtr);*/
  Message ("Unzulaessiges Zeichen", xxError, l_scan_Attribute.Position);
} // DEFAULT

EOF {
  /* What should be done if the end-of-input-file has been reached? */

  /* E.g.: check hat strings and comments are closed. */
  switch (yyStartState) {
  case STD:
    /* ok */
    break;
  case STRING:
   Message ("Nicht abgeschlossene Stringkonstante", xxError, l_scan_Attribute.Position);
   break;
  case COMMENT:
    Message ("Nicht abgeschlossener mehrzeiliger Kommentar", xxError, l_scan_Attribute.Position);
    break;
  default:
    Message ("UUPSI: Das sollte nicht passieren!! Jeder macht mal Fehler...", xxFatal, l_scan_Attribute.Position);
    break;
  }

  /* implicit: return the EofToken */
} // EOF

DEFINE  /* some abbreviations */
      digit  = {0-9}         .
      letter = {a-z_A-Z}     .
      string = - {"\\\n\r\f} .

/* define start states, note STD is defined by default, separate several states by a comma */
START STRING, COMMENT

RULE

/* Integers */
#STD# digit + :
	{l_scan_Attribute.int_const.Value = malloc (l_scan_TokenLength+1);
	 l_scan_GetWord (l_scan_Attribute.int_const.Value);
	 return tok_int_const;
	}

/* Please add rules for: (don't forget to adapt main()) */
/* Float numbers */
#STD# digit * "." digit + :
	{
		l_scan_Attribute.float_const.Value = malloc(l_scan_TokenLength+1);
		l_scan_GetWord(l_scan_Attribute.float_const.Value);
		return tok_float_const;
	}

/* case insensitive keywords: BEGIN PROCEDURE END CASE */
#STD# {Pp} {Rr} {Oo} {Gg} {Rr} {Aa} {Mm}          			: {return tok_PROGRAM;}
#STD# {Dd} {Ee} {Cc} {Ll} {Aa} {Rr} {Aa} {Tt} {Ii} {Oo}  {Nn}  {Ss}     : {return tok_DECLARATIONS;}
#STD# {Ii} {Nn}  {Pp} {Uu} {Tt}                   			: {return tok_INPUT;}
#STD# {Oo} {Uu} {Tt} {Pp} {Uu} {Tt}               			: {return tok_OUTPUT;}

#STD# {Ss} {Tt} {Rr} {Ii} {Nn} {Gg}					: {return tok_STRING;}
#STD# {Ii} {Nn} {Tt}							: {return tok_INT;}

#STD# {Ff} {Ll} {Oo} {Aa} {Tt}						: {return tok_FLOAT;}

#STD# {Bb} {Ee} {Gg} {Ii} {Nn}                    			: {return tok_BEGIN;}
#STD# {Ee} {Nn} {Dd} {.}                             			: {return tok_END;}

#STD# {Ii} {Ff}								: {return tok_IF;}
#STD# {Tt} {Hh} {Ee} {Nn}						: {return tok_THEN;}
#STD# {Ee} {Ll} {Ss} {Ee}						: {return tok_ELSE;}
#STD# {Ee} {Nn} {Dd} {Ii} {Ff} {.}					: {return tok_ENDIF;}

#STD# {Ww} {Hh} {ii} {Ll} {Ee}						: {return tok_WHILE;}
#STD# {Dd} {Oo}								: {return tok_DO;}
#STD# {Ee} {Nn} {Dd} {Ww} {Hh} {Ii} {Ll} {Ee} {.}			: {return tok_ENDWHILE;}

#STD# {Ff} {Oo} {Rr}							: {return tok_FOR;}
#STD# {;}								: {return tok_SEMICOLON;}
#STD# {Ee} {Nn} {Dd} {Ff} {Oo} {Rr} {.} 				: {return tok_ENDFOR;}

#STD# ">"					  			: {return tok_GT;}
#STD# "<" 					  			: {return tok_LT;}
#STD# {=}     			    					: {return tok_ASSIGN;}
#STD# {=} {=}         							: {return tok_EQUALS;}

#STD# {+}      								: {return tok_PLUS;}
#STD# "-"					  			: {return tok_MINUS;}
#STD# {*} 					        		: {return tok_MULT;}
#STD# {/}								: {return tok_DIVIDE;}

#STD# "(" :
	{
		return tok_BRACKETOP;
	}
	
#STD# ")" :
	{
		return tok_BRACKETCL;
	}

/* identifiers */
#STD# letter (letter | digit) * :
	{
		l_scan_Attribute.identifier.Value = malloc(l_scan_TokenLength+1);
		l_scan_GetWord(l_scan_Attribute.identifier.Value);
		return tok_identifier;
	}

/* comment up to end of line */
#STD# < "--" ANY * > :
        { /* comment up to end of line, nothing to do */
	  WritePosition (stdout, l_scan_Attribute.Position);
	  printf (" Einzeiliger Kommentar\n");
        }
        
/* C-style comment */
#STD# "/*" :
	{ /**/
	  yyStart (COMMENT);
	  WritePosition (stdout, l_scan_Attribute.Position);
	  printf (" Beginn eines mehrzeiligen Kommentars\n");
	}

#COMMENT# - {*\n\t} + | "*" :
        {}

#COMMENT# "*/" :
        {yyStart (STD);
	 WritePosition (stdout, l_scan_Attribute.Position);
	 printf (" Ende des mehrzeiligen Kommentars\n");
	}

/* double quote delimited strings */
#STD# \" :
	{ /* start of string */
          yyStart (STRING);
	  len = 0;
	}
#STRING# string* :
	{ /* we're inside the string */
          if (len + l_scan_TokenLength+1 >= MAX_STRING_LEN) {
	    Message ("String zu lang", xxError, l_scan_Attribute.Position);
	    len = 0;
	  } else {
  	    len += l_scan_GetWord (&string[len]);
	  }
        }
#STRING# \" :
	{ /* end of string */
          yyStart(STD);
	  string[len] = '\0';
	  l_scan_Attribute.string_const.Value = malloc (len+1);
	  strcpy (l_scan_Attribute.string_const.Value, string);
	  return tok_string_const;
        }
#STRING# \\ \" :
	{ /* transform the \" characters to a single " */
          if (len + 1 >= MAX_STRING_LEN) {
	    Message ("String zu lang", xxError, l_scan_Attribute.Position);
            len = 0;
	  } else {
  	    string[len++] = '"';
          }
	}
#STRING# \\ n :
	{ /* transform the \n characters to a single " */
          if (len + 1 >= MAX_STRING_LEN) {
	    Message ("String zu lang", xxError, l_scan_Attribute.Position);
            len = 0;
	  } else {
  	    string[len++] = '\n';
	  }
	}
#STRING# \\ :
	{ /* special treatment of the \-character */
          if (len + 1 >= MAX_STRING_LEN) {
	    Message ("String zu lang", xxError, l_scan_Attribute.Position);
            len = 0;
	  } else {
  	    string[len++] = '\\';
	  }
	}

/**********************************************************************/

