#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

// Define operators and their priorities
#define OPERATORS "+-*/="
#define PRI_PLUSMINUS 1
#define PRI_MULTDIV 2

// Function to check if a character is an operator
int isOperator(char ch) {
   return strchr(OPERATORS, ch) != NULL;
}

// Function to convert infix expression to postfix
void infix_to_postfix(char *formula, char *output) {
   char stack[MAX_LENGTH];
   int stack_top = 0;
   output[0] = '\0';

   for (int i = 0; formula[i] != '\0'; i++) {
       char ch = formula[i];
       if (!isOperator(ch)) {
           strncat(output, &ch, 1);
       } else if (ch == '(') {
           stack[stack_top++] = '(';
       } else if (ch == ')') {
           while (stack_top > 0 && stack[stack_top - 1] != '(') {
               output[strlen(output)] = stack[--stack_top];
           }
           stack_top--; // Pop '('
       } else {
           while (stack_top > 0 && stack[stack_top - 1] != '(' &&
                  ((ch == '+' || ch == '-') ? PRI_PLUSMINUS : PRI_MULTDIV) <=
                      ((stack[stack_top - 1] == '+' || stack[stack_top - 1] == '-') ? PRI_PLUSMINUS : PRI_MULTDIV)) {
               output[strlen(output)] = stack[--stack_top];
           }
           stack[stack_top++] = ch;
       }
   }
   // Leftover
   while (stack_top > 0) {
       output[strlen(output)] = stack[--stack_top];
   }
}

// Function to generate three address code
void generate3AC(char *pos) {
   printf("### THREE ADDRESS CODE GENERATION ###\n");
   char exp_stack[MAX_LENGTH][MAX_LENGTH];
   int stack_top = 0;
   int t = 1;

   for (int i = 0; pos[i] != '\0'; i++) {
       char ch = pos[i];
       if (!isOperator(ch)) {
           sprintf(exp_stack[stack_top++], "%c", ch);
       } else {
           printf("t%d := %s %c %s\n", t, exp_stack[stack_top - 2], ch, exp_stack[stack_top - 1]);
           stack_top -= 2;
           sprintf(exp_stack[stack_top++], "t%d", t++);
       }
   }
}

int main() {
   char expression[MAX_LENGTH];
   printf("INPUT THE EXPRESSION: ");
   fgets(expression, MAX_LENGTH, stdin);
   expression[strcspn(expression, "\n")] = '\0'; // Remove newline character from input

   char postfix[MAX_LENGTH];
   infix_to_postfix(expression, postfix);

   generate3AC(postfix);

   return 0;
}
