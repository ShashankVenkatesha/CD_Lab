%{
#include<stdio.h>
int line=1;
# define  ID_tok  1
# define COMMA_tok  2
#define REL_OP_tok 3
#define NUMBER_tok 4
#define KEYWORDS_tok 5
%}
binary_ar_op "*"|"/"|"+"|"-"
rel_op "=="|"!="|">"|"<"|"<="|">="
id      [a-z][a-z0-9]*
number    ["+"|"-"]?[0-9]*("."[0-9]+)?
keywords "prabegin"|"parend"|"task"|"begin"|"end"|"integer"|"real"|"do"|"until"|"od"|"send"|"accept"

%%
\n   {line++;  printf("\n%d:",line);}

{binary_ar_op}+ {printf( "An binary_ar_op: %s (%d) at line(%d)\n", yytext,
                   atoi( yytext ),line);}

{rel_op}+ {printf( "An rel_op: %s (%d) at line(%d)\n", yytext,
                   atoi( yytext ),line);}

{id}+ {printf( "An id: %s (%d) at line(%d)\n", yytext,
                   atoi( yytext ),line);}


{number}+ {printf( "An number: %s (%d) at line(%d)\n", yytext,
                   atoi( yytext ),line);}
%%
int yywrap()
{
return 1;
}
main()
{
printf("Enter a string of data\n");
yylex();
}
