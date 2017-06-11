/* Project:  COCKTAIL training
 * Descr:    A simple pocket computer (scanner, parser, evaluator)
 * Kind:     Some commonly used typedef's and functions
 * Author:   Prof. Dr. Juergen Vollmer <vollmer@dhbw-karlsruhe.de>
 * $Id: util.c,v 1.2 2010/04/26 16:34:26 vollmer Exp vollmer $
 */

# include <stdio.h>
# include <math.h>
# include "Errors.h"
# include "util.h"

const char *operator2string (tOperator op)
{
  switch (op) {
  case op_none:   return "<none>";
  case op_plus:   return "+";
  case op_minus:  return "-";
  case op_mult:   return "*";
  case op_div:    return "/";
  case op_mod:    return "%";
  case op_pow:    return "**";
  case op_lt:     return "<";
  case op_le:     return "<=";
  case op_gt:     return ">";
  case op_ge:     return ">=";
  case op_eq:     return "==";
  case op_ne:     return "!=";
  case op_not:    return "!";
  case op_and:    return "&";
  case op_or:     return "|";
  case op_in:     return "in";
  case op_div2:   return "div2";
  case op_is:     return "is";
  default:        FATAL_ERROR();
  }
}

double evalUnary (tOperator op, double argument, tPosition pos)
/* compute "op argument" */
{
  switch (op) {
  case op_minus: return -argument;
  case op_plus:  return argument;
  case op_not:   return argument == 0? 1 : 0;
  default:   	 FATAL_ERROR();
  }
}

double evalBinary (tOperator op, double left, double right, tPosition pos)
/* compute "left op right" */
{
  switch (op) {
  case op_minus: return left-right;
  case op_plus:  return left+right;
  case op_mult:  return left*right;
  case op_div:   if (right == 0.0) {
      WritePosition (stderr, pos);
      fprintf (stderr, " division bright zero\n");
      return 0.0;
    } else {
      return left/right;
    }
  case op_pow:   return pow (left,right);
  case op_lt:    return left <  right;
  case op_le:    return left <= right;
  case op_gt:    return left >  right;
  case op_ge:    return left >= right;
  case op_eq:    return left == right;
  case op_ne:    return left != right;
  case op_and:   return left && right;
  case op_or:    return left || right;
  default:   	 FATAL_ERROR();
  }
}

/*---------------------------------------------------------------------------*/

const char *type2string (tType type)
{
  switch (type) {
  case type_none:   return "<none>";
  case type_error:  return "<error>";
  case type_bool:   return "BOOL";
  case type_int:    return "INT";
  case type_float:  return "FLOAT";
  default:          FATAL_ERROR();
  }
}

tType result_type (tOperator op, tType left, tType right, tPosition pos)
{
  switch (op) {
  case op_lt:  case op_le: case op_gt:  case op_ge:  case op_eq:  case op_ne:
    /* relational operators */
    return type_bool;

  case op_and: case op_or: case op_not:
    /* boolean operators */
    return type_bool;

  case op_mod:
    /* modulo returns an integer */
    return type_int;

  case op_pow:
    /* power returns a float */
    return type_float;

  case op_plus: case op_minus: case op_mult: case op_div:
    /* numeric operators, return a numeric type */
    if (right == type_none && is_numeric_type (left)) return left; /* unary operator  */

    /* binary operators */
    if (is_numeric_type (left) && is_numeric_type (right)) {
      /* if types differ, return the "larger" type with: "INT < FLOAT" */
      return (left  == right) ? left : type_float;
    }

    /* may be an argument has a boolean type */
    Message ("Type mismatch", xxError, pos);
    return type_error;

  default:
    FATAL_ERROR();
    return type_error;
  }
}

tType argument_type (tOperator op, tType left, tType right, tPosition pos)
{
  switch (op) {
  case op_lt:  case op_le:  case op_gt:  case op_ge:  case op_eq:  case op_ne:
    /* relational operators take numeric or boolean argument */
    if (left == right) return left;

    if (is_numeric_type (left) && is_numeric_type (right)) {
      /* if types differ, return the "larger" type with: "INT < FLOAT" */
      return (left == right)? left : type_float;
    }

    Message ("Type mismatch", xxError, pos);
    return type_error;

  case op_mod:
    /* arguments should be coerced to INT */
    if (is_numeric_type (left) && is_numeric_type (right)) {
      return type_int;
    }

    Message ("Type mismatch", xxError, pos);
    return type_error;

  case op_plus: case op_minus: case op_mult: case op_div: case op_pow:
    /* numeric operators take numeric arguments */
    if (right == type_none && is_numeric_type (left)) return left; /* unary operators */

    if (is_numeric_type (left) && is_numeric_type (right)) {
      /* if types differ, return the "larger" type with: "INT < FLOAT" */
      return (left == right)? left : type_float;
    }

    Message ("Type mismatch", xxError, pos);
    return type_error;

  case op_and: case op_or: case op_not:
    /* boolean operators take boolean arguments */
    if (left == type_bool && (right == type_none || right == type_bool)) return type_bool;

    Message ("Type mismatch", xxError, pos);
    return type_error;

  default:
    FATAL_ERROR();
    return type_error;
  }
}

/*---------------------------------------------------------------------------*/
const char *coercion2string (tCoercion co)
{
  switch (co) {
  case coerce_none:  return "<none>";
  case coerce2bool:  return "coerce2bool";
  case coerce2int:   return "coerce2int";
  case coerce2float: return "coerce2float";
  default:           FATAL_ERROR();
  }
}

/*---------------------------------------------------------------------------*/
