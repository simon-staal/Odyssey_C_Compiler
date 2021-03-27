OVERVIEW
========
This file will be used to track the objectives and progress made in this coursework, tracking all the dates in which goals were set and achieved.

Objectives (last updated 27/03/2021)
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
- <del> Extend AST to fully support all basic features outlined in the [**compiler spec**](../c_compiler.md)</del> (Marked complete 18/03/2021)
- <del> Start codegen implementation for current AST nodes so that our compiler is able to produce assembly for base test case</del> (Reworked 17/03/2021)
- <del> Go through QEMU stuff to get a test script working</del> (Marked complete 18/03/2021)
- <del> Continue to build codegen implementation for current AST nodes, try to compile test cases for which the correct AST can be built.</del> (Marked complete 23/03/2021)
- <del> Extend AST to support intermediate features outlined in the [**compiler spec**](../c_compiler.md)</del> (Reworked 22/03/2021)
- <del>Extend compiler to support intermediate features outlined in the [**compiler spec**](../c_compiler.md)</del> (Reworked 25/03/2021)
- <del> Go through failing test-cases in functions and fix what needs to be fixed</del> (Marked complete 25/03/2021)
- <del> Go through AST and check every file (except operators)</del> (Marked complete 23/03/2021)
- <del> Add void to primitives and make sure it works</del> (Reworked 25/03/2021)
- <del>Check memory being allocated for called function arguments</del> (Marked complete 23/03/2021)
- Go through parser to make sure everything is added appropriately
- <del>Implement `sizeof()` and add types `char`, `unsigned` and `void` (?) to pass [**types**](../compiler_tests/types)</del> (Marked complete 27/03/2021)
- <del> Implement globals, just add to how we codegen in root node (check if function of variable) + print directives and update places where we use variable identifiers to check global map.</del> (Marked complete 26/03/2021)
- Implement floats (Please Kai <3)
- Implement typedef (should be pretty easy probs)
- Actually implement types `char` and `unsigned`, check if `void` functions work

Passing Testbench (last updated 27/03/2021)
-------------------------------------------
This list will keep track of the [pre-included test cases](../compiler_tests) that pass the entire testing process. This is done using the test process outlined in the [**specification**](../c_compiler.md), implemented in [**run_test.sh**](../utility/run_test.sh). Running single testcases are done using [**test_single.sh**](../utility/test_single.sh) and testing subdirectories (or all tests) is done using [**test_dir.sh**](../utility/test_dir.sh).

We are currently passing:
- [**array**](../compiler_tests/array) - Passes 5 out of 5 cases
- [**control_flow**](../compiler_tests/control_flow) - Passing 13 out of 13 cases
- [**default**](../compiler_tests/default) - Passes 5 out of 5 cases
- [**Extra**](../compiler_tests/Extra) Passes 9 out of 9 cases, checking break / continue behaviour + reading / writing to global variables / arrays + other random testcases we've added
- [**float**](../compiler_tests/floats) - Not yet implemented
- [**functions**](../compiler_tests/functions) - Passes 10 out of 10 cases
- [**integer**](../compiler_tests/integer) - Passes 12 out of 12 cases
- [**local_var**](../compiler_tests/local_var) - Passes 7 out of 7 cases.
- [**misc**](../compiler_tests/misc) - Passes 2 out of 6 testcases (typedef and enum not yet implemented)
- [**pointer**](../compiler_tests/pointer) - Passes 4/5 (not arithmetic) 
- [**programs**](../compiler_tests/programs) - Passes 3 out of 3 cases
- [**strings**](../compiler_tests/strings) - Not yet implemented
- [**struct**](../compiler_tests/struct) - Not yet implemented
- [**types**](../compiler_tests/types) - Passes 5 out of 5 cases

Overall we are passing **72/97** total testcases.

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

**17/03/2021**
BIG NEWS!!! After thinking for a long ass time, we've come up with the context required for codegen. It's still a work in progress and we'll probably add / remove shit as we go but it's a big step forward. Additionally, I have codegen producing what *looks like* correct assembly for the base test case we came up with so long ago... From here we have a working framework, we just need to build from here. The word vomit in [**notes**](notes.md) kinda outlines the logic for the stack and frame pointers (it's not formatted well at all, refer to the bottom for most recent thoughts). Added some new goals to work on.

**18/03/2021**
Finished the test script, and tested it on a case which passes! Also intentionally changed the assembly to be wrong and it correctly identifies the failure to ensure it wasn't a false positive. Added a new section in the log to track which testcases pass.

*Update_1*
Added `While` class in AST for while loops, now correctly producing the AST for while, added relevant test cases to AST section. This now means our parser / AST is fully able to parse all the basic features outlined by the spec. The goal now is to finish codegen for all these constructs, and then to start on intermediate features.

**20/03/2021**
Solved a big issue where our parser wouldn't correctly work when variables were declared and initialised at the same time, added new AST class to handle it. Also worked a lot more on register allocation / representation in context, seems to be working and passing more tests. <del>*Note: We were passing test cases where assembly being produced was wrong, I'm not sure why this was the case, might need to clarify with UTA.*</del> **never mind, I fixed this issue in the script**. Just need to keep working on codegen and running more tests.

**22/03/2021**
Implemented codegen for IfElse statements, all relevant tests (that I know of) are passing. Added/Updated functionality in context to work better, and updated return so that it actually exits a function instead of exiting a function at the end of the definiton. Want to implement function calls so that we can *hopefully* pass all tests in [**default**](../compiler_tests/default), as well as look at scopes so that we can pass all tests in [**local_var**](../compiler_tests/local_var) (see [**scoped_var.c**](../compiler_tests/local_var/scoped_var.c), need to check how parser handles this).

*Update_1*
Updated the scope logic, a little wasteful but should work and I cba making it cleaner, now passing [**scoped_var.c**](../compiler_tests/local_var/scoped_var.c). Reworked the testing scripts to have 2 different scripts, [**test_single.sh**](../utility/test_single.sh) accomplishes what **run_test.sh** did previously (this is now a helper script), and [**test_dir.sh**](../utility/test_dir.sh) tests all testcases in a given directory, or every test if no directory is specified. We now pass every test in [**local_var**](../compiler_tests/local_var).

*Update_2*
Implemented while codegen, again the scope stuff is a bit unelegant but if they wanted me to care about having neat implementation they shouldn't just assess the functional correctness of the compile :). Updated ifElse to free the register used to evaluate the condition, previously would have it allocated for the remainder of the runtime of the program. With that our compiler works for all the basic features outlined in the spec (just waiting on kai to finish off some of the operators). Time for function calls!

*Update_3*
Function calls was a bitch... Had to add some more structs in the AST since we are no longer simply containing a single function definition in our source code. Added a root node and a global scope to contain the different functions (should work for global vars too). Added new method `getNode(unsigned index)` which allows higher up nodes to compile lower branches, as there is too much specific behaviour for more generic branches in different cases (i.e. a declaration containing a function declaration in a function definition (a function definition), or just a declaration containing a function declaration (a function declaration)), and so the behaviour needs to be moved to the top level entity. Also made some changes to the context, added a map to keep track of function declarations so that for calls we now how much space we need to allocate for the arguments. I'll need to go through all the AST files to ensure the new function is correctly done. All the other codegen is untouched, if changes need to be made later we'll cross that bridge when we get to it. On the bright side, our compiler now pasts **A LOT** of tests, updated relevant section.

**23/03/2021**
Going to go through the repo and remove all the obsolete garbage code / add documentation to clean things up. Pre-refactor we pass 43/87 total testcases provided (for future me to refer back to and make sure I don't break anything). Cleaned a lot of stuff post refactor, and noticed a bug in function call, so now passing 44/87 testcases :D.

*Update_1*
Found issue with [**call_recursive_internal.c**](../compiler_tests/functions/call_recursive_internal.c), it has to do with how left / right ops are handled across function calls. Implemented correct behaviour in binaryAdd, this functionality will have to be refactored to work across all binary operators except assignment (and thing about unary stuff as well) - leaving that to kai cause that's his baby. After making this fix, we now pass 47/87 testcases!

*Update_2*
Finished implementing for loops, now passing all testcases in [**control_flow**](../compiler_tests/control_flow). Also added scripts to create new testcases, as not everything is tested by the testcases provided. Added test to ensure that a for loop with no increment works, and it now passes (after finding and solving a typo in unarySub which would print the wrong assembly). Can no longer test every file in the test directory, as some of the array tests using for-loop lead to an infinite loop, so won't be testing the entire directory until we get arrays implemented. For now I've moved array tests into a different directory so I can still make sure that I'm not breaking anything. Currently passing 48/83 testcases.

**24/03/2021**
Implemented `break` and `continue`, expanded context to include the necessary information. Starting writing testcases to specifically test their functionality, and found some bugs in operators (for syntactic sugar). Going to go through the parser and rework how they're implemented, since they're purely visual, and remove all the unnecessary clases after I'm done making sure continue and break work. For now, here's a list of stuff that's broken (make sure to test these after parser fix);
- `--i`: Causes segfault in visualising
- `++i`: Causes segfault in visualising
- `/=`: Causes segfault in qemu
Pre parser rework, we are passing 53/88 total testcases.

Implemented arrays (except globals) passing 4/5.

*Update_1*
Finished parser expression rework, kept `UnaryInc` and `UnaryDec` classes corresponding to `++` and `--` since it optimised the assembly produced **a lot**, so I felt like they deserved their stay. Using the syntactic sugar on operators now works. We now pass 54/88 testcases :D

*Update_2*
Merged in Kai's array stuff, added the array testcases back into [**compiler_tests**](../compiler_tests). 4/5 Array testcases pass, and we are now passing 58/93 testcases. Updated passing tests with relevant info.

**25/03/2021**
Finished implementing `switch`, `case` and `default` stuff, passing the relevant tests in [**misc**](../compiler_tests/misc), bringing us to a total of 60/93 testcases! Also slightly refactored the methods Kai added to deal with arrays, now method names should be a bit more clear.

*Update_1*
Figured out why we were failing [**call_mutual_recursive.c**](../compiler_tests/functions/call_mutual_recursive.c), solved issue by updating variable bindings map in FuncitonCall to indicate that variables stored in registers not preserved by function calls are no longer allocated in registers. We are now passing 62/93 testcases, updated test section.

**26/03/2021**
Started work on globals, added a bunch of files and now passing 63/93 tests.

*Update_1*
Fully finished implementing both globals (both reading and writing from), and added test cases to ensure this worked (as there were no test cases that actually did this pre-included), with all passing. Our compiler is now passing 67/97 testcases! Updated goals and merging to master.

**27/03/2021**
Added types `void`, `char` and `unsigned` to the primitives header file, and implemented `sizeof` to work for all these, as well as variable names. Currently passing all tests in [**types**](../compiler_tests/types), but the implementation of sizeof is very fragile and currently only works on literal type names and identifiers, functionality needs to be extended so that it works for any expression it can be passed by the parser. The types themselves are also not implemented, so this also needs to be done, will need to add another codegen helper for this. Adding everything didn't break anything, so we are now passing 72/97 testcases.
Implemented Post Inc and Dec everything still working.

*Update_1*
Added implementation for rest of sizeof, currently untested, all tests still passing. Reworked some of the scripts / compiler.cpp to update the formatting as well as just run more cleanly.
Implemented pointer stuff and support for types.

Building AST Correctly (last updated 14/03/2021)
------------------------------------------------
*This probably won't be updated anymore, refer back to the Passing Testbench section for what our compiler passes*

This list will keep track of the [pre-included test cases](../compiler_tests) our AST builds correctly for. The way this testing is done (currently) is by manually inspecting the graphically rendered AST (done using the `PrettyPrint()` method) and ensuring it matches what we expect.
- [**default/test_RETURN.c:**](../compiler_tests/default/test_RETURN.c) Function returning integer constant.
- [**local_var/return_constant.c:**](../compiler_tests/local_var/return_constant.c) Function returning  integer constant.
- [**local_var/identity.c:**](../compiler_tests/local_var/identity.c) Function returning variable.
- [**integer/add.c:**](../compiler_tests/integer/add.c) Function taking 2 input parameters (int variables), returning the sum of both.
- [**control_flow/sequence.c**](../compiler_tests/control_flow/sequence.c) A simple function, declaring an integer variable x, then assigning its value to 1, then adding it to itself, then returning x.
- [**if_else_false.c**](../compiler_tests/control_flow/if_else_false.c) Function with a literal 0 in the condition of an if/else statement with return statements.
- [**if_else_true.c**](../compiler_tests/control_flow/if_else_true.c) Same as above but with literal 1.
- [**if_false.c**](../compiler_tests/control_flow/if_false.c) Function with a literal 0 in the condition of an exclusive if statement with return statements.
- [**if_true.c**](../compiler_tests/control_flow/if_true.c) Same as above but with literal 1.
- [**while_multiple.c**](../compiler_tests/control_flow/while_multiple.c) Assigns a value of 20 to integer x, then runs a while loop decrementing x by 1 each iteration until x > 10, at which point it exits the loop and returns x.
- [**while_once.c**](../compiler_tests/control_flow/while_once.c) Assigns a value of 1 to integer x, then runs a while loop with x as the condition. The loop sets the value of x to 0, causing the loop to exit and return a constant.
- [**while_zero.c**](../compiler_tests/control_flow/while_zero.c) A while loop with a literal 0 in the condition, causing the program to never enter the loop and return 19937 (updated test case to return a different value inside the while)
