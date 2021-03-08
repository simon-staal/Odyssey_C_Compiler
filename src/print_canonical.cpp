#include "ast.hpp"

int main(int argc, char *argv[])
{
  if(argc != 5){
    std::cerr<<"Usage: bin/c_compiler -S [source-file.c] -o [dest-file.s]"<<std::endl;
    return 1;
  }
  std::ifstream src(argv[2]);

  if(!src.is_open()){
      fprintf(stderr, "Couldn't open '%s'\n", argv[1]);
      exit(1);
  }

  NodePtr program = parseAST(src);
	std::cout << program;

  return 0;
}