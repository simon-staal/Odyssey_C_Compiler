#include "ast.hpp"

// extern FILE *yyin // Used to pass input file to lexer / parser

int main(int argc, char *argv[])
{
		if(argc != 5){
			std::cerr<<"Usage: bin/c_compiler -S [source-file.c] -o [dest-file.s]"<<std::endl;
			return 1;
		}

		// Parsing / building AST
		/*
		yyin = fopen(argv[2], "r");
		if(yyin == NULL){
			std::cerr << "Couldn't open file: " << argv[2] << std::endl;
			exit(1);
		}
		*/

		Node *program = parseAST(argv[2]);
		std::cout << "=============AST Representation=============" << std::endl;
		std::cout << program << std::endl;

		std::cout << "===============Assembly Code===============" << std::endl;
		Context context;
		program->generateMIPS(std::cout, context, 2);


}
