#include "ast.hpp"

extern FILE *yyin // Used to pass input file to lexer / parser

int main(int argc, char *argv[])
{
		if(argc != 5){
			std::cerr<<"Usage: bin/c_compiler -S [source-file.c] -o [dest-file.s]"<<std::endl;
			return 1;
		}

		// Parsing / building AST
		yyin = fopen(argv[2], "r");
		if(yyin == NULL){
			std::cerr << "Couldn't open file: " << argv[2] << std::endl;
			exit(1);
		}

		NodePtr program = parseAST(src);
		std::cout << program;

		// Compile(program);
}
