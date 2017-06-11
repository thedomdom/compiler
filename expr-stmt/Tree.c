# include "Tree.h"

# ifndef EXTERN_C_BEGIN
# define EXTERN_C_BEGIN
# define EXTERN_C_END
# endif

EXTERN_C_BEGIN
# include <stdlib.h>
# include <stddef.h>
# include "rString.h"
# include "rSystem.h"
# include "General.h"
# include "rMemory.h"
# include "DynArray.h"
# include "Idents.h"
# include "Position.h"
# include "Errors.h"
EXTERN_C_END

# ifdef _MSC_VER
#  pragma warning (disable: 4100 4505 4514)
# endif

char Tree_module_does_not_match_evaluator_module_943672;
char generate_Tree_module_without_option_0;

static FILE * yyf;

/* line 23 "expr.ast" */

  tIdent id_sin, id_cos, id_tan;

# ifdef __cplusplus
#  ifndef yyALLOC
#   define yyALLOC(size1, size2) yyALLOCi (size1, size2)
#  endif
static inline tTree yyALLOCi (unsigned long yysize1, unsigned long yysize2)
{ return Tree_PoolFreePtr >= Tree_PoolStartPtr + yysize1 ?
  (tTree) (Tree_PoolFreePtr -= yysize1) : Tree_Alloc (yysize2); }
static inline tTree yyALLOCk (unsigned long yysize)
{ return yyALLOC (yysize, yysize); }
static inline tTree yyALLOCt (unsigned long yysize)
{ return yyALLOC (yyAlignedSize (yysize), yysize); }
# else
#  define yyALLOCk(size) yyALLOC (size, size)
#  define yyALLOCt(size) yyALLOC (yyAlignedSize (size), size)
#  ifndef yyALLOC
#   define yyALLOC(size1, size2) (Tree_PoolFreePtr -= (long) size1) >= \
     Tree_PoolStartPtr ? (tTree) Tree_PoolFreePtr : Tree_Alloc (size2)
#  endif
# endif
# ifndef yyFREE
# define yyFREE(ptr, size) 
# endif
# ifdef getchar
# undef getchar
# endif
# ifdef putchar
# undef putchar
# endif
# include "yyTree.h"

static void yyExit ARGS ((void)) { rExit (1); }

void (* Tree_Exit) ARGS ((void)) = yyExit;

tTree TreeRoot;
unsigned long Tree_HeapUsed = 0;

yytTree_BlockPtr Tree_BlockList	= (yytTree_BlockPtr) NoTree;
char * Tree_PoolFreePtr = (char *) & Tree_BlockList;
char * Tree_PoolStartPtr = (char *) & Tree_BlockList;
rbool Tree_CheckReportNoTree = rtrue, Tree_CheckReportNodes = rtrue;
int Tree_DrawBoxHeight = 20;
int Tree_DrawBoxWidth  = 60;
int Tree_DrawDepth     = 6;
int Tree_DrawLength    = 256;
char Tree_DrawFileName [256] = "";
# ifdef SUPPORT_TVA
rbool Tree_TreatTVAasChild = rfalse;
# endif

const unsigned short Tree_NodeSize [19] = { 0,
 yyAlignedSize (sizeof (ySTMTS)),
 yyAlignedSize (sizeof (yno_stmt)),
 yyAlignedSize (sizeof (ySTMT)),
 yyAlignedSize (sizeof (yassign_stmt)),
 yyAlignedSize (sizeof (yif_stmt)),
 yyAlignedSize (sizeof (ywhile_stmt)),
 yyAlignedSize (sizeof (yprint_stmt)),
 yyAlignedSize (sizeof (yEXPRS)),
 yyAlignedSize (sizeof (yno_exprs)),
 yyAlignedSize (sizeof (yexprs)),
 yyAlignedSize (sizeof (yEXPR)),
 yyAlignedSize (sizeof (yint_const)),
 yyAlignedSize (sizeof (yfloat_const)),
 yyAlignedSize (sizeof (yname)),
 yyAlignedSize (sizeof (yunary_expr)),
 yyAlignedSize (sizeof (ybinary_expr)),
 yyAlignedSize (sizeof (ycond_expr)),
 yyAlignedSize (sizeof (ycall_expr)),
};
const Tree_tKind Tree_TypeRange [19] = { 0,
 kprint_stmt,
 kno_stmt,
 kprint_stmt,
 kassign_stmt,
 kif_stmt,
 kwhile_stmt,
 kprint_stmt,
 kexprs,
 kno_exprs,
 kexprs,
 kcall_expr,
 kint_const,
 kfloat_const,
 kname,
 kunary_expr,
 kbinary_expr,
 kcond_expr,
 kcall_expr,
};
const char * const Tree_NodeName [19] = {
 "NoTree",
 "STMTS",
 "no_stmt",
 "STMT",
 "assign_stmt",
 "if_stmt",
 "while_stmt",
 "print_stmt",
 "EXPRS",
 "no_exprs",
 "exprs",
 "EXPR",
 "int_const",
 "float_const",
 "name",
 "unary_expr",
 "binary_expr",
 "cond_expr",
 "call_expr",
};

tTree Tree_Alloc
# ifdef HAVE_ARGS
 (unsigned long yySize)
# else
 (yySize) unsigned long yySize;
# endif
{
 register yytTree_BlockPtr yyBlockPtr = Tree_BlockList;
 Tree_BlockList = (yytTree_BlockPtr) Alloc ((unsigned long) sizeof (yytTree_Block));
 if ((tTree) Tree_BlockList == NoTree) {
  ErrorMessageI (xxTreeOutOfMemory, xxFatal, NoPosition, xxString, "Tree");
  Tree_Exit ();
 }
 Tree_BlockList->yySuccessor = yyBlockPtr;
 Tree_PoolStartPtr = (char *) Tree_BlockList;
 Tree_HeapUsed += sizeof (yytTree_Block);
 return (tTree) (Tree_PoolFreePtr = Tree_PoolStartPtr +
  (yyBlockSize - yyAlignedSize (yySize)));
}

tTree MakeTree
# ifdef HAVE_ARGS
 (Tree_tKind yyKind)
# else
 (yyKind) Tree_tKind yyKind;
# endif
{
 register tTree yyt = yyALLOCk (Tree_NodeSize [yyKind]);
 Tree_InitHead (yyt, yyKind)
 return yyt;
}

rbool Tree_IsType
# ifdef HAVE_ARGS
 (register tTree yyt, register Tree_tKind yyKind)
# else
 (yyt, yyKind) register tTree yyt; register Tree_tKind yyKind;
# endif
{
 return yyt != NoTree && yyKind <= yyt->Kind &&
  yyt->Kind <= Tree_TypeRange [yyKind];
}


tTree mSTMTS
# ifdef HAVE_ARGS
(void)
# else
()
# endif
{
 register tTree yyt = yyALLOCt (sizeof (ySTMTS));
 Tree_InitHead (yyt, kSTMTS)
 return yyt;
}

tTree mno_stmt
# ifdef HAVE_ARGS
(void)
# else
()
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yno_stmt));
 Tree_InitHead (yyt, kno_stmt)
 return yyt;
}

tTree mSTMT
# ifdef HAVE_ARGS
(tTree pNext, tPosition pPos)
# else
(pNext, pPos)
tTree pNext;
tPosition pPos;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (ySTMT));
 Tree_InitHead (yyt, kSTMT)
 yyt->STMT.Next = pNext;
 yyt->STMT.Pos = pPos;
 return yyt;
}

tTree massign_stmt
# ifdef HAVE_ARGS
(tTree pNext, tPosition pPos, tTree pLhs, tTree pRhs)
# else
(pNext, pPos, pLhs, pRhs)
tTree pNext;
tPosition pPos;
tTree pLhs;
tTree pRhs;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yassign_stmt));
 Tree_InitHead (yyt, kassign_stmt)
 yyt->assign_stmt.Next = pNext;
 yyt->assign_stmt.Pos = pPos;
 yyt->assign_stmt.Lhs = pLhs;
 yyt->assign_stmt.Rhs = pRhs;
 return yyt;
}

tTree mif_stmt
# ifdef HAVE_ARGS
(tTree pNext, tPosition pPos, tTree pCond, tTree pThen, tTree pElse)
# else
(pNext, pPos, pCond, pThen, pElse)
tTree pNext;
tPosition pPos;
tTree pCond;
tTree pThen;
tTree pElse;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yif_stmt));
 Tree_InitHead (yyt, kif_stmt)
 yyt->if_stmt.Next = pNext;
 yyt->if_stmt.Pos = pPos;
 yyt->if_stmt.Cond = pCond;
 yyt->if_stmt.Then = pThen;
 yyt->if_stmt.Else = pElse;
 return yyt;
}

tTree mwhile_stmt
# ifdef HAVE_ARGS
(tTree pNext, tPosition pPos, tTree pCond, tTree pBody)
# else
(pNext, pPos, pCond, pBody)
tTree pNext;
tPosition pPos;
tTree pCond;
tTree pBody;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (ywhile_stmt));
 Tree_InitHead (yyt, kwhile_stmt)
 yyt->while_stmt.Next = pNext;
 yyt->while_stmt.Pos = pPos;
 yyt->while_stmt.Cond = pCond;
 yyt->while_stmt.Body = pBody;
 return yyt;
}

tTree mprint_stmt
# ifdef HAVE_ARGS
(tTree pNext, tPosition pPos, tTree pArguments)
# else
(pNext, pPos, pArguments)
tTree pNext;
tPosition pPos;
tTree pArguments;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yprint_stmt));
 Tree_InitHead (yyt, kprint_stmt)
 yyt->print_stmt.Next = pNext;
 yyt->print_stmt.Pos = pPos;
 yyt->print_stmt.Arguments = pArguments;
 return yyt;
}

tTree mEXPRS
# ifdef HAVE_ARGS
(void)
# else
()
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yEXPRS));
 Tree_InitHead (yyt, kEXPRS)
 return yyt;
}

tTree mno_exprs
# ifdef HAVE_ARGS
(void)
# else
()
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yno_exprs));
 Tree_InitHead (yyt, kno_exprs)
 return yyt;
}

tTree mexprs
# ifdef HAVE_ARGS
(tTree pNext, tTree pExpr)
# else
(pNext, pExpr)
tTree pNext;
tTree pExpr;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yexprs));
 Tree_InitHead (yyt, kexprs)
 yyt->exprs.Next = pNext;
 yyt->exprs.Expr = pExpr;
 return yyt;
}

tTree mEXPR
# ifdef HAVE_ARGS
(tPosition pPos)
# else
(pPos)
tPosition pPos;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yEXPR));
 Tree_InitHead (yyt, kEXPR)
 yyt->EXPR.Pos = pPos;
 return yyt;
}

tTree mint_const
# ifdef HAVE_ARGS
(tPosition pPos, int pValue)
# else
(pPos, pValue)
tPosition pPos;
int pValue;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yint_const));
 Tree_InitHead (yyt, kint_const)
 yyt->int_const.Pos = pPos;
 yyt->int_const.Value = pValue;
 return yyt;
}

tTree mfloat_const
# ifdef HAVE_ARGS
(tPosition pPos, double pValue)
# else
(pPos, pValue)
tPosition pPos;
double pValue;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yfloat_const));
 Tree_InitHead (yyt, kfloat_const)
 yyt->float_const.Pos = pPos;
 yyt->float_const.Value = pValue;
 return yyt;
}

tTree mname
# ifdef HAVE_ARGS
(tPosition pPos, tIdent pIdent)
# else
(pPos, pIdent)
tPosition pPos;
tIdent pIdent;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yname));
 Tree_InitHead (yyt, kname)
 yyt->name.Pos = pPos;
 yyt->name.Ident = pIdent;
 return yyt;
}

tTree munary_expr
# ifdef HAVE_ARGS
(tPosition pPos, char pOp, tTree pArgument)
# else
(pPos, pOp, pArgument)
tPosition pPos;
char pOp;
tTree pArgument;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (yunary_expr));
 Tree_InitHead (yyt, kunary_expr)
 yyt->unary_expr.Pos = pPos;
 yyt->unary_expr.Op = pOp;
 yyt->unary_expr.Argument = pArgument;
 return yyt;
}

tTree mbinary_expr
# ifdef HAVE_ARGS
(tPosition pPos, char pOp, tTree pLeft, tTree pRight)
# else
(pPos, pOp, pLeft, pRight)
tPosition pPos;
char pOp;
tTree pLeft;
tTree pRight;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (ybinary_expr));
 Tree_InitHead (yyt, kbinary_expr)
 yyt->binary_expr.Pos = pPos;
 yyt->binary_expr.Op = pOp;
 yyt->binary_expr.Left = pLeft;
 yyt->binary_expr.Right = pRight;
 return yyt;
}

tTree mcond_expr
# ifdef HAVE_ARGS
(tPosition pPos, tTree pCond, tTree pThen, tTree pElse)
# else
(pPos, pCond, pThen, pElse)
tPosition pPos;
tTree pCond;
tTree pThen;
tTree pElse;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (ycond_expr));
 Tree_InitHead (yyt, kcond_expr)
 yyt->cond_expr.Pos = pPos;
 yyt->cond_expr.Cond = pCond;
 yyt->cond_expr.Then = pThen;
 yyt->cond_expr.Else = pElse;
 return yyt;
}

tTree mcall_expr
# ifdef HAVE_ARGS
(tPosition pPos, tIdent pName, tTree pArguments)
# else
(pPos, pName, pArguments)
tPosition pPos;
tIdent pName;
tTree pArguments;
# endif
{
 register tTree yyt = yyALLOCt (sizeof (ycall_expr));
 Tree_InitHead (yyt, kcall_expr)
 yyt->call_expr.Pos = pPos;
 yyt->call_expr.Name = pName;
 yyt->call_expr.Arguments = pArguments;
 return yyt;
}

static void yyMark
# ifdef HAVE_ARGS
 (register tTree yyt)
# else
 (yyt) register tTree yyt;
# endif
{
 for (;;) {
  if (yyt == NoTree || ++ yyt->yyHead.yyMark > 1) return;

  switch (yyt->Kind) {
case kSTMT:
yyt = yyt->STMT.Next; break;
case kassign_stmt:
yyMark (yyt->assign_stmt.Lhs);
yyMark (yyt->assign_stmt.Rhs);
yyt = yyt->assign_stmt.Next; break;
case kif_stmt:
yyMark (yyt->if_stmt.Cond);
yyMark (yyt->if_stmt.Then);
yyMark (yyt->if_stmt.Else);
yyt = yyt->if_stmt.Next; break;
case kwhile_stmt:
yyMark (yyt->while_stmt.Cond);
yyMark (yyt->while_stmt.Body);
yyt = yyt->while_stmt.Next; break;
case kprint_stmt:
yyMark (yyt->print_stmt.Arguments);
yyt = yyt->print_stmt.Next; break;
case kexprs:
yyMark (yyt->exprs.Expr);
yyt = yyt->exprs.Next; break;
case kunary_expr:
yyt = yyt->unary_expr.Argument; break;
case kbinary_expr:
yyMark (yyt->binary_expr.Left);
yyt = yyt->binary_expr.Right; break;
case kcond_expr:
yyMark (yyt->cond_expr.Cond);
yyMark (yyt->cond_expr.Then);
yyt = yyt->cond_expr.Else; break;
case kcall_expr:
yyt = yyt->call_expr.Arguments; break;
  default: return;
  }
 }
}

# define yyInitTreeStoreSize 64

# define yyTreeStoreHashSize 256

typedef struct { tTree yyPtr; Tree_tLabel yyNext; } yytTreeStore;
static unsigned long yyTreeStoreSize = yyInitTreeStoreSize;
static yytTreeStore * yyTreeStorePtr;
static Tree_tLabel yyLabelCount;
static short yyRecursionLevel = 0;
static Tree_tLabel yyTreeStoreHash [yyTreeStoreHashSize];

static void yyBeginTreeStore ARGS ((void))
{
 register int yyi;
 if (yyRecursionLevel ++ == 0) {
  MakeArray ((char * *) & yyTreeStorePtr, & yyTreeStoreSize,
   (unsigned long) sizeof (yytTreeStore)); yyLabelCount = 0;
  for (yyi = 0; yyi < yyTreeStoreHashSize; yyi ++)
   yyTreeStoreHash [yyi] = 0;
 }
}

static void yyCloseTreeStore ARGS ((void))
{
 if (-- yyRecursionLevel == 0) {
  ReleaseArray ((char * *) & yyTreeStorePtr, & yyTreeStoreSize,
   (unsigned long) sizeof (yytTreeStore));
 }
}

static Tree_tLabel yyMapToLabel
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 long yyhash = (((ptrdiff_t) yyt) >> 4) & (yyTreeStoreHashSize - 1);
 register Tree_tLabel yyi = yyTreeStoreHash [yyhash];
 for (; yyi; yyi = yyTreeStorePtr [yyi].yyNext)
  if (yyTreeStorePtr [yyi].yyPtr == yyt) return yyi;
 if (++ yyLabelCount == (Tree_tLabel) yyTreeStoreSize)
  ExtendArray ((char * *) & yyTreeStorePtr, & yyTreeStoreSize,
   (unsigned long) sizeof (yytTreeStore));
 yyTreeStorePtr [yyLabelCount].yyPtr = yyt;
 yyTreeStorePtr [yyLabelCount].yyNext = yyTreeStoreHash [yyhash];
 yyTreeStoreHash [yyhash] = yyLabelCount;
 return yyLabelCount;
}

static void yyWriteTree ARGS ((tTree yyt));
static void yyWriteTreeXML ARGS ((tTree yyt));

static void xxWriteNl ARGS ((void)) { putc ('\n', yyf); }

static void yyWriteSelector
# ifdef HAVE_ARGS
 (char * yys)
# else
 (yys) char * yys;
# endif
{
 register int yyi = 16 - strlen (yys);
 fputs (yys, yyf);
 while (yyi -- > 0) putc (' ', yyf);
 fputs (" = ", yyf);
}

static void yyWriteHex
# ifdef HAVE_ARGS
 (unsigned char * yyx, int yysize)
# else
 (yyx, yysize) unsigned char * yyx; int yysize;
# endif
{ register int yyi; for (yyi = 0; yyi < yysize; yyi ++)
   fprintf (yyf, "%02x ", yyx [yyi]); }

static void yyWriteAddr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 if (yyt == NoTree) fputs ("NoTree", yyf);
 else fprintf (yyf, "%p *", (void *) yyt);
 xxWriteNl ();
}

static void yWriteNodeSTMT
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yyWriteSelector ("Next");
 yyWriteAddr (yyt->STMT.Next);
 yyWriteSelector ("Pos");
 writetPosition (yyt->STMT.Pos) xxWriteNl ();
}

static void yWriteNodeassign_stmt
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeSTMT (yyt);
 yyWriteSelector ("Lhs");
 yyWriteAddr (yyt->assign_stmt.Lhs);
 yyWriteSelector ("Rhs");
 yyWriteAddr (yyt->assign_stmt.Rhs);
}

static void yWriteNodeif_stmt
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeSTMT (yyt);
 yyWriteSelector ("Cond");
 yyWriteAddr (yyt->if_stmt.Cond);
 yyWriteSelector ("Then");
 yyWriteAddr (yyt->if_stmt.Then);
 yyWriteSelector ("Else");
 yyWriteAddr (yyt->if_stmt.Else);
}

static void yWriteNodewhile_stmt
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeSTMT (yyt);
 yyWriteSelector ("Cond");
 yyWriteAddr (yyt->while_stmt.Cond);
 yyWriteSelector ("Body");
 yyWriteAddr (yyt->while_stmt.Body);
}

static void yWriteNodeprint_stmt
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeSTMT (yyt);
 yyWriteSelector ("Arguments");
 yyWriteAddr (yyt->print_stmt.Arguments);
}

static void yWriteNodeexprs
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yyWriteSelector ("Next");
 yyWriteAddr (yyt->exprs.Next);
 yyWriteSelector ("Expr");
 yyWriteAddr (yyt->exprs.Expr);
}

static void yWriteNodeEXPR
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yyWriteSelector ("Pos");
 writetPosition (yyt->EXPR.Pos) xxWriteNl ();
}

static void yWriteNodeint_const
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeEXPR (yyt);
 yyWriteSelector ("Value");
 writeint (yyt->int_const.Value) xxWriteNl ();
}

static void yWriteNodefloat_const
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeEXPR (yyt);
 yyWriteSelector ("Value");
 writedouble (yyt->float_const.Value) xxWriteNl ();
}

static void yWriteNodename
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeEXPR (yyt);
 yyWriteSelector ("Ident");
 writetIdent (yyt->name.Ident) xxWriteNl ();
}

static void yWriteNodeunary_expr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeEXPR (yyt);
 yyWriteSelector ("Op");
 writechar (yyt->unary_expr.Op) xxWriteNl ();
 yyWriteSelector ("Argument");
 yyWriteAddr (yyt->unary_expr.Argument);
}

static void yWriteNodebinary_expr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeEXPR (yyt);
 yyWriteSelector ("Op");
 writechar (yyt->binary_expr.Op) xxWriteNl ();
 yyWriteSelector ("Left");
 yyWriteAddr (yyt->binary_expr.Left);
 yyWriteSelector ("Right");
 yyWriteAddr (yyt->binary_expr.Right);
}

static void yWriteNodecond_expr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeEXPR (yyt);
 yyWriteSelector ("Cond");
 yyWriteAddr (yyt->cond_expr.Cond);
 yyWriteSelector ("Then");
 yyWriteAddr (yyt->cond_expr.Then);
 yyWriteSelector ("Else");
 yyWriteAddr (yyt->cond_expr.Else);
}

static void yWriteNodecall_expr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteNodeEXPR (yyt);
 yyWriteSelector ("Name");
 writetIdent (yyt->call_expr.Name) xxWriteNl ();
 yyWriteSelector ("Arguments");
 yyWriteAddr (yyt->call_expr.Arguments);
}

void WriteTreeNode
# ifdef HAVE_ARGS
 (FILE * yyyf, tTree yyt)
# else
 (yyyf, yyt) FILE * yyyf; tTree yyt;
# endif
{
 yyf = yyyf;
 if (yyt == NoTree) { fputs ("NoTree\n", yyf); return; }

 fputs (Tree_NodeName [yyt->Kind], yyf); fputc ('\n', yyf);
 writeNodeHead (yyt)
 switch (yyt->Kind) {
case kSTMT:
 yWriteNodeSTMT (yyt); break;
case kassign_stmt:
 yWriteNodeassign_stmt (yyt); break;
case kif_stmt:
 yWriteNodeif_stmt (yyt); break;
case kwhile_stmt:
 yWriteNodewhile_stmt (yyt); break;
case kprint_stmt:
 yWriteNodeprint_stmt (yyt); break;
case kexprs:
 yWriteNodeexprs (yyt); break;
case kEXPR:
 yWriteNodeEXPR (yyt); break;
case kint_const:
 yWriteNodeint_const (yyt); break;
case kfloat_const:
 yWriteNodefloat_const (yyt); break;
case kname:
 yWriteNodename (yyt); break;
case kunary_expr:
 yWriteNodeunary_expr (yyt); break;
case kbinary_expr:
 yWriteNodebinary_expr (yyt); break;
case kcond_expr:
 yWriteNodecond_expr (yyt); break;
case kcall_expr:
 yWriteNodecall_expr (yyt); break;
 default: ;
 }
}

static short yyIndentLevel;

void WriteTree
# ifdef HAVE_ARGS
 (FILE * yyyf, tTree yyt)
# else
 (yyyf, yyt) FILE * yyyf; tTree yyt;
# endif
{
 short yySaveLevel = yyIndentLevel;
 yyf = yyyf;
 yyMark (yyt);
 yyIndentLevel = 0;
 yyBeginTreeStore ();
 yyWriteTree (yyt);
 yyCloseTreeStore ();
 yyIndentLevel = yySaveLevel;
 if (ferror (yyyf)) {
  ErrorMessageI (xxTreeIOError, xxFatal, NoPosition, xxString, "Tree.WriteTree");
  Tree_Exit ();
 }
}

static void yyIndentSelector
# ifdef HAVE_ARGS
 (char * yys)
# else
 (yys) char * yys;
# endif
{
 register int yyi;
 for (yyi = 1; yyi <= yyIndentLevel; yyi ++) putc (' ', yyf);
 yyWriteSelector (yys);
}

static void yyIndentSelectorTree
# ifdef HAVE_ARGS
 (char * yys, tTree yyt)
# else
 (yys, yyt) char * yys; tTree yyt;
# endif
{ writeSELECTOR (yys); yyWriteTree (yyt); }

static void yWriteSTMT
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
{ writeSELECTOR ("Pos");
writetPosition (yyt->STMT.Pos) xxWriteNl (); }
}

static void yWriteassign_stmt
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteSTMT (yyt);
 yyIndentSelectorTree ("Lhs", yyt->assign_stmt.Lhs);
 yyIndentSelectorTree ("Rhs", yyt->assign_stmt.Rhs);
}

static void yWriteif_stmt
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteSTMT (yyt);
 yyIndentSelectorTree ("Cond", yyt->if_stmt.Cond);
 yyIndentSelectorTree ("Then", yyt->if_stmt.Then);
 yyIndentSelectorTree ("Else", yyt->if_stmt.Else);
}

static void yWritewhile_stmt
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteSTMT (yyt);
 yyIndentSelectorTree ("Cond", yyt->while_stmt.Cond);
 yyIndentSelectorTree ("Body", yyt->while_stmt.Body);
}

static void yWriteprint_stmt
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteSTMT (yyt);
 yyIndentSelectorTree ("Arguments", yyt->print_stmt.Arguments);
}

static void yWriteexprs
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yyIndentSelectorTree ("Expr", yyt->exprs.Expr);
}

static void yWriteEXPR
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
{ writeSELECTOR ("Pos");
writetPosition (yyt->EXPR.Pos) xxWriteNl (); }
}

static void yWriteint_const
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteEXPR (yyt);
{ writeSELECTOR ("Value");
writeint (yyt->int_const.Value) xxWriteNl (); }
}

static void yWritefloat_const
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteEXPR (yyt);
{ writeSELECTOR ("Value");
writedouble (yyt->float_const.Value) xxWriteNl (); }
}

static void yWritename
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteEXPR (yyt);
{ writeSELECTOR ("Ident");
writetIdent (yyt->name.Ident) xxWriteNl (); }
}

static void yWriteunary_expr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteEXPR (yyt);
{ writeSELECTOR ("Op");
writechar (yyt->unary_expr.Op) xxWriteNl (); }
}

static void yWritebinary_expr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteEXPR (yyt);
{ writeSELECTOR ("Op");
writechar (yyt->binary_expr.Op) xxWriteNl (); }
 yyIndentSelectorTree ("Left", yyt->binary_expr.Left);
}

static void yWritecond_expr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteEXPR (yyt);
 yyIndentSelectorTree ("Cond", yyt->cond_expr.Cond);
 yyIndentSelectorTree ("Then", yyt->cond_expr.Then);
}

static void yWritecall_expr
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 yWriteEXPR (yyt);
{ writeSELECTOR ("Name");
writetIdent (yyt->call_expr.Name) xxWriteNl (); }
}

static void yyWriteTree
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{ unsigned short yyLevel = yyIndentLevel;
 for (;;) {
  if (yyt == NoTree) { fputs (" NoTree\n", yyf); goto yyExit;
  } else if (yyt->yyHead.yyMark == 0) {
   fprintf (yyf, "^%d\n", yyMapToLabel (yyt)); goto yyExit;
  } else if (yyt->yyHead.yyMark > 1) {
   register int yyi;
   fprintf (yyf, "\n%06d:", yyMapToLabel (yyt));
   for (yyi = 8; yyi <= yyIndentLevel; yyi ++) putc (' ', yyf);
  } else putc (' ', yyf);
  yyt->yyHead.yyMark = 0;
  yyIndentLevel += 2;

  fputs (Tree_NodeName [yyt->Kind], yyf); fputc ('\n', yyf);
  writeNodeHead (yyt)
  switch (yyt->Kind) {
case kSTMT: yWriteSTMT (yyt);
writeSELECTOR ("Next");
yyt = yyt->STMT.Next; break;
case kassign_stmt: yWriteassign_stmt (yyt);
writeSELECTOR ("Next");
yyt = yyt->assign_stmt.Next; break;
case kif_stmt: yWriteif_stmt (yyt);
writeSELECTOR ("Next");
yyt = yyt->if_stmt.Next; break;
case kwhile_stmt: yWritewhile_stmt (yyt);
writeSELECTOR ("Next");
yyt = yyt->while_stmt.Next; break;
case kprint_stmt: yWriteprint_stmt (yyt);
writeSELECTOR ("Next");
yyt = yyt->print_stmt.Next; break;
case kexprs: yWriteexprs (yyt);
writeSELECTOR ("Next");
yyt = yyt->exprs.Next; break;
case kEXPR: yWriteEXPR (yyt); goto yyExit;
case kint_const: yWriteint_const (yyt); goto yyExit;
case kfloat_const: yWritefloat_const (yyt); goto yyExit;
case kname: yWritename (yyt); goto yyExit;
case kunary_expr: yWriteunary_expr (yyt);
writeSELECTOR ("Argument");
yyt = yyt->unary_expr.Argument; break;
case kbinary_expr: yWritebinary_expr (yyt);
writeSELECTOR ("Right");
yyt = yyt->binary_expr.Right; break;
case kcond_expr: yWritecond_expr (yyt);
writeSELECTOR ("Else");
yyt = yyt->cond_expr.Else; break;
case kcall_expr: yWritecall_expr (yyt);
writeSELECTOR ("Arguments");
yyt = yyt->call_expr.Arguments; break;
  default: goto yyExit;
  }
 }
yyExit:
 yyIndentLevel = yyLevel;
}

static Tree_tProcTree yyProc;

static void yyTraverseTreeTD
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 for (;;) {
  if (yyt == NoTree || yyt->yyHead.yyMark == 0) return;
  yyProc (yyt);
  yyt->yyHead.yyMark = 0;

  switch (yyt->Kind) {
case kSTMT:
yyt = yyt->STMT.Next; break;
case kassign_stmt:
yyTraverseTreeTD (yyt->assign_stmt.Lhs);
yyTraverseTreeTD (yyt->assign_stmt.Rhs);
yyt = yyt->assign_stmt.Next; break;
case kif_stmt:
yyTraverseTreeTD (yyt->if_stmt.Cond);
yyTraverseTreeTD (yyt->if_stmt.Then);
yyTraverseTreeTD (yyt->if_stmt.Else);
yyt = yyt->if_stmt.Next; break;
case kwhile_stmt:
yyTraverseTreeTD (yyt->while_stmt.Cond);
yyTraverseTreeTD (yyt->while_stmt.Body);
yyt = yyt->while_stmt.Next; break;
case kprint_stmt:
yyTraverseTreeTD (yyt->print_stmt.Arguments);
yyt = yyt->print_stmt.Next; break;
case kexprs:
yyTraverseTreeTD (yyt->exprs.Expr);
yyt = yyt->exprs.Next; break;
case kunary_expr:
yyt = yyt->unary_expr.Argument; break;
case kbinary_expr:
yyTraverseTreeTD (yyt->binary_expr.Left);
yyt = yyt->binary_expr.Right; break;
case kcond_expr:
yyTraverseTreeTD (yyt->cond_expr.Cond);
yyTraverseTreeTD (yyt->cond_expr.Then);
yyt = yyt->cond_expr.Else; break;
case kcall_expr:
yyt = yyt->call_expr.Arguments; break;
  default: return;
  }
 }
}

void TraverseTreeTD
# ifdef HAVE_ARGS
 (tTree yyt, Tree_tProcTree yyyProc)
# else
 (yyt, yyyProc) tTree yyt; Tree_tProcTree yyyProc;
# endif
{
# ifdef SUPPORT_TVA
 rbool yyPrevTreatTVAasChild = Tree_TreatTVAasChild;
 Tree_TreatTVAasChild = rfalse;
 yyMark (yyt);
 Tree_TreatTVAasChild = yyPrevTreatTVAasChild;
# else
 yyMark (yyt);
# endif
 yyProc = yyyProc;
 yyTraverseTreeTD (yyt);
}

tTree ReverseTree
# ifdef HAVE_ARGS
 (tTree yyOld)
# else
 (yyOld) tTree yyOld;
# endif
{
 register tTree yyNew, yyNext, yyTail;
 yyNew = yyOld;
 yyTail = yyOld;
 for (;;) {
  switch (yyOld->Kind) {
case kSTMT: yyNext = yyOld->STMT.Next;
 yyOld->STMT.Next = yyNew; break;
case kassign_stmt: yyNext = yyOld->assign_stmt.Next;
 yyOld->assign_stmt.Next = yyNew; break;
case kif_stmt: yyNext = yyOld->if_stmt.Next;
 yyOld->if_stmt.Next = yyNew; break;
case kwhile_stmt: yyNext = yyOld->while_stmt.Next;
 yyOld->while_stmt.Next = yyNew; break;
case kprint_stmt: yyNext = yyOld->print_stmt.Next;
 yyOld->print_stmt.Next = yyNew; break;
case kexprs: yyNext = yyOld->exprs.Next;
 yyOld->exprs.Next = yyNew; break;
  default: goto yyExit;
  }
  yyNew = yyOld;
  yyOld = yyNext;
 }
yyExit:
 switch (yyTail->Kind) {
case kSTMT: yyTail->STMT.Next = yyOld; break;
case kassign_stmt: yyTail->assign_stmt.Next = yyOld; break;
case kif_stmt: yyTail->if_stmt.Next = yyOld; break;
case kwhile_stmt: yyTail->while_stmt.Next = yyOld; break;
case kprint_stmt: yyTail->print_stmt.Next = yyOld; break;
case kexprs: yyTail->exprs.Next = yyOld; break;
 default: ;
 }
 return yyNew;
}

void ForallTree
# ifdef HAVE_ARGS
 (tTree yyt, Tree_tProcTree yyProc)
# else
 (yyt, yyProc) tTree yyt; Tree_tProcTree yyProc;
# endif
{
 for (;;) {
  tTree yyyt;
  if ((yyyt = yyt) == NoTree) return;
  switch (yyt->Kind) {
case kSTMT: yyt = yyt->STMT.Next; break;
case kassign_stmt: yyt = yyt->assign_stmt.Next; break;
case kif_stmt: yyt = yyt->if_stmt.Next; break;
case kwhile_stmt: yyt = yyt->while_stmt.Next; break;
case kprint_stmt: yyt = yyt->print_stmt.Next; break;
case kexprs: yyt = yyt->exprs.Next; break;
  default: return;
  }
  yyProc (yyyt);
 }
}

static rbool yyResult;

static void yyCheckTree ARGS ((tTree yyt));

rbool CheckTree
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
# ifdef SUPPORT_TVA
 rbool yyPrevTreatTVAasChild = Tree_TreatTVAasChild;
 Tree_TreatTVAasChild = rfalse;
 yyMark (yyt);
 Tree_TreatTVAasChild = yyPrevTreatTVAasChild;
# else
 yyMark (yyt);
# endif
 yyResult = rtrue;
 yyCheckTree (yyt);
 return yyResult;
}

static void yyCheckChild2
# ifdef HAVE_ARGS
 (tTree yyParent, tTree yyChild, Tree_tKind yyType, char * yySelector)
# else
 (yyParent, yyChild, yyType, yySelector)
 tTree yyParent, yyChild;
 Tree_tKind yyType;
 char * yySelector;
# endif
{
 if (yyChild == NoTree) {
  if (Tree_CheckReportNoTree) goto yyReport;
 } else if (yyType > yyChild->Kind || yyChild->Kind > Tree_TypeRange [yyType]) {
yyReport: yyResult = rfalse;
  fprintf (stderr, "%s\n", CodeToText (xxCheckTreeError));
  fprintf (stderr, "   %s %p\n", CodeToText (xxCheckTreeAddrOfParent), (void *) yyParent);
  fprintf (stderr, "   %s %s\n", CodeToText (xxCheckTreeTypeOfParent), Tree_NodeName [yyParent->Kind]);
  fprintf (stderr, "   %s %s\n", CodeToText (xxCheckTreeNameOfChild), yySelector);
  if (yyChild == NoTree)
   fprintf (stderr, "   %s NoTree\n", CodeToText (xxCheckTreeValueOfChild));
  else {
   fprintf (stderr, "   %s %p\n", CodeToText (xxCheckTreeAddrOfChild), (void *) yyChild);
   fprintf (stderr, "   %s %s\n", CodeToText (xxCheckTreeTypeOfChild), Tree_NodeName [yyChild->Kind]);
  }
  fprintf (stderr, "   %s %s\n", CodeToText (xxCheckTreeExpectedType), Tree_NodeName [yyType]);
  if (Tree_CheckReportNodes) {
   fprintf (stderr, "   %s\n", CodeToText (xxCheckTreeParentNode));
   WriteTreeNode (stderr, yyParent);
   fprintf (stderr, "   %s\n", CodeToText (xxCheckTreeChildNode));
   WriteTreeNode (stderr, yyChild);
  }
  fputc ('\n', stderr);
 }
}

static void yyCheckChild
# ifdef HAVE_ARGS
 (tTree yyParent, tTree yyChild, Tree_tKind yyType, char * yySelector)
# else
 (yyParent, yyChild, yyType, yySelector)
 tTree yyParent, yyChild;
 Tree_tKind yyType;
 char * yySelector;
# endif
{
 yyCheckChild2 (yyParent, yyChild, yyType, yySelector);
 yyCheckTree (yyChild);
}

static void yyCheckTree
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 for (;;) {
  if (yyt == NoTree) { if (Tree_CheckReportNoTree) yyResult = rfalse; return; }
  if (yyt->yyHead.yyMark == 0) return;
  yyt->yyHead.yyMark = 0;

  switch (yyt->Kind) {
case kSTMT:
yyCheckChild2 (yyt, yyt->STMT.Next,
kSTMTS, "Next");
yyt = yyt->STMT.Next; break;
case kassign_stmt:
yyCheckChild (yyt, yyt->assign_stmt.Lhs,
kEXPR, "Lhs");
yyCheckChild (yyt, yyt->assign_stmt.Rhs,
kEXPR, "Rhs");
yyCheckChild2 (yyt, yyt->assign_stmt.Next,
kSTMTS, "Next");
yyt = yyt->assign_stmt.Next; break;
case kif_stmt:
yyCheckChild (yyt, yyt->if_stmt.Cond,
kEXPR, "Cond");
yyCheckChild (yyt, yyt->if_stmt.Then,
kSTMTS, "Then");
yyCheckChild (yyt, yyt->if_stmt.Else,
kSTMTS, "Else");
yyCheckChild2 (yyt, yyt->if_stmt.Next,
kSTMTS, "Next");
yyt = yyt->if_stmt.Next; break;
case kwhile_stmt:
yyCheckChild (yyt, yyt->while_stmt.Cond,
kEXPR, "Cond");
yyCheckChild (yyt, yyt->while_stmt.Body,
kSTMTS, "Body");
yyCheckChild2 (yyt, yyt->while_stmt.Next,
kSTMTS, "Next");
yyt = yyt->while_stmt.Next; break;
case kprint_stmt:
yyCheckChild (yyt, yyt->print_stmt.Arguments,
kEXPRS, "Arguments");
yyCheckChild2 (yyt, yyt->print_stmt.Next,
kSTMTS, "Next");
yyt = yyt->print_stmt.Next; break;
case kexprs:
yyCheckChild (yyt, yyt->exprs.Expr,
kEXPR, "Expr");
yyCheckChild2 (yyt, yyt->exprs.Next,
kEXPRS, "Next");
yyt = yyt->exprs.Next; break;
case kunary_expr:
yyCheckChild2 (yyt, yyt->unary_expr.Argument,
kEXPR, "Argument");
yyt = yyt->unary_expr.Argument; break;
case kbinary_expr:
yyCheckChild (yyt, yyt->binary_expr.Left,
kEXPR, "Left");
yyCheckChild2 (yyt, yyt->binary_expr.Right,
kEXPR, "Right");
yyt = yyt->binary_expr.Right; break;
case kcond_expr:
yyCheckChild (yyt, yyt->cond_expr.Cond,
kEXPR, "Cond");
yyCheckChild (yyt, yyt->cond_expr.Then,
kEXPR, "Then");
yyCheckChild2 (yyt, yyt->cond_expr.Else,
kEXPR, "Else");
yyt = yyt->cond_expr.Else; break;
case kcall_expr:
yyCheckChild2 (yyt, yyt->call_expr.Arguments,
kEXPRS, "Arguments");
yyt = yyt->call_expr.Arguments; break;
  default: return;
  }
 }
}

# ifndef EXTERN_C_BEGIN
# define EXTERN_C_BEGIN
# define EXTERN_C_END
# endif

EXTERN_C_BEGIN
# include "Position.h"
EXTERN_C_END

static unsigned long yyLine, yyCurLine;
static tTree yyTheTree, yyNode;
static tIdent yyFile;

static void yySearch4
# ifdef HAVE_ARGS
 (tTree yyt, tPosition yyp)
# else
 (yyt, yyp) tTree yyt; tPosition yyp;
# endif
{
 if ((yyFile == NoIdent || yyFile == yyp.FileName) &&
   yyLine <= yyp.Line && yyp.Line < yyCurLine)
  { yyNode = yyt; yyCurLine = yyp.Line; }
}

static void yySearch2
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 switch (yyt->Kind) {
case kSTMT:
yySearch4 (yyt, yyt->STMT.Pos);
break;
case kassign_stmt:
yySearch4 (yyt, yyt->assign_stmt.Pos);
break;
case kif_stmt:
yySearch4 (yyt, yyt->if_stmt.Pos);
break;
case kwhile_stmt:
yySearch4 (yyt, yyt->while_stmt.Pos);
break;
case kprint_stmt:
yySearch4 (yyt, yyt->print_stmt.Pos);
break;
case kEXPR:
yySearch4 (yyt, yyt->EXPR.Pos);
break;
case kint_const:
yySearch4 (yyt, yyt->int_const.Pos);
break;
case kfloat_const:
yySearch4 (yyt, yyt->float_const.Pos);
break;
case kname:
yySearch4 (yyt, yyt->name.Pos);
break;
case kunary_expr:
yySearch4 (yyt, yyt->unary_expr.Pos);
break;
case kbinary_expr:
yySearch4 (yyt, yyt->binary_expr.Pos);
break;
case kcond_expr:
yySearch4 (yyt, yyt->cond_expr.Pos);
break;
case kcall_expr:
yySearch4 (yyt, yyt->call_expr.Pos);
break;
 }
}

# include <tcl.h>
# include <tk.h>

# if (TCL_MAJOR_VERSION >= 8) && (TCL_MINOR_VERSION >= 4)
#  define AST_CONST const
# else
#  define AST_CONST
# endif

# define yyMaxCoord		65535
# define yyIsBusy		65535
# define yyTruncByDepth	65535
# define yyTruncByLength	65534
static Tcl_Interp * yygInterp;

static int yySearch
# ifdef HAVE_ARGS
 (ClientData yyclass, Tcl_Interp * yyinterp, int yyargc, AST_CONST char * yyargv [])
# else
 (yyclass, yyinterp, yyargc, yyargv)
 ClientData	yyclass;
 Tcl_Interp *	yyinterp;
 int		yyargc;
 char *	yyargv [];
# endif
{
 tTree yyTheTree = (tTree) atol (yyargv [1]);
 char yyArray [32];
 yyLine = atol (yyargv [2]);
 yyFile = yyargv [3][0] == '\0' ? NoIdent : MakeIdent1 (yyargv [3]);
 yyCurLine = 1000000;
 yyNode = yyTheTree;
 TraverseTreeTD (yyTheTree, yySearch2);
 sprintf (yyArray, "%lu", (unsigned long) yyNode);
 Tcl_SetResult (yyinterp, yyArray, TCL_VOLATILE);
 return TCL_OK;
}

static rbool yyphase1;
static int yymaxx, yymaxy;

static int yySetY
# ifdef HAVE_ARGS
 (tTree yyp, tTree yyt, int yyy, int yyk, int yyl)
# else
 (yyp, yyt, yyy, yyk, yyl) tTree yyp, yyt; int yyy, yyk, yyl;
# endif
{
 int yy, yymax = ++ yyy;
 if (yyphase1) {
  if (yyt == NoTree || (yyt->yyHead.yyMark == 0 &&
   (yyt->yyHead.yyx == yyIsBusy || yyt->yyHead.yyy >= (unsigned short) yyy ||
    yyp->yyHead.yyy >= yyTruncByLength)))
   return yymax;
  yyt->yyHead.yyparent = yyp;
  yyt->yyHead.yyx = yyIsBusy;
 } else {
  if (yyt == NoTree ||
   yyt->yyHead.yyMark == 0 || yyt->yyHead.yyparent != yyp) return yymax;
 }
 yyt->yyHead.yyMark = 0;
 if (++ yyl > Tree_DrawLength) yyk = Tree_DrawDepth;
 yyk ++;
 yyt->yyHead.yyy = (unsigned short) (yyk <= Tree_DrawDepth ? 0 : yyTruncByDepth);
 switch (yyt->Kind) {
case kSTMT:
yymax = yySetY (yyt, yyt->STMT.Next, yymax, yyk - 1, yyl);
break;
case kassign_stmt:
yy = yySetY (yyt, yyt->assign_stmt.Lhs, yyy, yyk, 0);
yymax = Max (yymax, yy);
yy = yySetY (yyt, yyt->assign_stmt.Rhs, yyy, yyk, 0);
yymax = Max (yymax, yy);
yymax = yySetY (yyt, yyt->assign_stmt.Next, yymax - 1, yyk - 1, yyl);
break;
case kif_stmt:
yy = yySetY (yyt, yyt->if_stmt.Cond, yyy, yyk, 0);
yymax = Max (yymax, yy);
yy = yySetY (yyt, yyt->if_stmt.Then, yyy, yyk, 0);
yymax = Max (yymax, yy);
yy = yySetY (yyt, yyt->if_stmt.Else, yyy, yyk, 0);
yymax = Max (yymax, yy);
yymax = yySetY (yyt, yyt->if_stmt.Next, yymax - 1, yyk - 1, yyl);
break;
case kwhile_stmt:
yy = yySetY (yyt, yyt->while_stmt.Cond, yyy, yyk, 0);
yymax = Max (yymax, yy);
yy = yySetY (yyt, yyt->while_stmt.Body, yyy, yyk, 0);
yymax = Max (yymax, yy);
yymax = yySetY (yyt, yyt->while_stmt.Next, yymax - 1, yyk - 1, yyl);
break;
case kprint_stmt:
yy = yySetY (yyt, yyt->print_stmt.Arguments, yyy, yyk, 0);
yymax = Max (yymax, yy);
yymax = yySetY (yyt, yyt->print_stmt.Next, yymax - 1, yyk - 1, yyl);
break;
case kexprs:
yy = yySetY (yyt, yyt->exprs.Expr, yyy, yyk, 0);
yymax = Max (yymax, yy);
yymax = yySetY (yyt, yyt->exprs.Next, yymax - 1, yyk - 1, yyl);
break;
case kunary_expr:
yy = yySetY (yyt, yyt->unary_expr.Argument, yyy, yyk, 0);
yymax = Max (yymax, yy);
break;
case kbinary_expr:
yy = yySetY (yyt, yyt->binary_expr.Left, yyy, yyk, 0);
yymax = Max (yymax, yy);
yy = yySetY (yyt, yyt->binary_expr.Right, yyy, yyk, 0);
yymax = Max (yymax, yy);
break;
case kcond_expr:
yy = yySetY (yyt, yyt->cond_expr.Cond, yyy, yyk, 0);
yymax = Max (yymax, yy);
yy = yySetY (yyt, yyt->cond_expr.Then, yyy, yyk, 0);
yymax = Max (yymax, yy);
yy = yySetY (yyt, yyt->cond_expr.Else, yyy, yyk, 0);
yymax = Max (yymax, yy);
break;
case kcall_expr:
yy = yySetY (yyt, yyt->call_expr.Arguments, yyy, yyk, 0);
yymax = Max (yymax, yy);
break;
 }
 yyt->yyHead.yyx = 0;
 if (yyl > Tree_DrawLength) {
  yyt->yyHead.yyy = yyTruncByLength;
  return yyy;
 } else if (yyk > Tree_DrawDepth) {
  yyt->yyHead.yyy = yyTruncByDepth;
  return yyy;
 } else {
  yyt->yyHead.yyy = (unsigned short) yyy;
  yymaxy = Max (yymaxy, yyy);
  return yymax;
 }
}

typedef struct { unsigned short yyfirst, yylast; } yytFirstLast;

static int yySetX
# ifdef HAVE_ARGS
 (tTree yyp, tTree yyt, int yyx, yytFirstLast * yyout)
# else
 (yyp, yyt, yyx, yyout) tTree yyp, yyt; int yyx; yytFirstLast * yyout;
# endif
{
 int yyxin = yyx, yyw;
 yytFirstLast yyFirstLast;
 if (yyt == NoTree || yyt->yyHead.yyMark == 0 ||
  yyt->yyHead.yyparent != yyp) return yyx;
 yyt->yyHead.yyMark = 0;
 yyFirstLast.yyfirst = yyMaxCoord;
 yyFirstLast.yylast = 0;
 switch (yyt->Kind) {
case kSTMT:
yyw = yySetX (yyt, yyt->STMT.Next, yyx ++, & yyFirstLast);
goto yyList;
case kassign_stmt:
yyw = yySetX (yyt, yyt->assign_stmt.Next, yyx ++, & yyFirstLast);
yyx = yySetX (yyt, yyt->assign_stmt.Lhs, yyx, & yyFirstLast);
yyx = yySetX (yyt, yyt->assign_stmt.Rhs, yyx, & yyFirstLast);
goto yyList;
case kif_stmt:
yyw = yySetX (yyt, yyt->if_stmt.Next, yyx ++, & yyFirstLast);
yyx = yySetX (yyt, yyt->if_stmt.Cond, yyx, & yyFirstLast);
yyx = yySetX (yyt, yyt->if_stmt.Then, yyx, & yyFirstLast);
yyx = yySetX (yyt, yyt->if_stmt.Else, yyx, & yyFirstLast);
goto yyList;
case kwhile_stmt:
yyw = yySetX (yyt, yyt->while_stmt.Next, yyx ++, & yyFirstLast);
yyx = yySetX (yyt, yyt->while_stmt.Cond, yyx, & yyFirstLast);
yyx = yySetX (yyt, yyt->while_stmt.Body, yyx, & yyFirstLast);
goto yyList;
case kprint_stmt:
yyw = yySetX (yyt, yyt->print_stmt.Next, yyx ++, & yyFirstLast);
yyx = yySetX (yyt, yyt->print_stmt.Arguments, yyx, & yyFirstLast);
goto yyList;
case kexprs:
yyw = yySetX (yyt, yyt->exprs.Next, yyx ++, & yyFirstLast);
yyx = yySetX (yyt, yyt->exprs.Expr, yyx, & yyFirstLast);
goto yyList;
case kunary_expr:
yyx = yySetX (yyt, yyt->unary_expr.Argument, yyx, & yyFirstLast);
break;
case kbinary_expr:
yyx = yySetX (yyt, yyt->binary_expr.Left, yyx, & yyFirstLast);
yyx = yySetX (yyt, yyt->binary_expr.Right, yyx, & yyFirstLast);
break;
case kcond_expr:
yyx = yySetX (yyt, yyt->cond_expr.Cond, yyx, & yyFirstLast);
yyx = yySetX (yyt, yyt->cond_expr.Then, yyx, & yyFirstLast);
yyx = yySetX (yyt, yyt->cond_expr.Else, yyx, & yyFirstLast);
break;
case kcall_expr:
yyx = yySetX (yyt, yyt->call_expr.Arguments, yyx, & yyFirstLast);
break;
 }
 if (yyt->yyHead.yyy >= yyTruncByLength) {
  return yyxin;
 } else {
  yyt->yyHead.yyx = (unsigned short) (yyFirstLast.yyfirst == yyMaxCoord ? yyx :
   (yyFirstLast.yyfirst + yyFirstLast.yylast) / 2);
  yymaxx = Max ((unsigned short) yymaxx, yyt->yyHead.yyx);
  if (yyt->yyHead.yyparent == yyp) {
   if (yyout->yyfirst == yyMaxCoord) yyout->yyfirst = yyt->yyHead.yyx;
   yyout->yylast = yyt->yyHead.yyx;
  }
  yyxin ++;
  return Max (yyx, yyxin);
 }
yyList:
 if (yyt->yyHead.yyy >= yyTruncByLength) {
  return yyxin;
 } else {
  yyt->yyHead.yyx = (unsigned short) yyxin;
  yymaxx = Max (yymaxx, yyxin);
  if (yyt->yyHead.yyparent == yyp) {
   if (yyout->yyfirst == yyMaxCoord) yyout->yyfirst = yyt->yyHead.yyx;
   yyout->yylast = yyt->yyHead.yyx;
  }
  return Max (yyx, yyw);
 }
}

static void yyDrawEdge
# ifdef HAVE_ARGS
 (tTree yyfrom, tTree yyto)
# else
 (yyfrom, yyto) tTree yyfrom, yyto;
# endif
{
 char yyCoord [32];
 if (yyto == NoTree) return;
 if (yyto->yyHead.yyy < yyTruncByLength)
  sprintf (yyCoord, "%d %d %d %d", yyfrom->yyHead.yyx, yyfrom->yyHead.yyy,
   yyto->yyHead.yyx, yyto->yyHead.yyy);
 else if (yyto->yyHead.yyy == yyTruncByDepth)
  sprintf (yyCoord, "%d %d %d %d 1", yyfrom->yyHead.yyx, yyfrom->yyHead.yyy,
   yyfrom->yyHead.yyx + 1, yyfrom->yyHead.yyy);
 else
  sprintf (yyCoord, "%d %d %d %d 1", yyfrom->yyHead.yyx, yyfrom->yyHead.yyy,
   yyfrom->yyHead.yyx, yyfrom->yyHead.yyy + 1);
 Tcl_VarEval (yygInterp, "draw_edge ", yyCoord, NULL);
}

static void yyDrawNode
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 char yyCoord [32];
 if (yyt->yyHead.yyy >= yyTruncByLength) return;
 sprintf (yyCoord, "%d %d %lu ", yyt->yyHead.yyx, yyt->yyHead.yyy, (unsigned long) yyt);
 Tcl_VarEval (yygInterp, "draw_node ", yyCoord,
  Tree_NodeName [yyt->Kind], NULL);
 switch (yyt->Kind) {
case kSTMT:
yyDrawEdge (yyt, yyt->STMT.Next);
break;
case kassign_stmt:
yyDrawEdge (yyt, yyt->assign_stmt.Next);
yyDrawEdge (yyt, yyt->assign_stmt.Lhs);
yyDrawEdge (yyt, yyt->assign_stmt.Rhs);
break;
case kif_stmt:
yyDrawEdge (yyt, yyt->if_stmt.Next);
yyDrawEdge (yyt, yyt->if_stmt.Cond);
yyDrawEdge (yyt, yyt->if_stmt.Then);
yyDrawEdge (yyt, yyt->if_stmt.Else);
break;
case kwhile_stmt:
yyDrawEdge (yyt, yyt->while_stmt.Next);
yyDrawEdge (yyt, yyt->while_stmt.Cond);
yyDrawEdge (yyt, yyt->while_stmt.Body);
break;
case kprint_stmt:
yyDrawEdge (yyt, yyt->print_stmt.Next);
yyDrawEdge (yyt, yyt->print_stmt.Arguments);
break;
case kexprs:
yyDrawEdge (yyt, yyt->exprs.Next);
yyDrawEdge (yyt, yyt->exprs.Expr);
break;
case kunary_expr:
yyDrawEdge (yyt, yyt->unary_expr.Argument);
break;
case kbinary_expr:
yyDrawEdge (yyt, yyt->binary_expr.Left);
yyDrawEdge (yyt, yyt->binary_expr.Right);
break;
case kcond_expr:
yyDrawEdge (yyt, yyt->cond_expr.Cond);
yyDrawEdge (yyt, yyt->cond_expr.Then);
yyDrawEdge (yyt, yyt->cond_expr.Else);
break;
case kcall_expr:
yyDrawEdge (yyt, yyt->call_expr.Arguments);
break;
 }
}

static int yyPutAttr
# ifdef HAVE_ARGS
 (ClientData yyclass, Tcl_Interp * yyinterp, int yyargc, AST_CONST char * yyargv [])
# else
 (yyclass, yyinterp, yyargc, yyargv)
 ClientData	yyclass;
 Tcl_Interp *	yyinterp;
 int		yyargc;
 char *	yyargv [];
# endif
{
 FILE * yyf = fopen ("yyNode", "w");
 if (yyf) {
  WriteTreeNode (yyf, (tTree) atol (yyargv [1]));
  fclose (yyf);
 } else {
  Tcl_SetResult (yyinterp, CodeToText (xxDrawTreeyyNode), TCL_STATIC);
 }
 return TCL_OK;
}

static void yyDrawTree (tTree yyt, ClientData yyclass);

static int yyDrawSubTree
# ifdef HAVE_ARGS
 (ClientData yyclass, Tcl_Interp * yyinterp, int yyargc, AST_CONST char * yyargv [])
# else
 (yyclass, yyinterp, yyargc, yyargv)
 ClientData	yyclass;
 Tcl_Interp *	yyinterp;
 int		yyargc;
 char *	yyargv [];
# endif
{
 DrawTree ((tTree) atol (yyargv [1]));
 return TCL_OK;
}

# ifndef DrawAttr
# define DrawAttr(x, y)
# endif

static int yyCallAttr
# ifdef HAVE_ARGS
 (ClientData yyclass, Tcl_Interp * yyinterp, int yyargc, AST_CONST char * yyargv [])
# else
 (yyclass, yyinterp, yyargc, yyargv)
 ClientData	yyclass;
 Tcl_Interp *	yyinterp;
 int		yyargc;
 char *	yyargv [];
# endif
{
 DrawAttr ((tTree) atol (yyargv [1]), (char *) yyargv [2]);
 return TCL_OK;
}

static int yySetParam
# ifdef HAVE_ARGS
 (ClientData yyclass, Tcl_Interp * yyinterp, int yyargc, AST_CONST char * yyargv [])
# else
 (yyclass, yyinterp, yyargc, yyargv)
 ClientData	yyclass;
 Tcl_Interp *	yyinterp;
 int		yyargc;
 char *	yyargv [];
# endif
{
 Tree_DrawDepth     = atoi (yyargv [1]);
 Tree_DrawLength    = atoi (yyargv [2]);
 Tree_DrawBoxWidth  = atoi (yyargv [3]);
 Tree_DrawBoxHeight = atoi (yyargv [4]);
 strncpy (Tree_DrawFileName, yyargv [5], 256);
 Tree_DrawFileName [255] = '\0';
 return TCL_OK;
}

void SetDepthTree
# ifdef HAVE_ARGS
 (int yyDepth)
# else
 (yyDepth) int yyDepth;
# endif
{
 Tree_DrawDepth = yyDepth;
}

void SetBoxTree
# ifdef HAVE_ARGS
 (int yyWidth, int yyHeight)
# else
 (yyWidth, yyHeight) int yyWidth, yyHeight;
# endif
{
 Tree_DrawBoxWidth  = yyWidth;
 Tree_DrawBoxHeight = yyHeight;
}

static void yyDrawTree
# ifdef HAVE_ARGS
 (tTree yyt, ClientData yyclass)
# else
 (yyt, yyclass) tTree yyt; ClientData yyclass;
# endif
{
 char yyString [128];
 yytFirstLast yyDummy;
# ifdef SUPPORT_TVA
 rbool yyPrevTreatTVAasChild = Tree_TreatTVAasChild;
 Tree_TreatTVAasChild = rfalse;
# endif
 yyDummy.yyfirst = yyMaxCoord;
 yymaxx = yymaxy = 0;
 yyMark (yyt); yyphase1 = rtrue ;
 yySetY ((tTree) & yyt, yyt, 0, 0, 0);
 yyMark (yyt); yyphase1 = rfalse;
 yySetY ((tTree) & yyt, yyt, 0, 0, 0);
 yyMark (yyt);
 yySetX ((tTree) & yyt, yyt, 0, & yyDummy);
 yymaxx = Max (yymaxx, 16);
 yymaxy = Max (yymaxy, 16);
 sprintf (yyString, "%d %d %d %d %d %d {%s}", yymaxx, yymaxy, Tree_DrawBoxWidth, Tree_DrawBoxHeight, Tree_DrawDepth, Tree_DrawLength, Tree_DrawFileName);
 Tcl_VarEval (yygInterp, "draw_tree ", yyString, NULL);
 TraverseTreeTD (yyt, yyDrawNode);
# ifdef SUPPORT_TVA
 Tree_TreatTVAasChild = yyPrevTreatTVAasChild;
# endif
}

void DrawTree
# ifdef HAVE_ARGS
 (tTree yyt)
# else
 (yyt) tTree yyt;
# endif
{
 int yyCode;
 Tcl_Interp * yyInterp;
 char yyPath [256], * yyp;

 Tcl_FindExecutable ("");
 yygInterp = yyInterp = Tcl_CreateInterp ();
 yyCode = Tcl_Init (yyInterp);
 if (yyCode != TCL_OK) {
  ErrorMessageI (xxTclTkError, xxError, NoPosition, xxString, Tcl_GetStringResult (yyInterp));
  goto yyReturn;
 }
 yyCode = Tk_Init (yyInterp);
 if (yyCode != TCL_OK) {
  ErrorMessageI (xxTclTkError, xxError, NoPosition, xxString, Tcl_GetStringResult (yyInterp));
  goto yyReturn;
 }
 Tcl_StaticPackage (yyInterp, "Tk", Tk_Init, (Tcl_PackageInitProc *) NULL);

 Tcl_CreateCommand (yyInterp, "put_attr", yyPutAttr, (ClientData) NULL, NULL);
 Tcl_CreateCommand (yyInterp, "search_pos", yySearch, (ClientData) NULL, NULL);
 Tcl_CreateCommand (yyInterp, "draw_subtree", yyDrawSubTree, (ClientData) NULL, NULL);
 Tcl_CreateCommand (yyInterp, "call_attr", yyCallAttr, (ClientData) NULL, NULL);
 Tcl_CreateCommand (yyInterp, "set_param", yySetParam, (ClientData) NULL, NULL);
 yyCode = Tcl_EvalFile (yyInterp, "Tree.tcl");
 if (yyCode != TCL_OK) {
  yyp = (char *) getenv ("HOME");
  if (yyp) {
   strcat (strcpy (yyPath, yyp), "/.Tree.tcl");
   yyCode = Tcl_EvalFile (yyInterp, yyPath);
  }
 }
 if (yyCode != TCL_OK) {
  yyp = (char *) getenv ("CT_DIR");
  if (yyp) {
   strcat (strcpy (yyPath, yyp), "/lib/cg/Tree.tcl");
   yyCode = Tcl_EvalFile (yyInterp, yyPath);
  }
 }
 if (yyCode != TCL_OK) {
  yyCode = Tcl_EvalFile (yyInterp, "/home/cocktail/lib/cocktail/cg/Tree.tcl");
 }
 if (yyCode != TCL_OK) {
  ErrorMessageI (xxTclTkError, xxError, NoPosition, xxString, Tcl_GetStringResult (yyInterp));
  goto yyReturn;
 }
 yyDrawTree (yyt, NULL);
 Tk_MainLoop ();
yyReturn: Tcl_DeleteInterp (yyInterp);
}

void ConfigureTree
# ifdef HAVE_ARGS
 (char * yyParameter, char * yyValue)
# else
 (yyParameter, yyValue) char * yyParameter; char * yyValue;
# endif
{
 if (yyParameter == NULL || yyValue == NULL) return;
        if (strcmp (yyParameter, "CheckReportNoTree") == 0) {
  Tree_CheckReportNoTree = atoi (yyValue) != 0;
 } else if (strcmp (yyParameter, "CheckReportNodes") == 0) {
  Tree_CheckReportNodes = atoi (yyValue) != 0;
 } else if (strcmp (yyParameter, "DrawBoxHeight") == 0) {
  Tree_DrawBoxHeight = atoi (yyValue);
 } else if (strcmp (yyParameter, "DrawBoxWidth") == 0) {
  Tree_DrawBoxWidth = atoi (yyValue);
 } else if (strcmp (yyParameter, "DrawDepth") == 0) {
  Tree_DrawDepth = atoi (yyValue);
 } else if (strcmp (yyParameter, "DrawLength") == 0) {
  Tree_DrawLength = atoi (yyValue);
 } else if (strcmp (yyParameter, "DrawFileName") == 0) {
  strncpy (Tree_DrawFileName, yyValue, 256);
  Tree_DrawFileName [255] = '\0';
 } else if (strcmp (yyParameter, "TreatTVAasChild") == 0) {
# ifdef SUPPORT_TVA
  Tree_TreatTVAasChild = atoi (yyValue) != 0;
# endif
 } else {
  ErrorMessageI (xxConfigureUnknownParam, xxError, NoPosition, xxString, yyParameter);
 }
}

void BeginTree ARGS ((void))
{
/* line 27 "expr.ast" */

  id_sin = MakeIdent1 ("sin");
  id_cos = MakeIdent1 ("cos");
  id_tan = MakeIdent1 ("tan");

}

void CloseTree ARGS ((void))
{
}
