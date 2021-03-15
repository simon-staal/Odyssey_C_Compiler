OVERVIEW
========
This file will be used to track the objectives and progress made in this coursework, tracking all the dates in which goals were set and achieved.

Objectives (last updated 12/03/2021)
------------------------------------
- <del> Set up working environment</del>  (Marked complete 02/03/2021)
- <del> Build base structure for repo</del>   (Marked complete 02/03/2021)
- <del> Flesh out basic lexer / parser / AST for extremely minimal language:</del>  (Reworked 02/03/2021)
  + <del> i.e. ints, basic operators, variables</del>
- <del> Go through parser and add AST mapping using existing AST classes</del>  (Reworked 12/03/2021)
- <del> Compile and run AST for basic test case (i.e. run compiler.cpp)</del> (Marked complete 12/03/2021)
- <del> Solve `parseAST()` issue, how to make the lexer / parser use a specified istream</del> (Marked complete 10/03/2021)
- Find root of shift-reduce conflict in parser (good luck - **Note: Discussed with TA, told it wasn't really a problem, try %nonassociative or smth**)
- <del> Refactor header files to have implementation in seperate cpp files. Also group classes together in the same headers (i.e. put return, )</del> (Marked complete 12/03/2021)
- Extend AST to fully support all basic features outlined in the [**compiler spec**](../c_compiler.md)
- Start codegen implementation for current AST nodes so that our compiler is able to produce assembly for base test case

Building AST Correctly (last updated 14/03/2021)
------------------------------------------------
This list will keep track of the [pre-included test cases](../compiler_tests) our AST builds correctly for. The way this testing is done (currently) is by manually inspecting the graphically rendered AST (done using the `PrettyPrint()` method) and ensuring it matches what we expect.
- [**default/test_RETURN.c:**](../compiler_tests/default/test_RETURN.c) Function returning integer constant.
- [**local_var/return_constant.c:**](../compiler_tests/local_var/return_constant.c) Function returning  integer constant.
- [**local_var/identity.c:**](../compiler_tests/local_var/identity.c) Function returning variable.
- [**integer/add.c:**](../compiler_tests/integer/add.c) Function taking 2 input parameters (int variables), returning the sum of both.
- [**if_else_false.c**](../compiler_tests/control_flow/if_else_false.c) Function with a literal 0 in the condition of an if/else statement with return statements.
- [**if_else_true.c**](../compiler_tests/control_flow/if_else_true.c) Same as above but with literal 1.
- [**if_false.c**](../compiler_tests/control_flow/if_false.c) Function with a literal 0 in the condition of an exclusive if statement with return statements.
- [**if_true.c**](../compiler_tests/control_flow/if_true.c) Same as above but with literal 1.


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

**05/03/2021:**
Pruned a lot of the unassessed functionality from the lexer and parser, as well as fixed a lot of compilation issues within the AST header files. Currently unsure how to ensure the lexer reads from the ifstream src specified by the top-level cpp file, instead of stdin, causing issues with the global `parseAST()` function. More work needs to be done on the parser to turn the test program into an AST.

**10/03/2021:**
Completed all the necessary ast nodes for minimal code example, and added the implementation in the parser. Additionally fixed the issue to ensure the lexer / parser read from the fstream specified in compiler.cpp. Currently unable to test functionality as I'm obtaining a compilation error when trying to make the parser:
```
src/parser.y:226.1-14: error: syntax error, unexpected identifier
 jump_statement
 ^^^^^^^^^^^^^^
```
No clue what is causing this error, will update when this is solved.

*Update:*
Resolved the parser error, was something dumb. Now experiencing a lot of compiler errors, fixed most of the issues in the ast, top error is now:
```
include/ast.hpp:27:29: error: storage class specified for ‘parseAST’
 extern const Node *parseAST();
```
Unsure how to solve this, referred back to lab 2 and tried to copy how it was done but still experiencing errors. Also really weirdly second error is from the stdlib:
```
/usr/include/assert.h:66:1: error: expected unqualified-id before string constant
 __BEGIN_DECLS
 ^
```

**12/03/2021:**
Solved all issues with parser / ast (turned out there was a missing `}` somewhere lol), `compiler.cpp` now fully compiles with new makefile, and produces the expected AST for the base test case we've been working towards from the start! From here the next steps are to start implementing code generation for the current AST constructs, as well as further extending the AST to extend the functionality of the compiler.

**14/03/2021:**
Kai had a small git commit problem, the refactor branch is now fucked, but I've moved all his new work (starting on ast for binary operations) into main, and have it working. There was a bug in the way function parameters were being parse / generated into an AST, which has also been fixed. I've updated the way declarations work in the AST, as all the List stuff for scalability isn't required right now and I'm not sure when it will be, so for now this will make our AST simpler until we reach the point where we need the list extension (all old code commented out as legacy stuff). Also added a new section in log to track which pre-included test cases have the correct AST generated, as this is relevant in meeting our targets. Current plan is to continue working on developing the AST / parser.

*Update_1:*
Added new script `add_ast.sh` in base directory because creating new ast files for different constructs is getting quite tedious in terms of filepaths and shit. This script takes the name of the hpp/cpp file (without the ast prefix) as the first parameter and an optional second parameter for a deeper directory to store into (sub-directories within the ast/ directory), creates the necessary files in the correct directories and adds them to git. For more info the script usage just run `./add_ast.sh` in the base directory.

*Update_2:*
Added `IfElse` class in AST for representing if-then-else statements, and updated the parser to use this new class. Added working tests to the list. Important to note that 'boolean' literals are currently being evaluated as integer literals, but this is probably how we are going to have literals be interpreted anyways since the spec doesn't mention `bool` data types. Also worth looking for tests with more complicated expressions in the condition field.

**15/03/2021:**
Making the rest of the ast files for operators proved to be kinda tedious so I made a script 'add_and_make_file_ast.sh' which is pretty easy to understand from looking at it. It builds off Simon's last 'add_ast.sh' script and can be used for files which are very similar but differ by a word or so. Can change the file template later as well.
In terms of ast files I will finish adding and verifying that they function in the simple test case 'return x(op)y;'.
Feel like we might need to use the script in the future as well when we add codegen or other global functionality.
Might want to do something about 'ast.hpp' adding stuff is tedious.