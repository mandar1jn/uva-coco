%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ccngen/ast.h"
#include "ccngen/enum.h"
#include "parser.h"
#include "palm/str.h"
#include "global/globals.h"
#include "palm/ctinfo.h"

// Use for error messages, see parser.y
extern int yyerror(char *errname);

#define FILTER(token) \
  global.col += yyleng;  \
  return( token);

#define LINEBUF_SIZE 256
#define YY_NO_UNPUT
#define YY_NO_INPUT

static inline void token_action();

int yycolumn = 1;
#define YY_USER_ACTION token_action();


%}

%p 6000 /* set positions to 6000 */
%e 2000 /* set nodes to 1100 */
%option noyywrap
%option nounput
%option yylineno

DIGIT     [0-9]
LOWER     [a-z]
UPPER     [A-Z]
ALPHA     [A-Za-z]
ALPHANUM  [A-Za-z0-9]

%%

"("                        { FILTER( BRACKET_L); }
")"                        { FILTER( BRACKET_R); }
"["                        { FILTER( SQUARE_L); }
"]"                        { FILTER( SQUARE_R); }
"{"                        { FILTER( CURLY_L); }
"}"                        { FILTER( CURLY_R); }
","                        { FILTER( COMMA); }
";"                        { FILTER( SEMICOLON); }

"-"                        { FILTER( MINUS); }
"+"                        { FILTER( PLUS);  }
"*"                        { FILTER( STAR);  }
"/"                        { FILTER( SLASH);  }
"%"                        { FILTER( PERCENT);  }
"!"                        { FILTER( NOT); }

"<="                       { FILTER( LE);    }
"<"                        { FILTER( LT);    }
">="                       { FILTER( GE);    }
">"                        { FILTER( GT);    }
"=="                       { FILTER( EQ);    }
"!="                       { FILTER( NE);    }
"&&"                       { FILTER( AND);    }
"||"                       { FILTER( OR);    }

"="                        { FILTER( LET);    }

"true"                     { FILTER( TRUEVAL); }
"false"                    { FILTER( FALSEVAL); }

"if"                       { FILTER( IF);    }
"while"                    { FILTER( WHILE);    }
"do"                       { FILTER( DO);    }
"for"                      { FILTER( FOR);    }
"return"                   { FILTER( RETURN);    }

"void"                     { FILTER( VOID);    }
"extern"                   { FILTER( EXTERN);    }
"export"                   { FILTER( EXPORT);    }

{ALPHA}{ALPHANUM}*         { yylval.id = STRcpy(yytext);
                             FILTER( ID);
                           }

{DIGIT}+                   { yylval.cint=atoi(yytext);
                             FILTER( INT);
                           }

{DIGIT}+"."{DIGIT}*        { yylval.cflt=atof(yytext);
                             FILTER( FLOAT);
                           }

\n.*                       {
                             yycolumn = 1;
                             global.line += 1;
                             global.col = 0;
                             yyless(1);
                           }

[ \t]                      { global.col += yyleng;
                           }

"//".*                     { global.col = 0;
                             global.line += 1;
                            //  yyless(1);
                           }
%%

static inline void token_action() {
    yylloc.first_line = yylloc.last_line = yylineno;
    yylloc.first_column = yycolumn;
    yylloc.last_column = yycolumn + yyleng - 1;
    yycolumn += yyleng;
}
