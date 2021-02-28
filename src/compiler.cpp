#include "ast.hpp"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
		if(argc != 5){
			std::cerr<<"Usage: bin/c_compiler -S [source-file.c] -o [dest-file.s]"<<std::endl;
			return 1;
		}
		std::ifstream src(argv[1]);

		if(!src.is_open()){
        fprintf(stderr, "Couldn't open '%s'\n", argv[1]);
        exit(1);
    }

		ProgramPtr program=Parse(src);
		std::cout << program << endl;

		// Compile(program);
}
