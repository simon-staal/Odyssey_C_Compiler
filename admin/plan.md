OVERVIEW
========
This file will be used to track the objectives and progress made in this coursework, tracking all the dates in which goals were set and achieved.

Objectives (last updated 02/03/2021)
------------------------------------
- Go through parser and add AST mapping using existing AST classes
- Compile and run AST for basic test case (i.e. run compiler.cpp)

Changelog
---------
**28/02/2021:**
Set up a lot of files for project, started planning AST, as well as parser + lexer. Current goal is to create a working compiler for the following code:
```
int main()
{
  return 2;
}
```
Not planning on adding any further constructs until the suitable AST framework has been established for this.


**02/01/2021:**
Started building skeleton of AST, planning on switching parser + lexer to the [ANSI C grammar specification](https://www.lysator.liu.se/c/ANSI-C-grammar-l.html), and building the syntax tree from the Yacc file similar to lab 2. Aim is to finish the parser / AST classes so that the previous test program gets parsed into an AST successfully.
