# ifndef beginint
# define beginint(a)		
# endif
# ifndef closeint
# define closeint(a)		
# endif
# ifndef readint
# define readint(a)		fscanf (yyf, "%d", & a);
# endif
# ifndef writeint
# define writeint(a)		fprintf (yyf, "%d", a);
# endif
# ifndef getint
# define getint(a)		yyGet ((char *) & a, sizeof (a));
# endif
# ifndef putint
# define putint(a)		yyPut ((char *) & a, sizeof (a));
# endif
# ifndef copyint
# define copyint(a, b)		
# endif
# ifndef equalint
# define equalint(a, b)		(a) == (b)
# endif
# ifndef writeXMLint
# define writeXMLint(a)		fprintf (yyf, "%d", a);
# endif
# ifndef begindouble
# define begindouble(a)		
# endif
# ifndef closedouble
# define closedouble(a)		
# endif
# ifndef readdouble
# define readdouble(a)		fscanf (yyf, "%g", & a);
# endif
# ifndef writedouble
# define writedouble(a)		fprintf (yyf, "%g", a);
# endif
# ifndef getdouble
# define getdouble(a)		yyGet ((char *) & a, sizeof (a));
# endif
# ifndef putdouble
# define putdouble(a)		yyPut ((char *) & a, sizeof (a));
# endif
# ifndef copydouble
# define copydouble(a, b)	
# endif
# ifndef equaldouble
# define equaldouble(a, b)	(a) == (b)
# endif
# ifndef writeXMLdouble
# define writeXMLdouble(a)	fprintf (yyf, "%g", a);
# endif
# ifndef beginrbool
# define beginrbool(a)		
# endif
# ifndef closerbool
# define closerbool(a)		
# endif
# ifndef readrbool
# define readrbool(a)		a = fgetc (yyf) == 'T';
# endif
# ifndef writerbool
# define writerbool(a)		fputc (a ? 'T' : 'F', yyf);
# endif
# ifndef getrbool
# define getrbool(a)		yyGet ((char *) & a, sizeof (a));
# endif
# ifndef putrbool
# define putrbool(a)		yyPut ((char *) & a, sizeof (a));
# endif
# ifndef copyrbool
# define copyrbool(a, b)	
# endif
# ifndef equalrbool
# define equalrbool(a, b)	(a) == (b)
# endif
# ifndef writeXMLrbool
# define writeXMLrbool(a)	fputc (a ? 'T' : 'F', yyf);
# endif
# ifndef beginchar
# define beginchar(a)		
# endif
# ifndef closechar
# define closechar(a)		
# endif
# ifndef readchar
# define readchar(a)		a = fgetc (yyf);
# endif
# ifndef writechar
# define writechar(a)		fputc (a, yyf);
# endif
# ifndef getchar
# define getchar(a)		yyGet ((char *) & a, sizeof (a));
# endif
# ifndef putchar
# define putchar(a)		yyPut ((char *) & a, sizeof (a));
# endif
# ifndef copychar
# define copychar(a, b)		
# endif
# ifndef equalchar
# define equalchar(a, b)	(a) == (b)
# endif
# ifndef writeXMLchar
# define writeXMLchar(a)	yyWriteCharXML (a);
# endif
# ifndef begintIdent
# define begintIdent(a)		a = NoIdent;
# endif
# ifndef closetIdent
# define closetIdent(a)		
# endif
# ifndef readtIdent
# define readtIdent(a)		a = yyReadIdent ();
# endif
# ifndef writetIdent
# define writetIdent(a)		WriteIdent (yyf, a);
# endif
# ifndef gettIdent
# define gettIdent(a)		yyGetIdent (& a);
# endif
# ifndef puttIdent
# define puttIdent(a)		yyPutIdent (a);
# endif
# ifndef copytIdent
# define copytIdent(a, b)	
# endif
# ifndef equaltIdent
# define equaltIdent(a, b)	(a) == (b)
# endif
# ifndef writeXMLtIdent
# define writeXMLtIdent(a)	yyWriteStringXML (GetCStr (a));
# endif
# ifndef begintPosition
# define begintPosition(a)	a = NoPosition;
# endif
# ifndef closetPosition
# define closetPosition(a)	
# endif
# ifndef readtPosition
# define readtPosition(a)	ReadPosition (yyf, & a);
# endif
# ifndef writetPosition
# define writetPosition(a)	WritePosition (yyf, a);
# endif
# ifndef gettPosition
# define gettPosition(a)	yyGet ((char *) & a, sizeof (a));
# endif
# ifndef puttPosition
# define puttPosition(a)	yyPut ((char *) & a, sizeof (a));
# endif
# ifndef copytPosition
# define copytPosition(a, b)	
# endif
# ifndef equaltPosition
# define equaltPosition(a, b)	Compare (a, b) == 0
# endif
# ifndef writeXMLtPosition
# define writeXMLtPosition(a)	WritePosition (yyf, a);
# endif
# ifndef beginNodeHead
# define beginNodeHead(a)	
# endif
# ifndef closeNodeHead
# define closeNodeHead(a)	
# endif
# ifndef readNodeHead
# define readNodeHead(a)	
# endif
# ifndef writeNodeHead
# define writeNodeHead(a)	
# endif
# ifndef getNodeHead
# define getNodeHead(a)		
# endif
# ifndef putNodeHead
# define putNodeHead(a)		
# endif
# ifndef copyNodeHead
# define copyNodeHead(a, b)	
# endif
# ifndef equalNodeHead
# define equalNodeHead(a, b)	rtrue
# endif
# ifndef writeXMLNodeHead
# define writeXMLNodeHead(a)	
# endif
# ifndef begintTree
# define begintTree(a)	a = NoTree;
# endif
# ifndef closetTree
# define closetTree(a)
# endif
# ifndef readtTree
# define readtTree(a)	fscanf (yyf, "%p +", (void * *) & a);
# endif
# ifndef writetTree
# define writetTree(a)	fprintf (yyf, "%p +", (void *) a);
# endif
# ifndef gettTree
# define gettTree(a)	yyGet ((char *) & a, sizeof (a));
# endif
# ifndef puttTree
# define puttTree(a)	yyPut ((char *) & a, sizeof (a));
# endif
# ifndef copytTree
# define copytTree(a, b)	a = b;
# endif
# ifndef equaltTree
# define equaltTree(a, b)	a == b
# endif
# ifndef writeXMLtTree
# define writeXMLtTree(a)	yyWriteAddrXML ((void *) a);
# endif
# ifndef readSELECTOR
# define readSELECTOR()	yySkip ();
# endif
# ifndef writeSELECTOR
# define writeSELECTOR(a)	yyIndentSelector (a);
# endif
