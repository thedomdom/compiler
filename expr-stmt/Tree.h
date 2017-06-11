# ifndef yyTree
# define yyTree

extern char Tree_module_does_not_match_evaluator_module_943672;
extern char generate_Tree_module_without_option_0;

# include "ratc.h"

# include <stdio.h>

# ifndef rbool
# define rbool char
# endif
# define NoTree (tTree) 0L
# define kSTMTS 1
# define kno_stmt 2
# define kSTMT 3
# define kassign_stmt 4
# define kif_stmt 5
# define kwhile_stmt 6
# define kprint_stmt 7
# define kEXPRS 8
# define kno_exprs 9
# define kexprs 10
# define kEXPR 11
# define kint_const 12
# define kfloat_const 13
# define kname 14
# define kunary_expr 15
# define kbinary_expr 16
# define kcond_expr 17
# define kcall_expr 18
# define yyBlockSize 20480

typedef unsigned char Tree_tKind;
typedef unsigned short Tree_tMark;
typedef unsigned short Tree_tLabel;
typedef union Tree_Node * tTree;
typedef tTree tSTMTS;
typedef tTree tEXPRS;
typedef tTree tEXPR;
typedef void (* Tree_tProcTree) ARGS ((tTree));
typedef tTree * yytTreePtr;
typedef struct { tTree yyOld, yyNew; } yytTreeOldToNew;

typedef struct yysTree_Block {
 char yyBlock [yyBlockSize];
 struct yysTree_Block * yySuccessor;
} yytTree_Block, * yytTree_BlockPtr;

/* line 15 "expr.ast" */

  # include "Position.h"
  # include "Idents.h"

  /* tIdent's for function names */
  extern tIdent id_sin, id_cos, id_tan;


# define Tree_InitHead(ptr, kind) ptr->Kind = kind; \
   ptr->yyHead.yyMark = 0; \
   beginNodeHead (ptr)
# ifndef Tree_NodeHead
# define Tree_NodeHead unsigned short yyx, yyy; tTree yyparent;
# endif
typedef struct { Tree_tKind yyKind; Tree_tMark yyMark;
 Tree_NodeHead } Tree_tNodeHead;
typedef struct { Tree_tNodeHead yyHead;
} ySTMTS;
typedef struct { Tree_tNodeHead yyHead;
} yno_stmt;
typedef struct { Tree_tNodeHead yyHead;
tTree Next; tPosition Pos; } ySTMT;
typedef struct { Tree_tNodeHead yyHead;
tTree Next; tPosition Pos; tTree Lhs; tTree Rhs; } yassign_stmt;
typedef struct { Tree_tNodeHead yyHead;
tTree Next; tPosition Pos; tTree Cond; tTree Then; tTree Else; } yif_stmt;
typedef struct { Tree_tNodeHead yyHead;
tTree Next; tPosition Pos; tTree Cond; tTree Body; } ywhile_stmt;
typedef struct { Tree_tNodeHead yyHead;
tTree Next; tPosition Pos; tTree Arguments; } yprint_stmt;
typedef struct { Tree_tNodeHead yyHead;
} yEXPRS;
typedef struct { Tree_tNodeHead yyHead;
} yno_exprs;
typedef struct { Tree_tNodeHead yyHead;
tTree Next; tTree Expr; } yexprs;
typedef struct { Tree_tNodeHead yyHead;
tPosition Pos; } yEXPR;
typedef struct { Tree_tNodeHead yyHead;
tPosition Pos; int Value; } yint_const;
typedef struct { Tree_tNodeHead yyHead;
tPosition Pos; double Value; } yfloat_const;
typedef struct { Tree_tNodeHead yyHead;
tPosition Pos; tIdent Ident; } yname;
typedef struct { Tree_tNodeHead yyHead;
tPosition Pos; char Op; tTree Argument; } yunary_expr;
typedef struct { Tree_tNodeHead yyHead;
tPosition Pos; char Op; tTree Left; tTree Right; } ybinary_expr;
typedef struct { Tree_tNodeHead yyHead;
tPosition Pos; tTree Cond; tTree Then; tTree Else; } ycond_expr;
typedef struct { Tree_tNodeHead yyHead;
tPosition Pos; tIdent Name; tTree Arguments; } ycall_expr;

union Tree_Node {
 Tree_tKind Kind;
 Tree_tNodeHead yyHead;
 ySTMTS STMTS;
 yno_stmt no_stmt;
 ySTMT STMT;
 yassign_stmt assign_stmt;
 yif_stmt if_stmt;
 ywhile_stmt while_stmt;
 yprint_stmt print_stmt;
 yEXPRS EXPRS;
 yno_exprs no_exprs;
 yexprs exprs;
 yEXPR EXPR;
 yint_const int_const;
 yfloat_const float_const;
 yname name;
 yunary_expr unary_expr;
 ybinary_expr binary_expr;
 ycond_expr cond_expr;
 ycall_expr call_expr;
};

extern const unsigned short Tree_NodeSize [19];
extern const Tree_tKind Tree_TypeRange [19];
extern const char * const Tree_NodeName [];

extern rbool Tree_CheckReportNoTree, Tree_CheckReportNodes;
extern int Tree_DrawDepth;
extern int Tree_DrawLength;
extern int Tree_DrawBoxWidth;
extern int Tree_DrawBoxHeight;
extern char Tree_DrawFileName [];
# ifdef SUPPORT_TVA
extern rbool Tree_TreatTVAasChild;
# endif

extern tTree TreeRoot;
extern unsigned long Tree_HeapUsed;
extern yytTree_BlockPtr Tree_BlockList;
extern char * Tree_PoolFreePtr, * Tree_PoolStartPtr;

extern void (* Tree_Exit) ARGS ((void));
extern tTree Tree_Alloc ARGS ((unsigned long yySize));
extern tTree MakeTree ARGS ((Tree_tKind yyKind));
extern rbool Tree_IsType ARGS ((register tTree yyt,
 register Tree_tKind yyKind));

extern tTree mSTMTS
 ARGS ((void));
extern tTree mno_stmt
 ARGS ((void));
extern tTree mSTMT
 ARGS ((tTree pNext, tPosition pPos));
extern tTree massign_stmt
 ARGS ((tTree pNext, tPosition pPos, tTree pLhs, tTree pRhs));
extern tTree mif_stmt
 ARGS ((tTree pNext, tPosition pPos, tTree pCond, tTree pThen, tTree pElse));
extern tTree mwhile_stmt
 ARGS ((tTree pNext, tPosition pPos, tTree pCond, tTree pBody));
extern tTree mprint_stmt
 ARGS ((tTree pNext, tPosition pPos, tTree pArguments));
extern tTree mEXPRS
 ARGS ((void));
extern tTree mno_exprs
 ARGS ((void));
extern tTree mexprs
 ARGS ((tTree pNext, tTree pExpr));
extern tTree mEXPR
 ARGS ((tPosition pPos));
extern tTree mint_const
 ARGS ((tPosition pPos, int pValue));
extern tTree mfloat_const
 ARGS ((tPosition pPos, double pValue));
extern tTree mname
 ARGS ((tPosition pPos, tIdent pIdent));
extern tTree munary_expr
 ARGS ((tPosition pPos, char pOp, tTree pArgument));
extern tTree mbinary_expr
 ARGS ((tPosition pPos, char pOp, tTree pLeft, tTree pRight));
extern tTree mcond_expr
 ARGS ((tPosition pPos, tTree pCond, tTree pThen, tTree pElse));
extern tTree mcall_expr
 ARGS ((tPosition pPos, tIdent pName, tTree pArguments));

extern void ReleaseTree ARGS ((tTree yyt));
extern void ReleaseTreeModule ARGS ((void));
extern void WriteTreeNode ARGS ((FILE * yyyf, tTree yyt));
extern tTree ReadTree ARGS ((FILE * yyyf));
extern void WriteTree ARGS ((FILE * yyyf, tTree yyt));
extern void WriteTreeXML ARGS ((FILE * yyyf, tTree yyt));
extern void PutTree ARGS ((FILE * yyyf, tTree yyt));
extern tTree GetTree ARGS ((FILE * yyyf));
extern void TraverseTreeTD ARGS ((tTree yyt, Tree_tProcTree yyyProc));
extern void TraverseTreeBU ARGS ((tTree yyt, Tree_tProcTree yyProc));
extern tTree ReverseTree ARGS ((tTree yyt));
extern void ForallTree ARGS ((tTree yyt, Tree_tProcTree yyProc));
extern tTree CopyTree ARGS ((tTree yyt));
extern rbool IsEqualTree ARGS ((tTree yyt1, tTree yyt2));
extern rbool CheckTree ARGS ((tTree yyt));
extern void QueryTree ARGS ((tTree yyt));
extern void DrawTree ARGS ((tTree yyt));
extern void SetDepthTree ARGS ((int yyDepth));
extern void SetBoxTree ARGS ((int yyWidth, int yyHeight));
extern void ConfigureTree ARGS ((char * yyParameter, char * yyValue));
extern void InitTree ARGS ((register tTree yyt));
extern void BeginTree ARGS ((void));
extern void CloseTree ARGS ((void));

# endif
