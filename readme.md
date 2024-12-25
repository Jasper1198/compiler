# This is a program that can parser some fundamental lisp program.
the features include:
1. Syntax Validation
2. Print Implement
3. Numerical Operations 
4. Logical Operations 
5. if Expression

# Step
1. bison -d com.y
2. flex com.l
3. gcc lex.yy.c com.tab.c
4. ./a