# ifndef yyexpr
# define yyexpr

# include "ratc.h"

# include "Tree.h"

/* line 17 "expr.puma" */

 # include "Position.h"
 # include "Idents.h"


extern void (* expr_Exit) ARGS ((void));

extern void interpreteStmts ARGS ((tTree tree));

extern void Beginexpr ARGS ((void));
extern void Closeexpr ARGS ((void));

# endif
