OVERVIEW
========
This file will be used to track the objectives and progress made in this coursework, tracking all the dates in which goals were set and achieved.

Objectives (last updated 05/03/2021)
------------------------------------
- <del> Set up working environment</del>  (Marked complete 02/02/2021)
- <del> Build base structure for repo</del>   (Marked complete 02/02/2021)
- <del> Flesh out basic lexer / parser / AST for extremely minimal language:</del>  (Reworked 02/02/2021)
  + <del> i.e. ints, basic operators, variables</del>
- Go through parser and add AST mapping using existing AST classes
- Compile and run AST for basic test case (i.e. run compiler.cpp)
- Solve `parseAST()` issue, how to make the lexer / parser use a specified istream

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


**02/03/2021:**
Started building skeleton of AST, planning on switching parser + lexer to the [ANSI C grammar specification](https://www.lysator.liu.se/c/ANSI-C-grammar-l.html), and building the syntax tree from the Yacc file similar to lab 2. Aim is to finish the parser / AST classes so that the previous test program gets parsed into an AST successfully.

**05/03/2021**
Pruned a lot of the unassessed functionality from the lexer and parser, as well as fixed a lot of compilation issues within the AST header files. Currently unsure how to ensure the lexer reads from the ifstream src specified by the top-level cpp file, instead of stdin, causing issues with the global `parseAST()` function. More work needs to be done on the parser to turn the test program into an AST.
