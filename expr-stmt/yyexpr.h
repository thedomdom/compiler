# ifndef beginint
# define beginint(a)		
# endif
# ifndef equalint
# define equalint(a, b)		(a) == (b)
# endif
# ifndef begindouble
# define begindouble(a)		
# endif
# ifndef equaldouble
# define equaldouble(a, b)	(a) == (b)
# endif
# ifndef beginchar
# define beginchar(a)		
# endif
# ifndef equalchar
# define equalchar(a, b)	(a) == (b)
# endif
# ifndef begintIdent
# define begintIdent(a)		a = NoIdent;
# endif
# ifndef equaltIdent
# define equaltIdent(a, b)	(a) == (b)
# endif
# ifndef begintPosition
# define begintPosition(a)	a = NoPosition;
# endif
# ifndef equaltPosition
# define equaltPosition(a, b)	Compare (a, b) == 0
# endif
# ifndef beginNodeHead
# define beginNodeHead(a)	
# endif
# ifndef equalNodeHead
# define equalNodeHead(a, b)	rtrue
# endif
# ifndef begintTree
# define begintTree(a)	a = NULL;
# endif
# ifndef equaltTree
# define equaltTree(a, b)	IsEqualTree (a, b)
# endif
