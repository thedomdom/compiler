/* Project:  COCKTAIL training
 * Descr:    A recursive Decent Parser for expressions
 * Kind:     The parser (solution)
 * Author:   Prof. Dr. Juergen Vollmer <juergen.vollmer@dhbw-karlsruhe.de>
 * $Id: parser.c.in,v 1.7 2014/11/27 08:49:30 vollmer Exp $
 */

# include <stdlib.h>
# include <string.h>
# include "expr_scan.h"
# include "parser.h"
# include "Errors.h"
      	/* contains: `Message', `MessageI', `xxFatal', `xxError' */

tToken CurToken;

/*****************************************************************************
 * helpers
 *****************************************************************************/

/* Debugging:  if the C-compiler is called with `-DDEBUG',
 *             some output will be generated
 */
# ifdef DEBUG
# define DEBUG_show(msg) printf ("%-5s cur = `%s'\n", msg, token2string (CurToken));
# else
# define DEBUG_show(msg)  /* no output */
# endif

static const char* token2string (tToken token)
/* maps token-code to token textual representation */
{
  switch (token) {
  case '+':    return "+";
  case '*':    return "*";
  case '(':    return "(";
  case ')':    return ")";
  case '[':    return "[";
  case ']':    return "]";
  case '.':    return ".";
  case tok_identifier:
    return "identifier";
  case tok_arrow:
    return "->";
  case expr_scan_EofToken:
    return "EOF";
  default:
    /* this should never happen */
    MessageI ("FATAL ERROR: unknown token", xxFatal,
	      expr_scan_Attribute.Position, xxInteger, (char*) &token);
    abort(); /* aborts the program */
  }
}

/*****************************************************************************/

bool match (tToken token)
/* Instead of writing for each token 't' a function 'f_t()', we use 'match (t)'. */
{
# ifdef DEBUG
  printf ("      cur = `%s' expected = `%s'\n", token2string(CurToken), token2string (token));
# endif
  if (CurToken == token) {
    if (CurToken != expr_scan_EofToken) CurToken = expr_scan_GetToken();
    return true;
  } else {
    char msg[255];
    sprintf (msg, "Syntax Error: found: `%s' expected: `%s'",
	     token2string (CurToken), token2string (token));
    Message (msg, xxError, expr_scan_Attribute.Position);
    return false;  /* Syntax Error */
  }
}




/*****************************************************************************
 * First-Follow-set Tests
 ******************************************************************************/


static bool FirstFollow_1 (void)
{
  switch (CurToken) {
  case '(': case tok_identifier:
    return true;
  default:
    return false;
  }
}

static bool FirstFollow_2 (void)
{
  switch (CurToken) {
  case '+':
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_3 (void)
{
  switch (CurToken) {
    case expr_scan_EofToken: case ')': case ']':
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_4 (void)
{
  switch (CurToken) {
  case '(': case tok_identifier:
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_5 (void)
{
  switch (CurToken) {
  case '*':
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_6 (void)
{
  switch (CurToken) {
  case expr_scan_EofToken: case ')': case '+': case ']':
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_7 (void)
{
  switch (CurToken) {
  case '(':
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_8 (void)
{
  switch (CurToken) {
  case tok_identifier:
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_9 (void)
{
  switch (CurToken) {
  case tok_identifier:
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_10 (void)
{
  switch (CurToken) {
  case '[':
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_11 (void)
{
  switch (CurToken) {
  case '.':
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_12 (void)
{
  switch (CurToken) {
  case tok_arrow:
    return true;
  default:
    return false;
  }
}
static bool FirstFollow_13 (void)
{
  switch (CurToken) {
  case expr_scan_EofToken: case ')': case '+': case ']': case '*':
    return true;
  default:
    return false;
  }
}


/*****************************************************************************
 * Given the following grammar:
 *   E ::= E "+" T   | T
 *   T ::= T "*" F   | F
 *   F ::= "(" E ")" | D
 *   D ::= D "." identifier | D "[" E "]" | D "->" identifier | identifier
 * Implement a recurisve decent parser.
 ******************************************************************************/

/* forward-declarations of nonterminal-functions, needed by the langauge C
 * f_expr () is already declared in parser.h
 */
static bool f_E1 (void);
static bool f_T  (void);
static bool f_T1 (void);
static bool f_F  (void);
static bool f_D  (void);
static bool f_D1  (void);

bool f_E (void)
{
  DEBUG_show("E");

  if (FirstFollow_1()) return f_T() && f_E1();
  Message ("Syntax Error in <E>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_E1 (void)
{
  DEBUG_show("E1");

  if (FirstFollow_2()) return match ('+') && f_T() && f_E1();
  if (FirstFollow_3()) return true;
  Message ("Syntax Error in <E1>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_T (void)
{
  DEBUG_show("T");

  if (FirstFollow_4()) return f_F() && f_T1();
  Message ("Syntax Error in <T>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_T1 (void)
{
  DEBUG_show("T1");

  if (FirstFollow_5()) return match ('*') && f_F() && f_T1();
  if (FirstFollow_6()) return true;
  Message ("Syntax Error in <T1>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}

bool f_F (void)
{
  DEBUG_show("F");

  if (FirstFollow_7()) return match ('(') && f_E() && match (')');
  if (FirstFollow_8()) return f_D();
  Message ("Syntax Error in <F>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}
bool f_D (void)
{
  DEBUG_show("D");

  if (FirstFollow_9()) return match (tok_identifier) && f_D1();
  Message ("Syntax Error in <D>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}
bool f_D1 (void)
{
  DEBUG_show("D1");

  if (FirstFollow_10()) return match ('.') && match (tok_identifier) && f_D1();
  if (FirstFollow_11()) return match ('[') && f_E() && match (']') && f_D1();
  if (FirstFollow_12()) return match (tok_arrow) && match (tok_identifier) && f_D1();
  if (FirstFollow_13()) return true;
  Message ("Syntax Error in <D1>", xxError, expr_scan_Attribute.Position);
  return false; /* Syntax Error */
}


/***********************  E  N  D  ***********************************************/
