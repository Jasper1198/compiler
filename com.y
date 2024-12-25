%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VARIABLES 100

typedef struct {
    char* name;
    int value;
} Variable;

Variable variables[MAX_VARIABLES];
int var_count = 0;

void yyerror(const char *s);
int yylex();

int lookup_variable(char* name);
void define_variable(char* name, int value);
%}

%union {
    int num;
    char* str;
    struct {
        char* name;
        int value;
    } Variable;
}

%token <num> NUMBER BOOL_VAL FUN
%token <str>  ID 
%token PLUS MINUS MULTIPLY DIVIDE MODULUS GREATER SMALLER EQUAL
%token AND OR NOT DEFINE  IF PRINT_NUM PRINT_BOOL
%token LPAREN RPAREN

%type <num> exp_ exp mul_ add_ and and_ or or_ not TEST_EXP  THEN_EXP ELSE_EXP
%type <num> add min mul div mod gra  sma equ

%type <num> VARIABLE LOGICAL_OP IF_EXP NUM_OP

%%

program:
    program stmt
    | stmt
    ;

stmt: exp
    | def_stmt
    | print_stmt

print_stmt: LPAREN PRINT_NUM exp_ RPAREN { printf("%d\n", $3); }
          | LPAREN PRINT_BOOL exp_ RPAREN { printf($3 ? "#t\n" : "#f\n"); }  

exp_ : LPAREN exp RPAREN  {$$ = $2;}
     | exp 

exp : BOOL_VAL | NUMBER | VARIABLE | NUM_OP 
| LOGICAL_OP | IF_EXP


def_stmt : LPAREN DEFINE ID exp_ RPAREN { define_variable($3, $4); }
VARIABLE : ID { $$ = lookup_variable($1); }   
  

IF_EXP : LPAREN IF TEST_EXP THEN_EXP ELSE_EXP RPAREN { $$ = $3 ? $4 : $5; }
TEST_EXP : exp_  {$$ = $1;}
THEN_EXP : exp_  {$$ = $1;}
ELSE_EXP : exp_  {$$ = $1;}
    

NUM_OP : add     {$$ = $1;}
        | min    {$$ = $1;} 
        | mul    {$$ = $1;}
        | div    {$$ = $1;}
        | mod    {$$ = $1;}
        | gra    {$$ = $1;}
        | sma    {$$ = $1;}
        | equ    {$$ = $1;}

add: LPAREN PLUS exp_ add_ RPAREN { $$ = $3 + $4; }
add_    : exp_ add_         {$$ = $1 + $2;}
        | exp_              {$$ = $1;}
mul: LPAREN MULTIPLY exp mul_ RPAREN { $$ = $3 * $4; }
mul_    : exp_ mul_         {$$ = $1 * $2;}
        | exp_              {$$ = $1;}
min: LPAREN MINUS exp_ exp_ RPAREN { $$ = $3 - $4; }
div: LPAREN DIVIDE exp_ exp_ RPAREN { $$ = $3 / $4; }
mod: LPAREN MODULUS exp_ exp_ RPAREN { $$ = $3 % $4; }
gra: LPAREN GREATER exp_ exp_ RPAREN { $$ = $3 > $4; }
sma: LPAREN SMALLER exp_ exp_ RPAREN { $$ = $3 < $4; }
equ: LPAREN EQUAL exp_ exp_ RPAREN { $$ = ($3 == $4); }

LOGICAL_OP : and | or | not

and: LPAREN AND exp_ and_ RPAREN { $$ = $3 && $4; }
and_    : exp_ and_         {$$ = $1 && $2;}
        | exp_              {$$ = $1;}
or: LPAREN OR exp_ or_ RPAREN { $$ = $3 || $4; }
or_    : exp_ or_         {$$ = $1 || $2;}
        | exp_              {$$ = $1;}
not: LPAREN NOT exp_ RPAREN { $$ = !$3; }


%%

void yyerror(const char *s) {
    fprintf(stderr, "syntax error\n");
}

int lookup_variable(char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    fprintf(stderr, "Undefined variable: %s\n", name);
    exit(1);
}

void define_variable(char* name, int value) {
    if (var_count >= MAX_VARIABLES) {
        fprintf(stderr, "Variable limit exceeded\n");
        exit(1);
    }

    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            fprintf(stderr, "Variable %s already defined\n", name);
            exit(1);
        }
    }
    variables[var_count].name = strdup(name);
    variables[var_count].value = value;
    var_count++;
}

int main() {
    yyparse();
    return 0;
}

