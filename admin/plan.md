OVERVIEW
========
This file will be used to track the objectives and progress made in this coursework, tracking all the dates in which goals were set and achieved.

Objectives (last updated 28/02/2021)
------------------------------------
- Set up working environment
- Build base structure for repo
- Flesh out basic lexer / parser / AST for extremely minimal language:
  + i.e. ints, basic operators, variables

Changelog
---------
28/02/2021: Set up a lot of files for project, started planning AST, as well as parser + lexer. Current goal is to create a working compiler for the following code:
```
int main()
{
  return 2;
}
```
Not planning on adding any further constructs until the suitable AST framework has been established for this.

02/01/2021: Started building skeleton of AST, planning on switching parser + lexer to the [ANSI C grammar specification](https://www.lysator.liu.se/c/ANSI-C-grammar-l.html), and building the syntax tree from the Yacc file similar to lab 2.
