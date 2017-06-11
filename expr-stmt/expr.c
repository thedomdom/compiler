# include "expr.h"

# ifndef EXTERN_C_BEGIN
# define EXTERN_C_BEGIN
# define EXTERN_C_END
# endif

EXTERN_C_BEGIN
# include "General.h"
# include "rString.h"
# include "rSystem.h"
# include "Errors.h"
EXTERN_C_END

# include <stdio.h>

# define yyInline
# ifndef NULL
# define NULL 0L
# endif
# ifndef rfalse
# define rfalse 0
# endif
# ifndef rtrue
# define rtrue 1
# endif

# ifdef yyInline
# define yyALLOC(tree, free, start, alloc, type, make, ptr, kind, init) \
  ptr = (free -= yyAlignedSize (sizeof (type))) >= start ? \
   (tree) free : alloc (sizeof (type)); \
  init (ptr, kind);
# else
# define yyALLOC(tree, free, start, alloc, type, make, ptr, kind, init) \
  ptr = make (kind);
# endif

static void yyExit ARGS ((void)) { rExit (1); }

void (* expr_Exit) ARGS ((void)) = yyExit;

static FILE * yyf = NULL;
static rbool yyb;

/* line 22 "expr.puma" */

 # include <stdlib.h>
 # include <math.h>

 # define FATAL_ERROR() 								      \
  {fprintf (stderr, "***** FATAL ERROR *****: file %s, line %d\n", __FILE__ , __LINE__); abort(); }
/* Indicate a programming error
 * __FILE__  the filename of the source file "calling" the macro
 * __LINE__  the line "calling" this macro
 */


 /* The values of variables are stored in the global array 'storage',
  * which is indexed by the tIdent values representing the variable name.
  * The array elements are automatically initialized to 0.
  * TODO: check that no more than MAX_VARIABLES are used in your program source.
  *       ==> MaxIdents variable in the Idents-module (Idents.h)
  */
 # define MAX_VARIABLES 100
 static double storage[MAX_VARIABLES];

 static double evalBinary (char op, double left, double right, tPosition pos)
 /* compute "left op right"
  * "pos" is the source position of the expression
  *       in case an error message must be emitted.
  * Note: boolean values are represented as double values:
  *          FALSE   ==  0.0
  *          TRUE    ==  any other value
  */
 {
  switch (op) {
  case '+': return left+right;
  case '-': return left-right;
  case '*':  return left*right;
  case '/':  if (right == 0.0) {
               WritePosition (stderr, pos);
               fprintf (stderr, " division by zero\n");
               return 0.0;
             } else {
               return left/right;
             }
  case '^': return pow (left,right);
  case '<': return left <  right;
  case '>': return left >  right;
  case '=': return left == right;
  case '&': return left && right;
  case '|': return left || right;
  default:   	 FATAL_ERROR();
  }
 }

 static double evalUnary (char op, double argument, tPosition pos)
 /* compute "op argument" */
 {
  switch (op) {
  case '-': return -argument;
  case '+': return argument;
  case '!': return argument == 0? 1 : 0;
  default:  FATAL_ERROR();
  }
 }

 static double evalFunction (tIdent name, double argument, tPosition pos)
 {
    if (name == id_sin) return sin (argument);
    if (name == id_cos) return cos (argument);
    if (name == id_tan) return tan (argument);
    WritePosition (stderr, pos);
    fprintf (stderr, " Illegal function name `%s'\n", GetCStr (name));
    return 0.0;
 }


/* For output at high speed the following can be defined in the GLOBAL section
   provided the variable yyf has a defined value. */
/* # define yyWrite(s) (void) fputs (s, yyf) */
/* # define yyWriteNl (void) fputc ('\n', yyf) */

# ifndef yyWrite
# define yyWrite(s) yyWriteString (s)
# endif
# ifndef yyWriteNl
# define yyWriteNl yyWriteString ("\n")
# endif

# include "yyexpr.h"

static void yyWriteString
# ifdef HAVE_ARGS
 (const char * yyString)
# else
 (yyString) char * yyString;
# endif
{
 if (yyf == NULL) yyf = stdout;
 (void) fputs (yyString, yyf);
}

static void yyAbort
# ifdef HAVE_ARGS
 (const char * yyFunction)
# else
 (yyFunction) char * yyFunction;
# endif
{
 char yys [256];
 sprintf (yys, "expr.%s", yyFunction);
 ErrorMessageI (xxRoutineFailed, xxFatal, NoPosition, xxString, yys);
 expr_Exit ();
}

void interpreteStmts ARGS ((tTree tree));
static double evalExpr ARGS ((tTree tree));

void interpreteStmts
# ifdef HAVE_ARGS
(register tTree tree)
# else
(tree)
 register tTree tree;
# endif
{
 yyRecursion:

  if (tree)
  switch (tree->Kind) {
  case kassign_stmt:
  if (tree->assign_stmt.Lhs && tree->assign_stmt.Lhs->Kind == kname) {
/* line 103 "expr.puma" */
  {
/* line 104 "expr.puma" */
   storage [tree->assign_stmt.Lhs->name.Ident] = evalExpr (tree->assign_stmt.Rhs);
/* line 105 "expr.puma" */
   tree = tree->assign_stmt.Next;
   goto yyRecursion;
  }

  }
  break;
  case kif_stmt:
/* line 107 "expr.puma" */
  {
/* line 108 "expr.puma" */
   if (evalExpr (tree->if_stmt.Cond)) {
/* line 109 "expr.puma" */
   interpreteStmts (tree->if_stmt.Then);
   } else {
/* line 110 "expr.puma" */
   interpreteStmts (tree->if_stmt.Else);
   }
/* line 112 "expr.puma" */
   tree = tree->if_stmt.Next;
   goto yyRecursion;
  }

  case kwhile_stmt:
/* line 114 "expr.puma" */
  {
/* line 115 "expr.puma" */
   while (evalExpr (tree->while_stmt.Cond)) {
/* line 117 "expr.puma" */
   interpreteStmts (tree->while_stmt.Body);
   }
/* line 119 "expr.puma" */
   tree = tree->while_stmt.Next;
   goto yyRecursion;
  }

  case kprint_stmt:
/* line 121 "expr.puma" */
  {
/* line 122 "expr.puma" */
   interpreteStmts (tree->print_stmt.Arguments);
/* line 123 "expr.puma" */
   tree = tree->print_stmt.Next;
   goto yyRecursion;
  }

  case kexprs:
/* line 125 "expr.puma" */
  {
/* line 126 "expr.puma" */
   WritePosition (stdout, tree->exprs.Expr->EXPR.Pos);
/* line 127 "expr.puma" */
   printf (" ==> %-8.2f\n", evalExpr (tree->exprs.Expr));
/* line 128 "expr.puma" */
   tree = tree->exprs.Next;
   goto yyRecursion;
  }

  case kno_stmt:
/* line 130 "expr.puma" */
   return;

  case kno_exprs:
/* line 130 "expr.puma" */
   return;

  }

/* line 134 "expr.puma" */
  {
/* line 134 "expr.puma" */
   Message ("interpreteStmts: unknown tree", xxError, NoPosition);
/* line 135 "expr.puma" */
   DrawTree (tree);
  }
   return;

;
}

static double evalExpr
# ifdef HAVE_ARGS
(register tTree tree)
# else
(tree)
 register tTree tree;
# endif
{

  if (tree)
  switch (tree->Kind) {
  case kname:
/* line 144 "expr.puma" */
   return storage [tree->name.Ident];

  case kint_const:
/* line 148 "expr.puma" */
   return tree->int_const.Value;

  case kfloat_const:
/* line 153 "expr.puma" */
   return tree->float_const.Value;

  case kunary_expr:
/* line 156 "expr.puma" */
   return evalUnary (tree->unary_expr.Op, evalExpr (tree->unary_expr.Argument), tree->unary_expr.Pos);

  case kbinary_expr:
/* line 159 "expr.puma" */
   return evalBinary (tree->binary_expr.Op, evalExpr (tree->binary_expr.Left), evalExpr (tree->binary_expr.Right), tree->binary_expr.Pos);

  case kcond_expr:
/* line 162 "expr.puma" */
   return evalExpr (tree->cond_expr.Cond) ? evalExpr (tree->cond_expr.Then) : evalExpr (tree->cond_expr.Else);

  case kcall_expr:
  if (tree->call_expr.Arguments && tree->call_expr.Arguments->Kind == kexprs) {
  if (tree->call_expr.Arguments->exprs.Next && tree->call_expr.Arguments->exprs.Next->Kind == kno_exprs) {
/* line 167 "expr.puma" */
   return evalFunction (tree->call_expr.Name, evalExpr (tree->call_expr.Arguments->exprs.Expr), tree->call_expr.Pos);

  }
  }
/* line 170 "expr.puma" */
  {
/* line 171 "expr.puma" */
   WritePosition (stderr, tree->call_expr.Pos);
/* line 172 "expr.puma" */
   fprintf (stderr, " Wrong number of arguments for function `%s'\n", GetCStr (tree->call_expr.Name));
  }
   return 0.0;

  }

/* line 175 "expr.puma" */
  {
/* line 176 "expr.puma" */
   Message ("evalExpr: unknown tree", xxError, tree->EXPR.Pos);
/* line 177 "expr.puma" */
   DrawTree (tree);
  }
   return 0;

}

void Beginexpr ARGS ((void))
{
}

void Closeexpr ARGS ((void))
{
}
