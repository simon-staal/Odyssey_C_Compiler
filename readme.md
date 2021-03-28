Odessey C Compiler
==================

This repository contains the preprocessed C90 to MIPS assembly compiler produced as part of the EIE 2nd Year Instruction Set Architecture and Compilers coursework completed in Spring 2021 by me (Simon) and Kai. Development was primarily driven by the [**specification**](admin/c_compiler), but extra features such as AST visualisation were also included in <del>for no reason</del> because I wanted to. Please find below a brief guide to the repository, enjoy! If you have any questions, feel free to drop me a message on Teams or email me (sts219@ic.ac.uk)

Contributors
------------
- Simon Staal (sts219)
- Kaius Connway-Lai (kc319)


Overview
--------
Our compiler can be built by calling `make bin/c_compiler` (or just `make`), and must be invoked as follows:

    bin/c_compiler -S <source-file.c> -o <dest-file.s> -V (optional)

The command-line parameters must be provided in the order outlined above (with the -V flag being optional, and used to visualise the AST / assembly produced), although this functionality might be later improved (most of it was dictated by the spec). For more information on how to run tests on our compiler, please refer to the [*utility*](#utility) section of this readme.


admin
-----
This directory primarily contains documentation produced over the duration of the project, with [*log.md*](admin/log.md) tracking a timeline of the project goals that were set and achieved, as well as brief notes detailing our design approach. It also contains the specification for both the compiler and management components of the coursework. [*notes.md*](admin/notes.md) is a document that (very messily) contains notes about some of aspects of the coursework that were particularly difficult to implement, including stack/frame management, global variables and float implementation.


compiler_tests
--------------
This directory contains all the test cases used to evaluate the functional correctness of our compiler. Most of these were pre-included as part of the specification, but many have been added ourselves, particularly in [**Extra**](compiler_tests/Extra) to further test specific edge cases or to help in development. Each test case has accompanying driver code with which it is tested, where the driver code should always return 0.

include
-------
This directory contains all the header files for our compiler, including the nodes used to develop our [**AST**](include/ast) which we use to generate our assembly, as well as other [*helper functions*](include/parser_list.hpp) for our parser and [*context*](include/ast/context.hpp) used in code generation. The implementaiton for these files is done seperately in [**src**](src/include_impl/ast) to make re-compiling for troubleshooting purposes more efficient. The base class for our AST is [*node*](include/ast/ast_node.hpp), and all of our other AST constructs build off it, with each node serving a specific purpose in code generation, allowing a precise AST representation to be created by our parser.

src
---
As well as containing the [*implementation for our header files*](src/include_impl/ast), this directory also contains the source code for our [*parser*](src/parser.y) written in Yacc and accompanying [*lexer*](src/lexer.flex) written in flex, which are used to initially process the input source code and generate the AST. [*compiler.cpp*](src/compiler.cpp) contains the source code for our actual compiler, and mostly contains any directives needed at the start of the assembly code, as well as some formatting for visualisation.

<a name="utility"></a>utility
-----------------------------
The [**utility**](utility) directory contains several scripts that can be used to test / visualise our compiler.
- [*test_dir.sh*](utility/test_dir.sh) can be used to test the functionality of all cases of a particular sub-directory of [**compiler_tests**](compiler_tests), or every test in the directory if no particular directory is specified. It can be invoked from the base directory as follows:
`utility/test_dir.sh <subdirectory_name> (optional)`

- [*test_single.sh*](utility/test_single.sh) can be used to test the functionality and visualise the produced AST and MIPS assembly of a particular test case. It can be invoked from the base directory as follows:
`utility/test_single.sh <test_name>`
where `<test_name>` is the name of the c-file being tested, i.e. return_constant.c

- [*test_test.sh*](utility/test_test.sh) is more used in the creation of new test cases, but is essentially used to verify the correctness of a test case and its accompanying driver code by using `gcc` to run and simulate the code and ensuring it runs correctly. If you feel like adding any test cases of your own to play around with, you can verify them by invoking:
`utility/test_test.sh <test_path>`
where `<test_path>` is the full path to a particular test, i.e. compiler_tests/control_flow/for_multiple.c
