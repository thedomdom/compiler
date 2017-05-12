/* Project:  COCKTAIL training
 * Descr:    A simple scanner generated with rex
 * Kind:     C-main function, fully implemented solution
 * Author:   Dr. Juergen Vollmer <juergen.vollmer@informatik-vollmer.d
 * $Id: main.c.in,v 1.4 2010/04/15 12:52:49 vollmer Exp $
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "Position.h"
# include "l_scan.h"

int main (int argc, char *argv[])
{
   int Token, Count = 0;
   if (argc == 2) {
     if (strcmp (argv[1], "-h") == 0) {
       fprintf (stderr,
		"usage: scan [-h] [file]\n"
		"  simple scanner, reads `file' or stdin\n"
		"  -h: Help\n");
       exit (0);
     }
     l_scan_BeginFile (argv[1]);
     /* Read from file argv[1].
      * If this routine is not called, stdin is read.
      */
   }
   for (Token =  l_scan_GetToken ();
	Token != l_scan_EofToken;
	Token = l_scan_GetToken ()) {
      Count ++;
      WritePosition (stdout, l_scan_Attribute.Position); printf (" ");
      switch (Token) {
      case tok_int_const:
	printf ("int_const    : %s\n",l_scan_Attribute.int_const.Value);
	break;
      case tok_float_const:
	printf ("float_const  : %s\n",l_scan_Attribute.float_const.Value);
	break;
      case tok_identifier:
	printf ("identifier   : %s\n",l_scan_Attribute.identifier.Value);
	break;
      case tok_string_const:
	printf ("string_const : %s\n",l_scan_Attribute.string_const.Value);
	break;
      case tok_PROGRAM:
	printf ("PROGRAM\n");
	break;
      case tok_DECLARATIONS:
	printf ("DECLARATIONS\n");
	break;
      case tok_INPUT:
	printf ("INPUT\n");
	break;
      case tok_OUTPUT:
	printf ("OUTPUT\n");
	break;
	
      case tok_STRING:
	printf ("STRING\n");
	break;
      case tok_INT:
	printf ("INT\n");
	break;
      case tok_FLOAT:
	printf ("FLOAT\n");
	break;
	
      case tok_BEGIN:
	printf ("BEGIN\n");
	break;
      case tok_END:
	printf ("END\n");
	break;
	
      case tok_IF:
	printf ("IF\n");
	break;
      case tok_THEN:
	printf ("THEN\n");
	break;
      case tok_ELSE:
	printf ("ELSE\n");
	break;
      case tok_ENDIF:
	printf ("ENDIF\n");
	break;
      
      case tok_WHILE:
	printf ("WHILE\n");
	break;
      case tok_DO:
	printf ("DO\n");
	break;
      case tok_ENDWHILE:
	printf ("ENDWHILE\n");
	break;
	
      case tok_FOR:
	printf ("FOR\n");
	break;
      case tok_SEMICOLON:
	printf ("SEMICOLON\n");
	break;
      case tok_ENDFOR:
	printf ("ENDFOR\n");
	break;
	
      case tok_LT:
	printf ("<\n");
	break;
      case tok_GT:
	printf (">\n");
	break;
      case tok_EQUALS:
	printf ("== EQUALS\n");
	break;
      case tok_ASSIGN:
	printf ("= ASSIGN\n");
	break;
	
      case tok_PLUS:
	printf ("+\n");
	break;
      case tok_MINUS:
	printf ("-\n");
	break;
      case tok_MULT:
	printf ("*\n");
	break;
      case tok_DIVIDE:
	printf ("/\n");
	break;
      case tok_BRACKETOP:
	printf ("Bracket (\n");
	break;
      case tok_BRACKETCL:
	printf ("Bracket )\n");
	break;
      default: fprintf (stderr, "FATAL ERROR, unknown token\n");
      }
   }
   printf ("Token count: %d\n", Count);
   return 0;
}
