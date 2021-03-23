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
		Context context_vis;
		program->generateMIPS(std::cout, context_vis, 2);

		Context context;
		std::vector<std::string> macros = {
			".section .mdebug.abi32",
			".previous",
			".nan legacy",
			".module fp=32",
			".module nooddspreg"
		};
		std::ofstream ofs(argv[4], std::ofstream::out);
		if(ofs.is_open()){
			for(unsigned i = 0; i < macros.size(); i++){
				ofs << macros[i] << std::endl;
			}
			program->generateMIPS(ofs, context, 2);
			ofs.close();
		}
		else{
			std::cerr << "Couldn't open output file: " << argv[4] << std::endl;
			exit(1);
		}

}
