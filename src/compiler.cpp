#include "ast.hpp"

#include <sys/ioctl.h>
#include <unistd.h>
void printHeader(std::string title); // Nice pretty output format

int main(int argc, char *argv[])
{
		if(argc < 5){
			std::cerr<<"Usage: bin/c_compiler -S [source-file.c] -o [dest-file.s] -V (optional)"<<std::endl;
			return 1;
		}

		Node *program = parseAST(argv[2]);

		// -V enables visualisation
		if(argc == 6){
			// Formatting stuff
			struct winsize size;
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
			int width = size.ws_col;
			// Visualising outputs
			printHeader("AST Representation");
			std::cout << program << std::endl;

			printHeader("Assembly Code");
			Context context_vis;
			program->generateMIPS(std::cout, context_vis, 2);
		}

		// Actual compilation
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

void printHeader(std::string title){
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  int width = size.ws_col;
  int lead = (width-title.length())/2;
  int extra = (width-title.length())%2;
  std::string buffer (lead, '=');
  std::string pad = (extra) ? "=" : "";
  std::cout << buffer << title << buffer << pad << std::endl;
}
