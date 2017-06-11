#@ line 1
/* Project:  COCKTAIL training
 * Descr:    A simple pocket computer (scanner, parser, evaluator)
 * Kind:     Scanner specification
 * Author:   Prof. Dr. Juergen Vollmer <vollmer@dhbw-karlsruhe.de>
 * $Id: expr.scan,v 1.2 2010/04/26 14:07:24 vollmer Exp $
 */

SCANNER expr_scan

EXPORT {
/* code to be put into Scanner.h */
# include "Position.h"
# include "Idents.h"

/* Token Attributes.
 * For each token with user defined attributes, we need a typedef for the
 * token attributes.
 * LPP extracts the token-attribute declaration from the parser specification.
 * They are inserted here.
 */

#@ line 24
# ifndef CommonScanAttrs
# define CommonScanAttrs
# endif

# define zzCommonScanAttrs tPosition Position; CommonScanAttrs

typedef struct { zzCommonScanAttrs long Value; } zz_expr_scan_int_const;
typedef struct { zzCommonScanAttrs double Value; } zz_expr_scan_float_const;
typedef struct { zzCommonScanAttrs tIdent Ident; } zz_expr_scan_identifier;

typedef union {
tPosition Position;
struct { zzCommonScanAttrs } Common;
zz_expr_scan_int_const int_const;
zz_expr_scan_float_const float_const;
zz_expr_scan_identifier identifier;
} expr_scan_tScanAttribute;

# undef zzCommonScanAttrs

extern void expr_scan_ErrorAttribute ARGS((int Token, expr_scan_tScanAttribute * pAttribute));
#@ line 21

}

GLOBAL {
/* code to be put into Scanner.c */
# include <stdlib.h>
# include "Errors.h"

/* Insert the routine computing "error-values" of attributes, in case the
 * parser decides during error repair to insert a token.
 */

#@ line 59
void expr_scan_ErrorAttribute
# ifdef HAVE_ARGS
 (int Token, expr_scan_tScanAttribute * pAttribute)
# else
 (Token, pAttribute) int Token; expr_scan_tScanAttribute * pAttribute;
# endif
{
 pAttribute->Position = expr_scan_Attribute.Position;
 switch (Token) {
 case /* int_const */ 1: 
pAttribute->int_const.Value = 0;
  	 break;
 case /* float_const */ 2: 
pAttribute->float_const.Value = 0.0;
	 break;
 case /* identifier */ 3: 
pAttribute->identifier.Ident = NoIdent;
 break;
 }
}
#@ line 32

}

LOCAL {
/* user-defined local variables of the generated GetToken routine */
# define MAX_STRING_LEN 2048
char string[MAX_STRING_LEN];
int nesting = 0;
}

DEFAULT {
  /* What happens if no scanner rule matches the input */
  MessageI ("Illegal character",
	    xxError, expr_scan_Attribute.Position,
	    xxCharacter, expr_scan_TokenPtr);
}

EOF {
  /* What should be done if the end-of-input-file has been reached? */

  /* E.g.: check hat strings and comments are closed. */
  switch (yyStartState) {
  case STD:
    /* ok */
    break;
  case COMMENT:
    Message ("unclosed C-comment",
	     xxError, expr_scan_Attribute.Position);
    break;
  case COMMENT2:
    Message ("unclosed Modula-comment",
	     xxError, expr_scan_Attribute.Position);
    break;
  default:
    Message ("OOPS: that should not happen!!",
	     xxFatal, expr_scan_Attribute.Position);
    break;
  }

  /* implicit: return the EofToken */
}

DEFINE /* some abbreviations */
  letter = {a-zA-Z_} .
  digit  = {0-9}     .

/* define start states, note STD is defined by default */
START COMMENT, COMMENT2

RULES


#@ line 133
 #STD#\:\=	: { return 4; }
 #STD#pi	: { return 5; }
 #STD#\(	: { return 6; }
 #STD#\)	: { return 7; }
 #STD#\+	: { return 8; }
 #STD#\-	: { return 9; }
 #STD#\*	: { return 10; }
 #STD#\/	: { return 11; }
 #STD#\^	: { return 12; }
 #STD#\?	: { return 13; }
 #STD#\:	: { return 14; }
 #STD#\>	: { return 15; }
 #STD#\<	: { return 16; }
 #STD#\=	: { return 17; }
 #STD#\&	: { return 18; }
 #STD#\|	: { return 19; }
 #STD#\!	: { return 20; }
 #STD#\,	: { return 21; }
 #STD#IF	: { return 22; }
 #STD#THEN	: { return 23; }
 #STD#ELSE	: { return 24; }
 #STD#ELSEIF	: { return 25; }
 #STD#END	: { return 26; }
 #STD#WHILE	: { return 27; }
 #STD#DO	: { return 28; }
 #STD#PRINT	: { return 29; }
 #STD#\;	: { return 30; }
#@ line 84

/* Integers */
#STD# {0-9}+ :
	{expr_scan_GetWord (string);
	 expr_scan_Attribute.int_const.Value = atol (string);
	 return 1;
	}

/* Float numbers */
#STD# digit + "." digit * (("E"|"e") ("+"|"-") ? digit +) ? :
	{expr_scan_GetWord (string);
	 expr_scan_Attribute.float_const.Value = atof (string);
	 return 2;
	}

/* identifier */
#STD# letter (letter | digit)* :
	{ expr_scan_Attribute.identifier.Ident =
			MakeIdent (expr_scan_TokenPtr, expr_scan_TokenLength);
	  return 3;
	}

#STD# < "--" ANY * > :
        { /* comment up to end of line, nothing to do */
        }

/* C-style comment */
#STD# "/*" :
	{ /**/
	  yyStart (COMMENT);
	}

#COMMENT# - {*\n\t} + | "*" :
        {}

#COMMENT# "*/" :
        {yyStart (STD);
	}

/* Modula2-style nested comment */
#STD,COMMENT2# "(*" :
	{ yyStart (COMMENT2);
	  nesting ++;
	}

#COMMENT2# - {*(\n\t} + | "*" | "(" :
        {}

#COMMENT2# "*)" :
        { nesting --;
	  if (nesting == 0) {
	    yyStart (STD);
	  }
	}

/**********************************************************************/
